#include "config.h"

#include <glibmm>
#include <iostream>

#include "fileManager.h"

// Constructor
Config::Config(std::string fileName, bool errState) : fileName(fileName) {
  std::string confFullPath = checkConfig(fileName);
  if (confFullPath.empty()) {
    errState = true;
    Config::ErrorMessage newError = {1, static_cast<int>(confErrors.size()),
        "Configuration file was not found or creation of your configuration "
        "file failed"};
    confErrors.push_back(newError);
  }
  if (!confFullPath.empty()) {
    confFilePath = confFullPath;
    userData = getConfigData();
    // JSON validate data here
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

std::vector<Config::ErrorMessage> Config::getErrors() { return confErrors; }

bool Config::getErrorState() { return errState; }

// Setters
void Config::setErrorMessage(
    const int& severity, const std::string& errorMessage) {
  Config::ErrorMessage newMessage = {
      severity, static_cast<int>(confErrors.size()), errorMessage};
  confErrors.push_back(newMessage);
}