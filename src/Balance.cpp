#include "Precompiled.h"
#include "Balance.h"
#include "Application.h"
#include "Profile.h"

template<> Balance *Singleton<Balance>::mSingleton = NULL;

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
	"autoaluflag", "realstick", "result", "totaltime", "idletime", "balancetime", "worktime", "keycal0", "cheatepsilon", "rulercal0",
	"rulercal1", "rulercal2", "rulercal3", "rulercalf", "cal0", "cal1", "cal2", "cal3", "testdrv", "loaddef",
	"loadref", "saveref", "passwd", "start", "stop", "enter", "osc", "rotate", "c-meter", "rrulercal0",
	"rrulercal1", "rrulercal2", "rrulercal3", "rrulercal4", "rrulercal5"
};

Balance::Balance(Profile &profile)
: mProtocolValid(true), mSocketNameChanged(false), mOscMode(0)
{
	for (int i = 0; i < MAX_PARAMS; ++i)
		mParams.insert(std::make_pair(PARAMS[i], "0"));
	mParams["result"] = "1"; // HACK: needed to be nonzero after startup

	mSocketName = CL_SocketName(profile.getString("server_addr", "192.168.0.1"), "23");
	profile.setInt("language", profile.getInt("language", 0));
	profile.setString("server_addr", mSocketName.get_address());
	profile.setString("local_addr", profile.getString("local_addr", "127.0.0.1"));
	profile.setString("netmask", profile.getString("netmask", "255.255.255.0"));
	profile.setString("gateway", profile.getString("gateway", "127.0.0.1"));
	profile.setString("dns", profile.getString("dns", "127.0.0.1"));
	profile.setBool("remote_control", profile.getBool("remote_control", true));
	profile.setInt("input_dev", profile.getInt("input_dev", 1));
	profile.setString("cal_command", profile.getString("cal_command", "balance_xinput_calibrator"));
	profile.setString("update_command", profile.getString("update_command", "lxterminal -e \"sleep 5\""));
	profile.setString("available_update_version", profile.getString("available_update_version", ""));
	profile.setString("ignored_update_version", profile.getString("ignored_update_version", ""));

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

void Balance::setOscMode(int mode)
{
	mOscMode = mode;
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

			if (params["version"] == "117" && stream.good())
			{
				mProtocolValid = true;
				for (ParamMap::const_iterator it = params.begin(); it != params.end(); ++it)
					mParams[it->first] = it->second;
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
	CL_ConsoleWindow console("Balance", 80, 100);
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif

	while (mStopThread.get() == 0)
	{
		try
		{
			if (mStopThread.get() != 0)
				return;

			if (mSocketNameChanged)
			{
				mSocketName = mNewSocketName;
				mSocketNameChanged = false;
			}

			CL_Console::write_line("Connecting...");
			mConnected.set(0);
			mRequests.clear();
			CL_TCPConnection connection(mSocketName);
			mConnected.set(1);
			CL_Console::write_line("*** OK ***");

			CL_SocketName serverSocketName(mSocketName.get_address(), "16666");
			CL_UDPSocket socket(CL_SocketName("16679"));

			unsigned startTime = CL_System::get_time();
			int numRetries = 0;
			int oscMode = 0;
			std::string data;
			unsigned short oldIndex = 0xFFFF;
			while (mStopThread.get() == 0 && numRetries <= MAX_RETRIES && !mSocketNameChanged)
			{
				int elapsedTime = CL_System::get_time() - startTime;
				if (elapsedTime >= POLL_INTERVAL)
				{
					startTime += POLL_INTERVAL;
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
						std::string request = cl_format("osc %1\r\n", mOscMode);
						CL_Console::write_line("> " + request.substr(0, request.length() - 2));
						connection.write(request.c_str(), request.length());

						if (oscMode == 0)
						{
							CL_System::sleep(500);
							char ch = '1';
							socket.send(&ch, sizeof(ch), serverSocketName);
						}

						oscMode = mOscMode;
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
					if (connection.get_read_event().wait(oscMode == 0 ? POLL_INTERVAL - elapsedTime : 0))
					{
						// append received data to the data buffer
						char buf[1024];
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
					}

					// read data from UDP socket
					if (socket.get_read_event().wait(oscMode != 0 ? POLL_INTERVAL - elapsedTime : 0))
					{
						// receive data
						unsigned char buf[2048];
						CL_SocketName sender;
						int size = socket.receive(buf, sizeof(buf), sender);
						if (sender.get_address() != serverSocketName.get_address() || size < 4 || buf[0] != 'P' || buf[1] != 'S')
							continue;
						numRetries = 0;

						// check for packet loss
						unsigned short newIndex = buf[2] | buf[3] << 8;
						if (newIndex != ((oldIndex + 1) & 0xFFFF))
							CL_Console::write_line(cl_format("Packet lost: %1", (oldIndex + 1) & 0xFFFF));
						oldIndex = newIndex;
					}
				}
			}

			if (oscMode != 0)
				connection.write("osc 0\r\n", 7);
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
