#include "singleton_logger.hpp"

Logger& SingletonLogger::GetInstance()
{
    static Logger singleton(Logger::DEBUG);

    return singleton;
}

