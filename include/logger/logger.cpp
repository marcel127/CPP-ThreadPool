#include <fstream>
#include <iostream>
#include "logger.hpp"

Logger::Logger(Severity initialSeverity)
    : m_severity(initialSeverity)
{
    static std::ofstream s_devNull("/dev/null", std::ofstream::out);
    
    m_stream[DEV_NULL] = &s_devNull;
    m_stream[OUTPUT] = &std::cerr;
}

void Logger::Log(Severity msgSeverity, const char* msg)
{
    Log(msgSeverity , std::string(msg));
}

void Logger::Log(Severity msgSeverity, const std::string& msg)
{
    *m_stream[m_severity <= msgSeverity] << msg << std::endl;
}

void Logger::SetOutputSeverity(Severity outputSeverity)
{
    m_severity = outputSeverity;
}

void Logger::SetOutput(std::ostream& output)
{
    m_stream[OUTPUT] = &output;
}

Logger::Severity Logger::GetSeverity()
{
    return m_severity;
}


