#ifndef BALANCE_H
#define BALANCE_H

#include "Singleton.h"

class Profile;

// Class for communication with the balance device
class Balance : public Singleton<Balance>, CL_Runnable
{
public:

	// Constructor
	Balance(Profile &profile);

	// Destructor
	virtual ~Balance();

	// Returns the connection status
	bool isConnected() const;

	// Returns the protocol valid flag
	bool isProtocolValid() const;

	// Sets the balance address
	void setServerAddr(const std::string &addr);

	// Sets the oscilloscope mode
	void setOscMode(int mode);

	// Returns the balance parameter
	std::string getParam(const std::string &name) const;

	// Returns the integer balance parameter
	int getIntParam(const std::string &name) const;

	// Returns the floating-point balance parameter
	float getFloatParam(const std::string &name) const;

	// Sets the balance parameter
	void setParam(const std::string &name, const std::string &value = "");

	// Sets the integer balance parameter
	void setIntParam(const std::string &name, int value = 0);

	// Sets the floating-point balance parameter
	void setFloatParam(const std::string &name, float value = 0.0f);

private:

	// Name -> value map type
	typedef std::map<std::string, std::string> ParamMap;

	static const int MAX_INPUT_PARAMS = 97;         // Maximum number of input parameters
	static const int MAX_PARAMS = 125;              // Total number of parameters
	static const std::string PARAMS[MAX_PARAMS];    // Parameters list

	static const int POLL_INTERVAL = 100;           // Polling interval
	static const int MAX_RETRIES = 50;              // Maximum number of polling retries

	// Update event handler
	void onUpdate(int delta);

	// Balance thread function
	virtual void run();

	CL_SocketName               mSocketName;        // Current balance address
	CL_Thread                   mThread;            // Balance thread
	CL_InterlockedVariable      mStopThread;        // Balance thread stop flag
	CL_Slot                     mSlotUpdate;        // Update event slot
	CL_InterlockedVariable      mConnected;         // Successful connection flag
	bool                        mProtocolValid;     // Valid protocol flag
	ParamMap                    mParams;            // Parameters map
	CL_Mutex                    mRequestMutex;      // Request queue mutex
	std::vector<std::string>    mRequests;          // Request queue
	CL_Mutex                    mReplyMutex;        // Reply queue mutex
	std::vector<std::string>    mReplies;           // Reply queue
	bool                        mSocketNameChanged; // Socket change flag
	CL_SocketName               mNewSocketName;     // New socket name

	int                         mOscMode;           // New oscilloscope mode
};

#endif
