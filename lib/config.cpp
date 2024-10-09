#include "config.h"

#include <glibmm>
#include <iostream>

#include "fileManager.h"
#include "json.hpp"

// Constructor
Config::Config(std::string fileName) : fileName(fileName) {
  std::string confFullPath = checkConfig(fileName);
  if (confFullPath.empty()) {
    Config::EventLog newError = {Config::StatusCodes::FAILED_CREATE,
        "Configuration file was not found or creation of your configuration "
        "file failed"};
    confLog.push_back(newError);
    errorState = true;
    return;
  }
  confFilePath = confFullPath;
  configFileStr = getConfigData();
  if (configFileStr.empty()) {
    Config::EventLog newMessage = {
        Config::StatusCodes::NEW_USER, "Welcome to Sketch It!"};
    confLog.push_back(newMessage);
    return;
  }
  try {
    configFileStr >> in_UserData;
  } catch (const nlohmann::json::parse_error& e) {
    std::cout << "Error parsing json config: " << e.what() << std::endl;
    Config::EventLog newError = {Config::StatusCodes::FAILED_READ,
        "Misconfigured file for Sketch It. You can reset the file in your "
        "settings"};
    errorState = true;
    return;
  }
}

// Constructor methods
std::string Config::checkConfig(const std::string& configName) {
  auto configDir = Glib::get_user_config_dir();
  if (!configDir) {
    return "";
  }
  std::string configPath = configDir + configName;
  try {
    Glib::mkdir_with_parents(configPath);
    return configPath;
  } catch (const Glib::FileError& e) {
    std::cout << "Error creating configuration file for Sketch It, Error: "
              << e.what() << endl;
    return "";
  }
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
  if (configFile.fail() || configFile.eof()) {
    return "";
  }
  configFile.close();
  return userConfigData;
}

Config::EventLog& Config::getLogAt(const int& index) {
  if (index < 0 || index > confLog.size()) {
    throw std::out_of_range(
        "Cannot access configuration event log with out of bounds index");
  }
  return confLog[ index ];
}

std::vector<Config::EventLog> Config::getLog() { return confLog; }

// Setters
void Config::setEventLogMessage(
    const int& severity, const std::string& message) {
  Config::EventLog newMessage = {StatusCodes::severity, message};
  confLog.push_back(newMessage);
}

void Config::clearError(const int& index) {
  confLog.erase(confLog.begin() + index);
}