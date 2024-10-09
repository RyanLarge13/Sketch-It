#ifndef CONFIG
#define CONFIG

#include <fstream>
#include <iostream>

#include "json.hpp"

class Config {
 public:
  // Member variables
  enum StatusCodes : int {
    FAILED_CREATE,
    FAILED_READ,
    FAILED_WRITE,
    NEW_USER,
    SUCCESS_READ,
    SUCCESS_WRITE
  };

  bool errorState;
  std::string fileName;
  std::string userData;
  std::string confFilePath;
  std::vector<EventLog> confLog = {3};

  // Constructor
  Config(std::string fileName) : fileName(fileName){};

  // Methods
  EventLog getLogAt(const int& index);
  void setEventLogMessage(const int& status, const std::string& message);
  void clearError(const int& index);
  std::string checkConfig(const std::string& configName);
  std::string getConfigData();
  std::vector<EventLog> getLog();

 private:
  // Member variables
  struct EventLog {
    int status;
    std::string message;
    EventLog(int& s, std::string& m) : status(l), err(m) {}
  };
  nlohmann::json in_UserData;
  // Methods
};

#endif