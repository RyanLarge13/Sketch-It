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

#ifndef CONFIG
#define CONFIG

#include <fstream>
#include <vector>

#include "../lib/json.hpp"

namespace SketchItApplication {
namespace Files {
class ConfigManager {
 public:
  ConfigManager(const std::string& fileName);
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

  EventLog getLogAt(const int& index);
  void setEventLogMessage(const int& status, const std::string& message);
  void clearError(const int& index);
  void clearAllErrors();
  std::string checkConfig(const std::string& configName);
  std::string getConfigData();
  std::vector<EventLog> getLog();

 protected:
 private:
};
}  // namespace Files
}  // namespace SketchItApplication

#endif