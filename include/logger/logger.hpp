#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#include <iosfwd>

class Logger
{
public:
    enum Severity {DEBUG, INFO, WARNING, ERROR};

    explicit Logger(Severity initialSeverity = WARNING);    //ctor
    //~Logger() = default
    //Logger(const Logger& other) = default
    //Logger& operator=() = default

    void Log(Severity msgSeverity, const char* msg);
    void Log(Severity msgSeverity, const std::string& msg);

    void SetOutputSeverity(Severity outputSeverity);
    void SetOutput(std::ostream& output);
    Severity GetSeverity();

private:
    enum Out {DEV_NULL = 0 , OUTPUT = 1 , SIZE = 2};
    Severity m_severity;
    std::ostream *m_stream[SIZE];
};


#endif //__LOGGER_HPP