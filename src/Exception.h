#ifndef EXCEPTION_H
#define EXCEPTION_H

// Base exception class
class Exception : public CL_Exception
{
public:

	// Constructor
	Exception(const std::string &message)
	: CL_Exception(message)
	{
	}

	// Destructor
	virtual ~Exception() throw()
	{
	}
};

#endif
