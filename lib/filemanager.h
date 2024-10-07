#ifndef FiLE_MANAGER
#define FiLE_MANAGER

#include <iostream>

class fileManager {
 public:
  fileManager();
  bool fileExists(const std::string& fileName);
  bool createFile(const std::string& fileName);
  bool createDir(const std::string& dirName);
  bool dirExists(const std::string& dirName);

 private:
};

#endif