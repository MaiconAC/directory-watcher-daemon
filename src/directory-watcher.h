#ifndef DIRECTORY_WATCHER_H
#define DIRECTORY_WATCHER_H

#include <string>
#include <unordered_map>
#include <time.h>
#include <filesystem>

class DirectoryWatcher
{
  public:
    DirectoryWatcher(std::string t_directoryPath);

    void start();

    std::time_t convert_file_time(std::filesystem::file_time_type fileTime);

  private:
    std::string directoryPath;
    bool running;
    std::unordered_map<std::string, std::filesystem::file_time_type> filesState;

    std::unordered_map<std::string, std::filesystem::file_time_type> populateFilesMap();
};

#endif
