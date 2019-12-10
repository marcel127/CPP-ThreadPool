#include "logger.hpp"
#include <fstream>
#include <iostream>

void StdErrTest();
void LogFileTest();

int main()
{
    StdErrTest();
    LogFileTest();

    return 0;
}

void StdErrTest()
{
    Logger logger(Logger::INFO);

    logger.Log(Logger::DEBUG, "DEBUG MSG\n");
    logger.Log(Logger::INFO, "INFO MSG\n");
    logger.Log(Logger::ERROR, "ERROR MSG\n");

    logger.SetOutputSeverity(Logger::ERROR);

    logger.Log(Logger::WARNING, "WARNING MSG\n");
    logger.Log(Logger::ERROR, "ERROR MSG"); 
    
}

void LogFileTest()
{
    Logger logger(Logger::INFO);

    std::ofstream myfile ("a.log", std::ofstream::out);
    
    logger.SetOutput(myfile);
    
    logger.Log(Logger::DEBUG, "DEBUG MSG\n");
    logger.Log(Logger::INFO, "INFO MSG\n");
    logger.Log(Logger::ERROR, "ERROR MSG\n");

    logger.SetOutputSeverity(Logger::ERROR);

    logger.Log(Logger::WARNING, "WARNING MSG\n");
    logger.Log(Logger::ERROR, "ERROR MSG");
}

