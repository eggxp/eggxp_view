//---------------------------------------------------------------------------

#ifndef AThreadLockH
#define AThreadLockH
//---------------------------------------------------------------------------
#include <vcl.h>

class ThreadLock
{
private:
	CRITICAL_SECTION * m_Lock;

public:
	ThreadLock(CRITICAL_SECTION * lock)
	{
		m_Lock = lock;
		if (m_Lock)
			EnterCriticalSection(m_Lock);
	}

	~ThreadLock()
	{
		if (m_Lock)
			LeaveCriticalSection(m_Lock);
	}
};

#endif
