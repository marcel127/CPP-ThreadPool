#include <fstream>          // write to log
#include <sstream>          // std::ostringstream
#include "logger.hpp"       // logger
#include "thread.hpp"       // thread
#include "thread_exception.hpp"       // thread

pthread_mutex_t mutex;
Logger log(Logger::DEBUG);

void ThreadVoidTest();
void ThreadFunctorTest();
void ThreadSharedPtrTest();
void ThreadFunc();
void SafeCounter();

class ThreadFunctor
{

public:
    ThreadFunctor(){}

    void operator()()
    {
        SafeCounter();
    }
    
    void Fun()
    {
        SafeCounter();
    }

};

int main()
{   
    std::ofstream myfile ("thread_log.log", std::ofstream::out);
    log.SetOutput(myfile);
    pthread_mutex_init(&mutex,0);
    
    log.Log(Logger::DEBUG, "DEBUG ThreadVoidTest output\n");
    ThreadVoidTest();
    
    log.Log(Logger::DEBUG, "\nDEBUG ThreadFunctorTest output\n");
    ThreadFunctorTest();
    
    log.Log(Logger::DEBUG, "\nDEBUG ThreadSharedPtrTest output\n");
    ThreadSharedPtrTest();

    return 0;
}

void ThreadVoidTest()
{
    try
    {
        Thread t1(ThreadFunc);
        Thread t2(ThreadFunc);
        Thread t3(ThreadFunc);
    }

    catch(ExceptionCreateEAGAIN &a)
    {
        log.Log(Logger::ERROR,a.what());
    }
    catch(ExceptionCreateEINVAL &b)
    {
        log.Log(Logger::ERROR,b.what());
    }
    catch(ExceptionCreateEPERM &c)
    {
        log.Log(Logger::ERROR,c.what());
    }
    catch(ThreadException &e)
    {
        log.Log(Logger::ERROR,e.what());
    }
    
    // t1.Join();
    // t2.Join();
    // t3.Join();
}

void ThreadFunctorTest()
{
    ThreadFunctor tf;
    try
    {
        Thread t1(tf);      
        Thread t2(tf);      
        Thread t3(tf);
    }

    catch(ExceptionCreateEAGAIN &a)
    {
        log.Log(Logger::ERROR,a.what());
    }
    catch(ExceptionCreateEINVAL &b)
    {
        log.Log(Logger::ERROR,b.what());
    }
    catch(ExceptionCreateEPERM &c)
    {
        log.Log(Logger::ERROR,c.what());
    }
    catch(ThreadException &e)
    {
        log.Log(Logger::ERROR,e.what());
    }

    // t1.Join();
    // t2.Join();
    // t3.Join();
}

void ThreadSharedPtrTest()
{
    ThreadFunctor* tf = new ThreadFunctor;
    boost::shared_ptr <ThreadFunctor> p_tf(tf);
    
    try
    {
        Thread t1(p_tf, &ThreadFunctor::Fun);
        Thread t2(p_tf, &ThreadFunctor::Fun);
        Thread t3(p_tf, &ThreadFunctor::Fun);
    }
    catch(ExceptionCreateEAGAIN &a)
    {
        log.Log(Logger::ERROR,a.what());
    }
    catch(ExceptionCreateEINVAL &b)
    {
        log.Log(Logger::ERROR,b.what());
    }
    catch(ExceptionCreateEPERM &c)
    {
        log.Log(Logger::ERROR,c.what());
    }
    catch(ThreadException &e)
    {
        log.Log(Logger::ERROR,e.what());
    }
    
    // t1.Join();
    // t2.Join();
    // t3.Join();
}

void ThreadFunc()
{
    SafeCounter();    
}

void SafeCounter()
{
    pthread_mutex_lock(&mutex);
    
    static int count = 0;
    std::ostringstream str;
    str << count << "\n";
    log.Log(Logger::DEBUG,str.str() );
    ++count;
    
    pthread_mutex_unlock(&mutex);
}