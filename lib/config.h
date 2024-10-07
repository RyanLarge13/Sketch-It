#ifndef CONFIG
#define CONFIG

#include <fstream>

class Config {
 public:
  Config();
  ifstream getConfig(const string& configName);

 private:
  bool configExists();
};

#endif