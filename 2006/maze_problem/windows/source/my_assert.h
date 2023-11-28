#ifndef MY_ASSERT
#define MY_ASSERT

#define DEBUG
#ifdef DEBUG
	void _mAssert(char *, unsigned);

	#define mASSERT(f) \
		if(f) \
			NULL; \
		else \
			_mAssert(__FILE__,__LINE__);

#else

	#define mASSERT(f) NULL

#endif

#endif