#ifndef __SINGLETON_LOGGER_HPP
#define __SINGLETON_LOGGER_HPP

#include "logger.hpp"

class SingletonLogger
{
public:
    static Logger& GetInstance();
};


#endif // __SINGLETON_LOGGER_HPP
