#include "thread_pool.hpp"

ThreadPool::ThreadPool(size_t threadNum)
    : m_tasksQ()
    , m_stopFlag(false)  
{
    for (size_t i = 0; i < threadNum; ++i)
    {
        detail::TaskDoer* functor = new detail::TaskDoer(*this);
        m_vecThread.push_back(new Thread(*functor));
    }
}

ThreadPool::~ThreadPool()
{
    Stop();
}

namespace detail
{

static void DoNothing(){}

}//namespace detail


void ThreadPool::Stop()
{
    m_stopFlag.store(true);
    size_t threadNum = m_vecThread.size();
    
    for (size_t i = 0; i < threadNum; ++i)
    {
        m_tasksQ.Push(detail::DoNothing);
    }
    
    for (size_t i = 0; i < threadNum ; ++i)
    {
        delete m_vecThread[i];
    }

    m_vecThread.clear();
}

namespace detail
{

TaskDoer::TaskDoer(ThreadPool& tp)
    :m_tp(tp)
{
}

void TaskDoer::operator()()
{
    while (!m_tp.m_stopFlag.load())
    {
        boost::function<void()> doTask(DoNothing);
        m_tp.m_tasksQ.Pop(doTask);
        doTask();   
    }

    delete this;
}

}//namespace detail
