#include "config.h"

#include <iostream>

#include "fileManager.h"

Config::Config() { this.fileManager = FileManager fileManager; }

Config::getConfig(const std::string& configName) {
  bool configExists = this.fileManager.fileExists(configName);
  if (!configExists) {
    ifstream newConfig = this.fileManager.createFile(configName);
  }
}