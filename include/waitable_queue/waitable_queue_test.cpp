#include "waitable_queue.hpp"
#include "thread.hpp"
#include "logger.hpp"
#include "singleton_logger.hpp"
#include <unistd.h>
#include <vector>

static void PushPopTest();
static void PushPopTimeTest();
static void ThreadTest();

static void PushThread();
static void PopThread();

Logger g_logger = SingletonLogger::GetInstance();
static WaitableQueue<std::vector<int> > threadQ;
static size_t g_numOfThread = 0;    

static boost::mutex errLock;

int main()
{
    PushPopTest();
    PushPopTimeTest();
    ThreadTest();

    return 0;
}


void PushPopTest()
{
    WaitableQueue<std::vector<int> > wq;
    size_t error = 0;
    
    for(int i = 0; i < 10 ; ++i)
    {
        wq.Push(i);
    }
    for(int i = 0; i < 10 ; ++i)
    {
        int ans = 0;
        wq.Pop(ans);
        if(i != ans)
        {
            std::ostringstream str;
            str <<  "ERROR::pop error expected: " << i << " result:" << ans;
            g_logger.Log(Logger::ERROR, str.str());
            ++error;
        }
    }

    if(error == 0)
    {
        g_logger.Log(Logger::INFO, "INFO::TEST PUSH POP SUCCESS");
    }
    else
    {
        g_logger.Log(Logger::ERROR, "ERROR::TEST PUSH POP FAILED");
    }
    

}

void PushPopTimeTest()
{
    WaitableQueue<std::vector<int> > wq;
    boost::chrono::milliseconds timer(1000);

    size_t error = 0;
    
    for(int i = 0; i < 10 ; ++i)
    {
        wq.Push(i);
    }
        
    int ans = 0;
    
    for(int i = 0; i < 10 ; ++i)
    {
        if(true != wq.Pop(ans, timer))
        {
            std::ostringstream str;
            str <<  "ERROR::pop error expected: " << true << " result:" << false;
            g_logger.Log(Logger::ERROR, str.str());
            ++error;
        }
    }
    
    timer.zero();
    if(true == wq.Pop(ans, timer))
    {
        std::ostringstream str;
        str <<  "ERROR::pop error expected: " << true << " result:" << false;
        g_logger.Log(Logger::ERROR, str.str());
        ++error;
    }

    if(error == 0)
    {
        g_logger.Log(Logger::INFO, "INFO::TEST TIMED PUSH POP SUCCESS");
    }
    else
    {
        g_logger.Log(Logger::ERROR, "ERROR::TEST TIMED PUSH POP FAILED");
    }   
}

void ThreadTest()
{
    Thread t1(PopThread);
    Thread t2(PopThread);
    Thread t3(PopThread);
    Thread t4(PopThread);

    g_numOfThread = 4;
    Thread t5(PushThread);
    
    t1.Join();
    t2.Join();
    t3.Join();
    t4.Join();
    t5.Join();
    int x = 0;
    
    boost::chrono::milliseconds timer(3000);
    if(false == threadQ.Pop(x,timer))
    {
        g_logger.Log(Logger::INFO, "INFO::THREAD SUCCESS");
    }
    else
    {
        g_logger.Log(Logger::INFO, "INFO::THREAD FAILED");
    }

}

void PopThread()
{
    int x = 0;
    threadQ.Pop(x);
}

void PushThread()
{
    size_t i = 0;
    while(i < g_numOfThread)
    {
        threadQ.Push(0);
        ++i;
    }
}