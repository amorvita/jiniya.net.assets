#ifndef MY_ASSERT
#define MY_ASSERT

#define DEBUG
#ifdef DEBUG
	void _mAssert(char *, unsigned);

	#define ASSERT(f) \
		if(f) \
			NULL; \
		else \
			_mAssert(__FILE__,__LINE__);

#else

	#define ASSERT(f) NULL

#endif

#endif