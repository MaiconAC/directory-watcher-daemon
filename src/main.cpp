#include <iostream>
#include <unistd.h>

#include "directory-watcher.h"

int main()
{
  DirectoryWatcher dirWatcher("/home/mcunico/Templates/");
  dirWatcher.start();

  return 0;
};
