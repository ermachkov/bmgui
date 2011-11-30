#ifndef SINGLETON_H
#define SINGLETON_H

#include "GameAssert.h"

// Singleton template class
template<typename T> class Singleton
{
public:

	// Constructor
	Singleton()
	{
		GAME_ASSERT(mSingleton == NULL);
		mSingleton = static_cast<T *>(this);
	}

	// Destructor
	virtual ~Singleton()
	{
		GAME_ASSERT(mSingleton != NULL);
		mSingleton = NULL;
	}

	// Returns a reference to the global class instance
	static T &getSingleton()
	{
		GAME_ASSERT(mSingleton != NULL);
		return *mSingleton;
	}

	// Returns a pointer to the global class instance
	static T *getSingletonPtr()
	{
		return mSingleton;
	}

protected:

	// Global instance pointer
	static T *mSingleton;
};

#endif
