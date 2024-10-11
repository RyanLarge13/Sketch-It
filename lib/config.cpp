#include "config.h"

#include <glibmm.h>

#include <iostream>
#include <vector>

#include "json.hpp"

// Constructor
Config::Config(std::string fileName)
    : fileName(fileName),
      errorState(false),
      userData(""),
      confFilePath(""),
      configFileStr(""),
      in_UserData(""),
      confLog() {
  confLog.reserve(3);
  std::string confFullPath = checkConfig(fileName);
  if (confFullPath.empty()) {
    Config::EventLog newLog(Config::StatusCodes::FAILED_CREATE,
        "Configuration file was not found or creation of your configuration "
        "file failed");
    confLog.push_back(newLog);
    errorState = true;
    return;
  }
  confFilePath = confFullPath;
  configFileStr = getConfigData();
  if (configFileStr.empty()) {
    Config::EventLog newLog(
        Config::StatusCodes::NEW_USER, "Welcome to Sketch It!");
    confLog.push_back(newLog);
    return;
  }
  try {
    std::istringstream(configFileStr) >> in_UserData;
  } catch (const nlohmann::json::parse_error& e) {
    std::cout << "Error parsing json config: " << e.what() << std::endl;
    Config::EventLog newLog(Config::StatusCodes::FAILED_READ,
        "Misconfigured file for Sketch It. You can reset the file in your "
        "settings");
    confLog.push_back(newLog);
    errorState = true;
    return;
  }
}

// Constructor methods
std::string Config::checkConfig(const std::string& configName) {
  // std::string configDir = Glib::get_user_config_dir();
  // if (configDir.empty()) {
  //   return "";
  // }
  // std::string configPath = configDir + configName;
  // try {
  //   Glib::make_directory_with_parents(configPath);
  //   return configPath;
  // } catch (const Glib::FileError& e) {
  //   std::cout << "Error creating configuration file for Sketch It, Error: "
  //             << Glib::strerror(e.code()) << "\n";
  //   return "";
  // }
  return "";
}

// Getters
std::string Config::getConfigData() {
  std::string userConfigData;
  std::ifstream configFile(confFilePath);
  if (!configFile.is_open()) {
    return "";
  }
  std::string line;
  while (std::getline(configFile, line)) {
    userConfigData += line + "\n";
  }
  if (configFile.fail()) {
    return "";
  }
  configFile.close();
  return userConfigData;
}

Config::EventLog Config::getLogAt(const int& index) {
  if (index < 0 || index >= confLog.size()) {
    throw std::out_of_range(
        "Cannot access configuration event log with out of bounds index");
  }
  return confLog[ index ];
}

std::vector<Config::EventLog> Config::getLog() { return confLog; }

// Setters
void Config::setEventLogMessage(const int& status, const std::string& message) {
  if (status < 0 || status > 5) {
    std::cout << "Please pass a valid Config::StatusCode between 0 and 5"
              << "\n";
    return;
  }
  Config::EventLog newLog(static_cast<Config::StatusCodes>(status), message);
  confLog.push_back(newLog);
}

void Config::clearError(const int& index) {
  if (index < 0 || index >= confLog.size()) {
    std::cout << "Invalid index for removing Config event log value. "
                 "Index: "
              << index << "\n";
  }
  confLog.erase(confLog.begin() + index);
}

void Config::clearAllErrors() { confLog = {}; }