/*
Sketch It - A learn to draw program
Copyright (C) 2024 Ryan Large

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "Config.h"

#include <glib.h>
#include <glibmm.h>

#include <iostream>
#include <vector>

#include "../lib/json.hpp"

// Constructor
namespace SketchItApplication {
namespace Files {
ConfigManager::ConfigManager(const std::string& fileName)
    : fileName(fileName),
      errorState(false),
      userData(""),
      confFilePath(""),
      configFileStr(""),
      in_UserData(""),
      confLog() {
  confLog.reserve(3);
  // Check for config file. Create if not there
  std::string confFullPath = checkConfig(fileName);

  // Append error logs to config logs
  if (confFullPath.empty()) {
    ConfigManager::EventLog newLog(ConfigManager::StatusCodes::FAILED_CREATE,
        "Configuration file was not found or creation of your configuration "
        "file failed");
    confLog.push_back(newLog);
    errorState = true;
    return;
  }

  // Load config data from file
  confFilePath = confFullPath;
  configFileStr = getConfigData();

  // Add more logs to config log
  if (configFileStr.empty()) {
    ConfigManager::EventLog newLog(
        ConfigManager::StatusCodes::NEW_USER, "Welcome to Sketch It!");
    confLog.push_back(newLog);
    return;
  }

  // Parse configuration load it into app memory log if failed
  try {
    std::istringstream(configFileStr) >> in_UserData;
  } catch (const nlohmann::json::parse_error& e) {
    std::cout << "Error parsing json config: " << e.what() << std::endl;
    ConfigManager::EventLog newLog(ConfigManager::StatusCodes::FAILED_READ,
        "Misconfigured file for Sketch It. You can reset the file in your "
        "settings");
    confLog.push_back(newLog);
    errorState = true;
    return;
  }
}

std::string ConfigManager::checkConfig(const std::string& configName) {
  // Load config file. create if not exists. return "" if fall fails
  std::string configDir = Glib::get_user_config_dir();

  if (configDir.empty()) {
    return "";
  }

  std::string configPath = configDir + configName;

  try {
    gint result = g_mkdir_with_parents(configPath.c_str(), 0755);
    if (result == -1) {
      return "";
    }
    // return "";
    return configPath;
  } catch (const Glib::FileError& e) {
    std::cout << "Error creating configuration file for Sketch It, Error: "
              << Glib::strerror(e.code()) << "\n";
    return "";
  }

  return "";
}

std::string ConfigManager::getConfigData() {
  // Return config file raw data as string return "" if all fails
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

ConfigManager::EventLog ConfigManager::getLogAt(const int& index) {
  if (index < 0 || index >= confLog.size()) {
    throw std::out_of_range(
        "Cannot access configuration event log with out of bounds index");
  }

  return confLog[ index ];
}

std::vector<ConfigManager::EventLog> ConfigManager::getLog() { return confLog; }

void ConfigManager::setEventLogMessage(
    const int& status, const std::string& message) {
  if (status < 0 || status > 5) {
    std::out_of_range(
        "Please pass a valid ConfigManager::StatusCode between 0 and 5");
    return;
  }

  // Append new log
  ConfigManager::EventLog newLog(
      static_cast<ConfigManager::StatusCodes>(status), message);
  confLog.push_back(newLog);
}

void ConfigManager::clearError(const int& index) {
  if (index < 0 || index >= confLog.size()) {
    std::cout << "Invalid index for removing Config event log value. "
                 "Index: "
              << index << "\n";
  }

  // Remove log by index
  confLog.erase(confLog.begin() + index);
}

void ConfigManager::clearAllErrors() { confLog = {}; }

}  // namespace Files
}  // namespace SketchItApplication