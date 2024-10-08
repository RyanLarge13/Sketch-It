#ifndef CONFIG
#define CONFIG

#include <fstream>
#include <iostream>

class Config {
 public:
  Config();
  std::string checkConfig(const std::string& configName);
  void getConfigRead(const std::string& pathToConf);

 private:
};

#endif