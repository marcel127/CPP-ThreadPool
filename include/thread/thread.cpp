#include "thread.hpp"

void Thread::CheckError(const int& err) const
{
    if (EAGAIN == err)
    {
        throw ExceptionCreateEAGAIN();
    }

    else if (EPERM == err)
    {
        throw ExceptionCreateEPERM();
    }

    else if (EINVAL == err)
    {
        throw ExceptionCreateEINVAL();
    }

    else
    {
        throw ThreadException();
    }
    
}

Thread::Thread(VoidPtrFunc threadFunction)
    : m_isJoin(false)
{
    int err = pthread_create(&m_threadID, NULL, 
                          reinterpret_cast<ArgPtrFunc>(threadFunction), NULL);
    if(0 != err)
    {
        CheckError(err);
    }

}

Thread::~Thread() noexcept
{
    if (!m_isJoin)
    {
        Join();
    }
}

void Thread::Join() 
{
    int err = pthread_join(m_threadID, NULL);
    m_isJoin = true;

    if(0 != err)
    {
        if (EDEADLK == err)
        {
            throw ExceptionJoinEDEADLK();
        }
    
        else if (ESRCH == err)
        {
            throw ExceptionJoinESRCH();
        }
    
        else if (EINVAL == err)
        {
            throw ExceptionJoinEINVAL();
        }

        else
        {
            throw ThreadException();
        }
    } 
}


ThreadException::ThreadException() :runtime_error("Global thread exception"){}
    
ThreadException::ThreadException(const std::string& err) :runtime_error(err){}

CreateException::CreateException() :ThreadException("Creation exception"){}
 
CreateException::CreateException(const std::string& err) :ThreadException(err){}

ExceptionCreateEAGAIN::ExceptionCreateEAGAIN() :CreateException(
                    "EAGAIN Insufficient resources to create another thread\n"){}

ExceptionCreateEINVAL::ExceptionCreateEINVAL() :CreateException(
        "No permission to set the scheduling policy \
                                       and  parameters  specified  in attr\n"){}

ExceptionCreateEPERM::ExceptionCreateEPERM() :CreateException(
                                                "Invalid settings in attr\n"){}

JoinException::JoinException() :ThreadException("Join exception"){}
 
JoinException::JoinException(const std::string& err) :ThreadException(err){}

ExceptionJoinEDEADLK::ExceptionJoinEDEADLK() :JoinException(
            "A deadlock  was  detected (e.g., two threads tried to join with \
                                                                each other)\n"){}

ExceptionJoinESRCH::ExceptionJoinESRCH() :JoinException(
        "Another thread is already waiting to join with this thread.\n or \
                                            thread is not a joinable thread."){}

ExceptionJoinEINVAL::ExceptionJoinEINVAL() :JoinException(
    "No thread with the ID thread could be found\n"){}
