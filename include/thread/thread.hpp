#ifndef __THREAD__HPP
#define __THREAD__HPP

#include <iostream>         // exception
#include <pthread.h>        // c thread
#include <errno.h>          // error flags 
#include <boost/shared_ptr.hpp>     // shr_ptr

#include "thread_exception.hpp"


#if __cplusplus < 201103UL
    #define noexcept throw()
    #define nullptr 0

#endif

class Thread
{
public:
    typedef void(*VoidPtrFunc)();
    typedef void*(*ArgPtrFunc)(void *);
    
    Thread(VoidPtrFunc threadFunction);
    ~Thread() noexcept;
    
    template<typename T>
    Thread(const T& func);

    template <typename T>
    Thread(boost::shared_ptr<T>& shp,  void(T::*Fun)());
    void Join();

private:
    Thread(const Thread& other);                //uncopyable
    Thread& operator=(const Thread& other);     //uncopyable
    void CheckError(const int& err) const;
    
    pthread_t m_threadID;
    bool m_isJoin;
};

template <typename T>
void *Run(void *func);

template<typename T>
Thread::Thread(const T& func)
    : m_isJoin(false)
{
    int err = pthread_create(&m_threadID, NULL, Run<T>, (void *)&func);
   
    if(0 != err)
    {
        CheckError(err);
    }
}

template <typename T>
void *Run(void *func)
{
    T* obj = reinterpret_cast<T*>(func);

    (*obj)();   //call functor operator()

    return nullptr;
}

template <typename T>
Thread::Thread(boost::shared_ptr<T>& shp, void(T::*Fun)())
    : m_isJoin(false)
{
    int err = pthread_create(&m_threadID, NULL, 
                            *reinterpret_cast<ArgPtrFunc *>(&Fun) ,&shp);
    if(0 != err)
    {
        CheckError(err);
    }

}

#endif //__THREAD__HPP
