#include "directory-watcher.h"
#include "logger.h"
#include <filesystem>
#include <chrono>
#include <time.h>
#include <thread>
#include <unordered_map>
#include <string>
#include <functional>

DirectoryWatcher::DirectoryWatcher(std::string t_directoryPath) : directoryPath(t_directoryPath), running(true), filesState(populateFilesMap()) {}

void DirectoryWatcher::start()
{
  Logger logger("logFile.txt");

  std::string startMessage = "Directory Watcher is running on " + directoryPath + "...";
  logger.log(startMessage, 0);

  while (running)
  {
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Validar se algum arquivo foi excluido -> usa exists para ver se o path existe
    for (auto file = filesState.begin(); file != filesState.end(); ++file)
    {
      if (!std::filesystem::exists(file->first))
      {
        filesState.erase(file->first);
        std::string logMessage = "File: " + file->first + " deleted!";
        logger.log(logMessage, 0);
      }
    }

    for (std::filesystem::directory_entry file : std::filesystem::recursive_directory_iterator(directoryPath))
    {
      std::filesystem::file_time_type fileLastWriteTime = std::filesystem::last_write_time(file);

      if (!filesState.contains(file.path().string()))
      {
        // Valida se o arquivo foi criado -> nao esta no map
        filesState[file.path().string()] = fileLastWriteTime;
        std::string logMessage = "File: " + file.path().string() + " created!";
        logger.log(logMessage, convert_file_time(fileLastWriteTime));
      }
      else if (filesState[file.path().string()] != fileLastWriteTime)
      {
        // Validar se o arquivo foi atualizado -> mudou a data de atualizacao
        filesState[file.path().string()] = fileLastWriteTime;
        std::string logMessage = "File: " + file.path().string() + " updated!";
        logger.log(logMessage, convert_file_time(fileLastWriteTime));
      }
    }
  }
}


// Criar um map com todos os arquivos do diretorio para validar as mudancas
std::unordered_map<std::string, std::filesystem::file_time_type> DirectoryWatcher::populateFilesMap()
{
  std::unordered_map<std::string, std::filesystem::file_time_type> response;

  for (std::filesystem::directory_entry file : std::filesystem::recursive_directory_iterator(directoryPath))
  {
    response[file.path().string()] = std::filesystem::last_write_time(file);
  }

  return response;
}

std::time_t DirectoryWatcher::convert_file_time(std::filesystem::file_time_type fileTime)
{
  auto systemTime = std::chrono::clock_cast<std::chrono::system_clock>(fileTime);
  return std::chrono::system_clock::to_time_t(systemTime);
}
