#ifndef CONFIG
#define CONFIG

#include <fstream>
#include <vector>

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

  struct EventLog {
    StatusCodes status;
    std::string message;
    EventLog(StatusCodes s, std::string m) : status(s), message(m) {}
  };

  bool errorState;
  std::string fileName;
  std::string userData;
  std::string confFilePath;
  std::string configFileStr;
  std::vector<EventLog> confLog;
  nlohmann::json in_UserData;

  // Constructor
  Config(std::string fileName);

  // Methods
  EventLog getLogAt(const int& index);
  void setEventLogMessage(const int& status, const std::string& message);
  void clearError(const int& index);
  void clearAllErrors();
  std::string checkConfig(const std::string& configName);
  std::string getConfigData();
  std::vector<EventLog> getLog();

 private:
  // Member variables
  // Methods
};

#endif