#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>
#include <string>
#include <fstream>

class Logger
{
  public:
    Logger(const std::string &filename);

    ~Logger();

    void log(const std::string &message, time_t currTime);

  private:
    std::ofstream logFile;
};

#endif
