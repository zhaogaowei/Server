#include "EventLoopThreadPool.h"

EventLoopThreadPool::EventLoopThreadPool(const int threadNum)
	:_threadNum(threadNum),
	_nextID(0)
{
	for (int i = 0; i < threadNum; ++i) {
		EventLoopThread *thread = new EventLoopThread();
		_threads.push_back(thread);
	}
}

EventLoopThreadPool::~EventLoopThreadPool()
{
	for (int i = 0; i < _threadNum; ++i)
		delete _threads[i];
}

//ÿ������ѯ�ķ�ʽ��ȡһ�������߳�
EventLoopThread * EventLoopThreadPool::getNextThread()
{
	if (_nextID >= _threadNum)
		_nextID = 0;
	return _threads[_nextID++];
}
