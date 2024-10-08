#include "config.h"

#include <glibmm>
#include <iostream>

#include "fileManager.h"

struct ErrorMessages {
  int level int num std::string err;
  ErrorMessages() : level(level), num(num), err(err) {}
};

Config::Config(std::string fileName, bool errState) : errState(errState) {
  std::string confFullPath = checkConfig(fileName);
  std::vector<ErrorMessages> errors;
  if (!confFullPath) {
    errState = true;
    ErrorMessages newError = {1, errors.size(),
        "Configuration file was not found or creation of your configuration "
        "file failed"};
    errors.push_back(newError);
  }
}

void Config::getConfigRead(const std::string& pathToConf) {
  std::string userConfigData;
  ifstream configFile = std::filesystem::file(pathToConf);
  if (!configFile.is_open()) {
    // Do somethings
    return;
  }
  while (std::get_line(configFile, line)) {
    userConfigData += line + "\n";
  }
  file.close();
  // What should I return from this function
  // How should I handle errors from main?
  return;
}

std::string Config::checkConfig(const std::string& configName) {
  auto configDir = Glib::get_user_config_dir();
  if (!configDir) {
    return "";
  }
  std::string configPath = configDir + configName;
  try {
    Glib::mkdir_with_parents(configPath);
    return configPath;
  } catch (const Glib::error& err) {
    std::cout << "Could not create configuration file for sketch it. Error: "
              << err.what() << endl;
    return "";
  }
  return "";
}

// Getters

bool getErrorState() { return errState; }

std::vector<ErrorMessages> getErrors() { return errors; }

// Setters