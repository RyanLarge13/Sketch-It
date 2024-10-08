#ifndef CONFIG
#define CONFIG

#include <fstream>
#include <iostream>

class Config {
 public:
  // Member variables
  bool errState;
  std::string fileName;
  std::string userData;
  std::string confFilePath;
  std::vector<ErrorMessage> confErrors = {3};

  // Constructor
  Config(std::string fileName) : fileName(fileName) {};

  // Methods
  checkConfig(const std::string& configName);
  std::string getConfigData();
  std::vector<ErrorMessage> getErrors();
  void setErrorMessage(const int& severity, const std::string& errorMessage);
  void clearErrors(const int& index);
  bool getErrorState();

 private:
  // Member variables
  struct ErrorMessage {
    int level int num std::string err;
    ErrorMessage(int& l, int& n, std::string& e) : level(l), num(n), err(e) {}
  };

  // Methods
};

#endif