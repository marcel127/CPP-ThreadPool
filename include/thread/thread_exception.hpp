#ifndef __THREAD_EXCEPTION__HPP
#define __THREAD_EXCEPTION__HPP

#include <exception>        // exception
#include <stdexcept>        // runtime_error 

struct ThreadException : public std::runtime_error
{
    ThreadException();
    
protected: 
    ThreadException(const std::string& err);
};

struct CreateException : public ThreadException
{
    CreateException();
protected: 
    CreateException(const std::string& err);
};

struct ExceptionCreateEAGAIN : public CreateException 
{
    ExceptionCreateEAGAIN();
};

struct ExceptionCreateEINVAL : public CreateException
{
    ExceptionCreateEINVAL();
};

struct ExceptionCreateEPERM : public CreateException
{
    ExceptionCreateEPERM();
};

struct JoinException : public ThreadException 
{
    JoinException();
protected: 
    JoinException(const std::string& err);
};

struct ExceptionJoinEDEADLK : public JoinException
{
    ExceptionJoinEDEADLK();
};

struct ExceptionJoinESRCH : public JoinException
{
    ExceptionJoinESRCH();
};

struct ExceptionJoinEINVAL : public JoinException
{
    ExceptionJoinEINVAL();
};



#endif //__THREAD_EXCEPTION__HPP