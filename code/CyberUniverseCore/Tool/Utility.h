#pragma once
#include <windows.h>


//自动锁
template<typename T>
class __AutoLock
{
public:
	__AutoLock(T& lock) : m_lock(lock){m_lock.Lock();}
	~__AutoLock(){m_lock.Unlock();}
private:
	T& m_lock;
};



// 互斥体
class __Mutex
{
public:
	__Mutex(){InitializeCriticalSection(&m_cs);}
	virtual ~__Mutex(){DeleteCriticalSection(&m_cs);}
	void Lock(){EnterCriticalSection(&m_cs);}
	void Unlock(){LeaveCriticalSection(&m_cs);}
	bool TryLock(){return FALSE != TryEnterCriticalSection(&m_cs);}
	int GetRecursionCount(){return m_cs.RecursionCount;}//获取当前线程临界区的递归深度（进入次数）
private:
	CRITICAL_SECTION	m_cs;
};

