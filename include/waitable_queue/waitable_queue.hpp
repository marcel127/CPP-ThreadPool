#ifndef _WAITABLE_QUEUE__HPP
#define _WAITABLE_QUEUE__HPP

#include <boost/thread/mutex.hpp>               //mutex
#include <boost/thread/condition_variable.hpp>  //condition varible
#include <boost/chrono.hpp>                     //milisecond

template <typename Container>
class WaitableQueue
{
public:
    explicit WaitableQueue();
    //~WaitableQueue() = default
    void Push(const typename Container::value_type& obj);
    void Pop(typename Container::value_type& obj);
    bool Pop(typename Container::value_type& obj, const boost::chrono::milliseconds timeOut);

private: 
    WaitableQueue(const WaitableQueue&);                //uncopyable
    WaitableQueue& operator=(const WaitableQueue&);     //uncopyable
    
    Container m_q;
    boost::mutex m_mutex;
    boost::condition_variable m_cv;
};

template <typename Container>
WaitableQueue<Container>::WaitableQueue()
    : m_q(),
      m_mutex(),
      m_cv() //,
{
}

template <typename Container>
void WaitableQueue<Container>::Push(const typename Container::value_type& obj)
{
    boost::unique_lock<boost::mutex> locker(m_mutex); 
    
    m_q.push_back(obj);
    m_cv.notify_one();
}

template <typename Container>
void WaitableQueue<Container>::Pop(typename Container::value_type& obj)
{
    boost::unique_lock<boost::mutex> locker(m_mutex);
    
    while(m_q.empty())
    {
        m_cv.wait(locker);
    } 
    
    obj = *m_q.begin();
    m_q.erase(m_q.begin());

}

template <typename Container>
bool WaitableQueue<Container>::Pop(typename Container::value_type& obj,
                                            const boost::chrono::milliseconds timeOut)
{
    boost::unique_lock<boost::mutex> locker(m_mutex);
    boost::cv_status timeStatus(boost::cv_status::no_timeout);
    
    while(m_q.empty() && timeStatus == boost::cv_status::no_timeout)
    {
        timeStatus = m_cv.wait_for(locker, timeOut);
    }

    bool isSucceeded = false;
    if(boost::cv_status::no_timeout == timeStatus)
    {
        isSucceeded = true;
        obj = *m_q.begin();
        m_q.erase(m_q.begin());
    }
    
    return isSucceeded;
}

#endif //_WAITABLE_QUEUE__HPP