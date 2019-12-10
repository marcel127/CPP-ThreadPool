#include "thread_pool.hpp"
#include "logger.hpp"
#include "singleton_logger.hpp"
#include <unistd.h>
#include <time.h>


static void ThreadFunc();
Logger& m_logger = SingletonLogger::GetInstance();
boost::mutex mu;

class TestFunctor
{
public:
   
   void operator()()
    {
        static int num = 0;
        mu.lock();
        ++num;

        std::ostringstream str;
        str <<  "DEBUG::I am functor: " << num;
        m_logger.Log(Logger::DEBUG, str.str());

        mu.unlock();

        sleep(2);
    } 

};


int main()
{
    ThreadPool tp(3);

    for(size_t i = 0; i < 100 ; ++i)
    {
        TestFunctor t;
        tp.AddTask(ThreadFunc);
        tp.AddTask(t);
    }

    time_t timeRun = time(NULL) + 10;
    while(timeRun > time(NULL));
    
    tp.Stop();
 
    return 0;
}


void ThreadFunc()
{
    static int num = 0;
    mu.lock();
    ++num;
    
    std::ostringstream str;
    str <<  "DEBUG::I am function: " << num;
    m_logger.Log(Logger::DEBUG, str.str());
    
    mu.unlock();
    
    sleep(2);
}