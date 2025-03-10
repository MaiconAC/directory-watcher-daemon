#include "logger.h"
// Trabalhar com datetim
#include <ctime>
// Ler e escrever arquivos
#include <fstream>
// Operacoes de string
#include <sstream>
#include <string>
#include <ios>

Logger::Logger(const std::string &filename)
  {
    // Abre o arquivo em modo de append(ios::app), os logs sao escritos no final do arquivo
    logFile.open(filename, std::ios::app);
      
    if (!logFile.is_open())
    {
      // Apresentar erro ou para o serviço? Talvez parar e tentar de novo mais tarde
    }
  }

Logger::~Logger() { logFile.close(); }

void Logger::log(const std::string &message, std::time_t currTime)
  {
    // Pega o tempo atual
    std::time_t logTime = (currTime != 0) ? currTime : time(0);

    // Converte o tempo para DateTime, localtime retorna um ponteiro
    tm* timeInfo = localtime(&logTime);

    // Formata string de DateTime -> strftime = string format time
    char timeStamp[20];
    strftime(timeStamp, sizeof(timeStamp), "%Y-%m-%d %H:%M:%S", timeInfo);

    // Constroi string do log
    std::ostringstream logEntry;
    logEntry << "[" << timeStamp << "] "
              << message
              << std::endl;

    // Output to log file
    if (logFile.is_open())
    {
      logFile << logEntry.str();
      logFile
          .flush(); // Ensure immediate write to file
    }
  }

