#include "Precompiled.h"
#include "Balance.h"
#include "Application.h"
#include "Graphics.h"
#include "Profile.h"

template<> Balance *Singleton<Balance>::mSingleton = NULL;
const float Balance::PI = 3.1415926535897932f;

const std::string Balance::PARAMS[MAX_PARAMS] =
{
	"version", "state", "substate", "testmode", "spiinput", "drvcurr", "drvvolt", "wheelangle", "wheelspeed", "rofs",
	"rdiam", "rwidth", "weight0", "angle0", "rndweight0", "wheelangle0", "weight1", "angle1", "rndweight1", "wheelangle1",
	"weight2", "angle2", "rndweight2", "wheelangle2", "user", "msg1", "width", "diam", "offset", "split",
	"numsp", "mode", "layout", "stick", "roundmode", "minweight", "startmode", "covermode", "pedalmode", "automode",
	"clockwise", "truemode", "autoalu", "maxrot", "diamepsilon", "drvfreq", "minfreq", "accthld", "angleepsilon", "rulerhorz",
	"rulervert", "rulerrad", "rulerofs", "rulerdiam", "calweight", "deccurr", "decfreq", "weightdist", "v0", "v1",
	"v2", "v3", "v4", "v5", "va0", "va1", "va2", "va3", "va4", "va5",
	"va6", "va7", "w0", "w1", "w2", "w3", "freqcoeff", "rstick", "c0", "c1",
	"c2", "c3", "c4", "c5", "r0", "r1", "errors0", "errors1", "errors2", "wheeldist",
	"autoaluflag", "realstick", "result", "totaltime", "idletime", "balancetime", "worktime", "muxval", "keycal0", "cheatepsilon",
	"rulercal0", "rulercal1", "rulercal2", "rulercal3", "rulercalf", "cal0", "cal1", "cal2", "cal3", "testdrv",
	"loaddef", "loadref", "saveref", "passwd", "start", "stop", "enter", "osc", "rotate", "c-meter",
	"rrulercal0", "rrulercal1", "rrulercal2", "rrulercal3", "rrulercal4", "rrulercal5"
};

Balance::Balance(Profile &profile)
: mProtocolValid(true), mSocketNameChanged(false), mOscMode(0), mCurrSample(0), mPlaying(true), mVertScale(1.0f), mHorzScale(1.0f), mSampleOffset(0),
  mSSHStarted(false), mSSHRunning(false), mSSHPinging(false)
{
	for (int i = 0; i < MAX_PARAMS; ++i)
		mParams.insert(std::make_pair(PARAMS[i], "0"));
	mParams["result"] = "1"; // HACK: needed to be nonzero after startup

	mSocketName = CL_SocketName(profile.getString("server_addr"), "23");

	mSlotUpdate = Application::getSingleton().getSigUpdate().connect(this, &Balance::onUpdate);

	mThread.start(this);
}

Balance::~Balance()
{
	if (isConnected())
	{
		mStopThread.set(1);
		mThread.join();
	}
	else
	{
		mThread.kill();
	}

	stopSSH();
}

bool Balance::isConnected() const
{
	return mConnected.get() != 0;
}

bool Balance::isProtocolValid() const
{
	return mProtocolValid;
}

void Balance::setServerAddr(const std::string &addr)
{
	mNewSocketName = CL_SocketName(addr, "23");
	mSocketNameChanged = true;
}

void Balance::setOscMode(int ch1, int ch2)
{
	if (ch1 == OSC_NONE || ch2 == OSC_NONE)
		ch1 = ch2 = OSC_NONE;
	else if (ch1 == OSC_QEP || ch2 == OSC_QEP)
		ch1 = ch2 = OSC_QEP;
	else if (ch1 == OSC_FFT || ch2 == OSC_FFT)
		ch1 = ch2 = OSC_FFT;
	mOscMode = ch1 | ch2 << 8;
}

void Balance::setVertScale(float scale)
{
	mVertScale = scale;
}

void Balance::setHorzScale(float scale)
{
	mHorzScale = scale;
}

void Balance::setSampleOffset(int offset)
{
	mSampleOffset = offset;
}

void Balance::setPlaying(bool playing)
{
	mPlaying = playing;
}

void Balance::getMinMaxSamples(int *minSample1, int *minSample2, int *maxSample1, int *maxSample2)
{
	CL_MutexSection mutexSection(&mOscMutex);
	*minSample1 = mMinSamples[0];
	*minSample2 = mMinSamples[1];
	*maxSample1 = mMaxSamples[0];
	*maxSample2 = mMaxSamples[1];
}

void Balance::getAmplitudePhase(float *amplitude1, float *phase1, float *amplitude2, float *phase2)
{
	CL_MutexSection mutexSection(&mOscMutex);
	*amplitude1 = floor(abs(mMainHarmonic[0]));
	*phase1 = arg(mMainHarmonic[0]) * 180.0f / PI;
	*amplitude2 = floor(abs(mMainHarmonic[1]));
	*phase2 = arg(mMainHarmonic[1]) * 180.0f / PI;
}

std::string Balance::getParam(const std::string &name) const
{
	ParamMap::const_iterator it = mParams.find(name);
	if (it == mParams.end())
		throw Exception("Invalid parameter name '" + name + "' specified");
	return it->second;
}

int Balance::getIntParam(const std::string &name) const
{
	return CL_StringHelp::text_to_int(getParam(name));
}

float Balance::getFloatParam(const std::string &name) const
{
	return CL_StringHelp::text_to_float(getParam(name));
}

void Balance::setParam(const std::string &name, const std::string &value)
{
	ParamMap::iterator it = mParams.find(name);
	if (it == mParams.end())
		throw Exception("Invalid parameter name '" + name + "' specified");
	it->second = value;

	if (isConnected())
	{
		CL_MutexSection mutexSection(&mRequestMutex);
		mRequests.push_back(name + (!value.empty() ? " " + value : "") + "\r\n");
	}
}

void Balance::setIntParam(const std::string &name, int value)
{
	setParam(name, CL_StringHelp::int_to_text(value));
}

void Balance::setFloatParam(const std::string &name, float value)
{
	setParam(name, CL_StringHelp::float_to_text(value, 2));
}

void Balance::drawOscilloscope(float x1, float y1, float x2, float y2)
{
	if (mOscMode == 0)
		return;

	float width = x2 - x1, height = y2 - y1;
	static CL_Vec2f positions[3][NUM_SAMPLES_QEP];
	static CL_Colorf colors[3] = {CL_Colorf(1.0f, 0.0f, 0.0f), CL_Colorf(0.0f, 1.0f, 0.0f), CL_Colorf(0.0f, 0.0f, 1.0f)};
	float phase[2] = {0.0f, 0.0f};

	// copy data to the buffers
	mOscMutex.lock();
	int numSamples, numChannels;
	if (mOscMode == (OSC_QEP | OSC_QEP << 8))
	{
		numSamples = NUM_SAMPLES_QEP;
		numChannels = 3;
		int index = mCurrSample - numSamples + mSampleOffset;
		if (index < 0)
			index += TOTAL_SAMPLES;
		for (int i = 0; i < numSamples; ++i)
		{
			positions[0][i].x = positions[1][i].x = positions[2][i].x = x1 + width * i / numSamples * mHorzScale;
			positions[0][i].y = y1 + 1.0f * height / 4.0f - (mChannels[0][index] != 0 ? height / 5.0f : 0.0f);
			positions[1][i].y = y1 + 2.0f * height / 4.0f - (mChannels[1][index] != 0 ? height / 5.0f : 0.0f);
			positions[2][i].y = y1 + 3.0f * height / 4.0f - (mChannels[2][index] != 0 ? height / 5.0f : 0.0f);
			if (++index >= TOTAL_SAMPLES)
				index = 0;
		}
	}
	else if (mOscMode == (OSC_FFT | OSC_FFT << 8))
	{
		numSamples = FFT_BUF_SIZE;
		numChannels = 2;

		mMainHarmonic[0] = mFFTBuf[0][NUM_FFT_PERIODS];
		mMainHarmonic[1] = mFFTBuf[1][NUM_FFT_PERIODS];

		float scale[2] = {3.0f / 8.0f * height / abs(mMainHarmonic[0]), 3.0f / 8.0f * height / abs(mMainHarmonic[1])};
		phase[0] = y1 + 1.0f * height / 4.0f - arg(mMainHarmonic[0]) / PI * height / 4.0f;
		phase[1] = y1 + 3.0f * height / 4.0f - arg(mMainHarmonic[1]) / PI * height / 4.0f;
		for (int i = 0; i < numSamples; ++i)
		{
			positions[0][i].x = positions[1][i].x = x1 + width * i / numSamples;
			positions[0][i].y = y1 + height / 2.0f - abs(mFFTBuf[0][i]) * scale[0];
			positions[1][i].y = y1 + height / 1.0f - abs(mFFTBuf[1][i]) * scale[1];
		}
	}
	else
	{
		numSamples = NUM_SAMPLES_ANALOG;
		numChannels = 2;
		float avgSample[2] = {static_cast<float>(mSampleSum[0] / numSamples), static_cast<float>(mSampleSum[1] / numSamples)};
		int index = mCurrSample - numSamples + mSampleOffset;
		if (index < 0)
			index += TOTAL_SAMPLES;
		for (int i = 0; i < numSamples; ++i)
		{
			positions[0][i].x = positions[1][i].x = x1 + width * i / numSamples * mHorzScale;
			positions[0][i].y = y1 + 1.0f * height / 4.0f - (mChannels[0][index] - avgSample[0]) / 2097152.0f * height / 4.0f * mVertScale;
			positions[1][i].y = y1 + 3.0f * height / 4.0f - (mChannels[1][index] - avgSample[1]) / 2097152.0f * height / 4.0f * mVertScale;
			if (++index >= TOTAL_SAMPLES)
				index = 0;
		}
	}
	mOscMutex.unlock();

	// set the clipping rectangle
	Graphics::getSingleton().setClipRect(x1, y1, x2, y2);

	// draw phases
	CL_GraphicContext &gc = Graphics::getSingleton().getWindow().get_gc();
	if (mOscMode == (OSC_FFT | OSC_FFT << 8))
	{
		CL_Draw::line(gc, x1, phase[0], x2, phase[0], CL_Colorf(0.5f, 0.0f, 0.0f));
		CL_Draw::line(gc, x1, phase[1], x2, phase[1], CL_Colorf(0.0f, 0.5f, 0.0f));
	}

	// draw graphs
	CL_PrimitivesArray array(gc);
	gc.set_program_object(cl_program_color_only);
	for (int i = 0; i < numChannels; ++i)
	{
		array.set_attributes(0, positions[i]);
		array.set_attribute(1, colors[i]);
		gc.draw_primitives(cl_line_strip, numSamples, array);
	}
	gc.reset_program_object();

	// reset the clipping rectangle
	Graphics::getSingleton().resetClipRect();
}

void Balance::startSSH()
{
	if (!mSSHStarted)
	{
		mSSHStarted = true;
		mSSHRunning = false;
		mSSHPinging = false;

		mSSHRunThread.start(this, &Balance::SSHRunThreadFunc);
		mSSHPingThread.start(this, &Balance::SSHPingThreadFunc);
	}
}

void Balance::stopSSH()
{
	if (mSSHStarted)
	{
		mSSHRunThread.kill();
		mSSHRunThread = CL_Thread();
		mSSHPingThread.kill();
		mSSHPingThread = CL_Thread();

		mSSHStarted = false;
		mSSHRunning = false;
		mSSHPinging = false;
	}
}

bool Balance::isSSHStarted() const
{
	return mSSHStarted;
}

bool Balance::isSSHConnected() const
{
	return mSSHRunning && mSSHPinging;
}

void Balance::calcFFT(int channel, int start, int end)
{
	// check the number of samples to process
	int N = end >= start ? end - start : end - start + TOTAL_SAMPLES;
	if (N > MAX_FFT_SAMPLES)
		return;

	// calculate FFT transform
	for (int k = 0; k < FFT_BUF_SIZE; ++k)
	{
		std::complex<float> sum(0.0f, 0.0f);
		int index = start;
		for (int n = 0; n < N; ++n)
		{
			float xn = static_cast<float>(mChannels[channel][index]);
			float x = -2.0f * PI * k * n / N;
			sum += xn * std::complex<float>(cos(x), sin(x));
			if (++index >= TOTAL_SAMPLES)
				index = 0;
		}
		mFFTBuf[channel][k] = sum;
	}
}

void Balance::onUpdate(int delta)
{
	// process the reply queue
	CL_MutexSection mutexSection(&mReplyMutex);

	for (std::vector<std::string>::const_iterator it = mReplies.begin(); it != mReplies.end(); ++it)
	{
		std::istringstream stream(*it);
		std::string command;
		stream >> command;

		if (command == "params")
		{
			ParamMap params;
			for (int i = 0; i < MAX_INPUT_PARAMS; ++i)
				stream >> params[PARAMS[i]];

			if (params["version"] == "118" && stream.good())
			{
				mProtocolValid = true;
				for (ParamMap::const_iterator it = params.begin(); it != params.end(); ++it)
					mParams[it->first] = it->second;
				mConnected.set(1);
			}
			else
			{
				mProtocolValid = false;
			}
		}
	}

	mReplies.clear();
}

void Balance::run()
{
#ifdef WIN32
	CL_ConsoleWindow console("bmgui", 80, 100);
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif

	unsigned short oldIndex = 0xFFFF;
	while (mStopThread.get() == 0)
	{
		try
		{
			if (mSocketNameChanged)
			{
				mSocketName = mNewSocketName;
				mSocketNameChanged = false;
			}

			mRequestMutex.lock();
			mRequests.clear();
			mRequestMutex.unlock();

			CL_Console::write_line("Connecting...");
			mConnected.set(0);
			CL_TCPConnection connection(mSocketName);
			CL_Console::write_line("*** OK ***");

			CL_SocketName serverSocketName(mSocketName.get_address(), "16666");
			CL_UDPSocket socket(CL_SocketName("16679"));

			unsigned lastTime = CL_System::get_time();
			int numRetries = 0;
			int oscMode = 0;
			std::string data;
			int numMinMaxSamples = 0;
			int minSamples[2] = {INT_MAX, INT_MAX};
			int maxSamples[2] = {INT_MIN, INT_MIN};
			unsigned char qep = 0x00;
			int startFFTSample = 0;
			int numFFTPeriods = 0;
			while (mStopThread.get() == 0 && numRetries <= MAX_RETRIES && !mSocketNameChanged)
			{
				unsigned currTime = CL_System::get_time();
				int delta = static_cast<int>(currTime - lastTime);
				if (delta < 0 || delta > 1000)
				{
					lastTime = currTime;
					continue;
				}

				if (delta >= POLL_INTERVAL)
				{
					lastTime = currTime;
					++numRetries;

					// first send all pending requests in the queue
					CL_MutexSection mutexSection(&mRequestMutex);
					for (std::vector<std::string>::const_iterator it = mRequests.begin(); it != mRequests.end(); ++it)
					{
						CL_Console::write_line("> " + it->substr(0, it->length() - 2));
						connection.write(it->c_str(), it->length());
					}
					mRequests.clear();
					mutexSection.unlock();

					// finally send the polling/oscilloscope request
					if (oscMode != mOscMode)
					{
						oscMode = mOscMode;

						mOscMutex.lock();
						memset(mChannels, 0, sizeof(mChannels));
						memset(mFFTBuf, 0, sizeof(mFFTBuf));
						mCurrSample = 0;
						mSampleSum[0] = mSampleSum[1] = 0.0;
						mOscMutex.unlock();

						std::string request = "osc 0 0\r\n";
						CL_Console::write_line("> " + request.substr(0, request.length() - 2));
						connection.write(request.c_str(), request.length());
						CL_System::sleep(250);

						if (oscMode != 0)
						{
							int mode = oscMode != (OSC_FFT | OSC_FFT << 8) ? oscMode : (OSC_IIR1 | OSC_IIR2 << 8);
							request = cl_format("osc %1 %2\r\n", mode & 0xFF, mode >> 8 & 0xFF);
							CL_Console::write_line("> " + request.substr(0, request.length() - 2));
							connection.write(request.c_str(), request.length());
							CL_System::sleep(250);

							char ch = '1';
							socket.send(&ch, sizeof(ch), serverSocketName);
						}
					}
					else if (oscMode == 0)
					{
						std::string request = "state\r\n";
						CL_Console::write_line("> " + request.substr(0, request.length() - 2));
						connection.write(request.c_str(), request.length());
					}
				}
				else
				{
					// read data from TCP socket
					if (connection.get_read_event().wait(oscMode == 0 ? POLL_INTERVAL - delta : 0))
					{
						// append received data to the data buffer
						char buf[2048];
						int size = connection.read(buf, sizeof(buf), false);
						data.append(buf, size);

						// split received data to CR+LF-terminated strings
						for (std::string::size_type pos = data.find("\r\n"); pos != std::string::npos; pos = data.find("\r\n"))
						{
							std::string reply = data.substr(0, pos + 2);
							CL_Console::write_line(reply.substr(0, reply.length() - 2));
							data.erase(0, pos + 2);
							numRetries = 0;

							CL_MutexSection mutexSection(&mReplyMutex);
							mReplies.push_back(reply);
						}

						// clear data string on overflow
						if (data.length() > 2048)
							data.clear();
					}

					// read data from UDP socket
					if (socket.get_read_event().wait(oscMode != 0 ? POLL_INTERVAL - delta : 0))
					{
						// receive data
						unsigned char buf[2048];
						CL_SocketName sender;
						int size = socket.receive(buf, sizeof(buf), sender);
						if (size < 4 || sender.get_address() != serverSocketName.get_address() || buf[0] != 'P' || buf[1] != 'S')
							continue;
						numRetries = 0;

						// check for packet loss
						unsigned short newIndex = buf[2] | buf[3] << 8;
						if (newIndex != ((oldIndex + 1) & 0xFFFF))
							CL_Console::write_line(cl_format("Packet lost: %1", (oldIndex + 1) & 0xFFFF));
						oldIndex = newIndex;

						// decode the received data
						if (oscMode != 0 && mPlaying)
						{
							CL_MutexSection mutexSection(&mOscMutex);
							if (oscMode == (OSC_QEP | OSC_QEP << 8))
							{
								for (int i = 0; i < (size - 4) * 8; i += 3)
								{
									mChannels[0][mCurrSample] = (buf[(i + 0) / 8 + 4] & (1 << (i + 0) % 8)) != 0;
									mChannels[1][mCurrSample] = (buf[(i + 1) / 8 + 4] & (1 << (i + 1) % 8)) != 0;
									mChannels[2][mCurrSample] = (buf[(i + 2) / 8 + 4] & (1 << (i + 2) % 8)) != 0;
									if (++mCurrSample >= TOTAL_SAMPLES)
										mCurrSample = 0;
								}
							}
							else
							{
								for (int i = 4; i < size; i += 6)
								{
									// subtract the oldest samples from the samples sum
									int index = mCurrSample - NUM_SAMPLES_ANALOG;
									if (index < 0)
										index += TOTAL_SAMPLES;
									mSampleSum[0] -= mChannels[0][index];
									mSampleSum[1] -= mChannels[1][index];

									// unpack and sign-extend current sample pair
									int sample1 = buf[i + 0] | buf[i + 1] << 8 | (buf[i + 2] & 0x3F) << 16;
									int sample2 = (buf[i + 2] >> 6 & 0x03) | buf[i + 3] << 2 | buf[i + 4] << 10 | (buf[i + 5] & 0x0F) << 18;
									if ((sample1 & 0x00200000) != 0)
										sample1 |= 0xFFC00000;
									if ((sample2 & 0x00200000) != 0)
										sample2 |= 0xFFC00000;

									// add received samples to the buffer
									mChannels[0][mCurrSample] = sample1;
									mChannels[1][mCurrSample] = sample2;

									if (++mCurrSample >= TOTAL_SAMPLES)
										mCurrSample = 0;

									// add the newest samples to the samples sum
									mSampleSum[0] += sample1;
									mSampleSum[1] += sample2;

									// update min/max sample values
									if (sample1 < minSamples[0])
										minSamples[0] = sample1;
									if (sample2 < minSamples[1])
										minSamples[1] = sample2;
									if (sample1 > maxSamples[0])
										maxSamples[0] = sample1;
									if (sample2 > maxSamples[1])
										maxSamples[1] = sample2;

									if (++numMinMaxSamples >= NUM_MIN_MAX_SAMPLES)
									{
										numMinMaxSamples = 0;
										mMinSamples[0] = minSamples[0]; mMinSamples[1] = minSamples[1];
										mMaxSamples[0] = maxSamples[0]; mMaxSamples[1] = maxSamples[1];
										minSamples[0] = minSamples[1] = INT_MAX;
										maxSamples[0] = maxSamples[1] = INT_MIN;
									}

									// calculate FFT if enabled
									if (oscMode == (OSC_FFT | OSC_FFT << 8) && (buf[i + 5] & 0x80) != 0 && (qep & 0x80) == 0 && ++numFFTPeriods >= NUM_FFT_PERIODS)
									{
										calcFFT(0, startFFTSample, mCurrSample);
										calcFFT(1, startFFTSample, mCurrSample);
										startFFTSample = mCurrSample;
										numFFTPeriods = 0;
									}

									// save current QEP byte
									qep = buf[i + 5];
								}
							}
						}
					}
				}
			}

			if (oscMode != 0)
			{
				std::string request = "osc 0 0\r\n";
				CL_Console::write_line("> " + request.substr(0, request.length() - 2));
				connection.write(request.c_str(), request.length());
			}
		}
		catch (const std::exception &exception)
		{
			CL_Console::write_line(cl_format("*** FAIL: %1 ***", exception.what()));
			CL_System::sleep(1000);
		}
		catch (...)
		{
			CL_Console::write_line("*** FAIL ***");
			throw;
		}
	}
}

void Balance::SSHRunThreadFunc()
{
	// ssh -R 50000:127.0.0.1:22 bm@sibek.ru -p 2222 -N
	for (;;)
	{
		// connect to SSH server
		mSSHRunning = true;
		system("ssh -R 50000:127.0.0.1:22 bm@sibek.ru -p 2222 -N");
		mSSHRunning = false;

		// make a delay
		CL_Console::write_line("SSH Terminated");
		CL_System::sleep(5000);
	}
}

void Balance::SSHPingThreadFunc()
{
	// ssh bm@sibek.ru -p 2222 "netstat -an"
	for (;;)
	{
		// make a polling delay
		CL_System::sleep(5000);

		// try to execute netstat command via ssh
		FILE *stream = popen("ssh bm@sibek.ru -p 2222 \"netstat -an\"", "r");
		if (stream == NULL)
		{
			mSSHPinging = false;
			continue;
		}

		// read all output from netstat
		std::string str;
		while (!feof(stream))
			str += fgetc(stream);

		// close the file descriptor
		pclose(stream);

		// parse the output and determine current SSH status
		mSSHPinging = str.find("127.0.0.1.50000") != std::string::npos;
		CL_Console::write_line(mSSHPinging ? "SSH Port: Opened" : "SSH Port: NOT Opened");
	}
}
