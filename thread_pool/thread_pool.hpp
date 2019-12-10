
#ifndef __THREAD_POOL__HPP
#define __THREAD_POOL__HPP

#include <vector>                               // stl vector
#include <boost/atomic.hpp>                     // atomic flags
#include <boost/function.hpp>                   // function

#include "waitable_queue.hpp"                   // waitable q
#include "thread.hpp"                           //thread

namespace detail
{
    class TaskDoer;
}

class ThreadPool
{
public:
    explicit ThreadPool(size_t threadNum = 1);
    ~ThreadPool();
    
    template <typename Task>
    void AddTask(Task task);
    void Stop();

private:
    ThreadPool(const ThreadPool&);              //uncopyable
    ThreadPool& operator=(const ThreadPool&);   //uncopyable

    WaitableQueue<std::vector< boost::function < void() > > > m_tasksQ;
    std::vector<Thread*> m_vecThread;
    boost::atomic<bool>m_stopFlag;
    
    friend class detail::TaskDoer;
};

template <typename Task>
void ThreadPool::AddTask(Task task)
{
    boost::function<void()> newTask(task);
    m_tasksQ.Push(newTask);
}

namespace detail
{
class TaskDoer
{
public:
    TaskDoer(ThreadPool& tp_);
    void operator()();

private:
    ThreadPool& m_tp;

};

} // namespace detail

#endif //__THREAD_POOL__HPP