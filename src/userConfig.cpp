#include "../includes/userConfig.h"

#include <iostream>

UserConfig::UserConfig() { std::cout << "I am a users config manager" << "\n"; }

void UserConfig::loadConfig() {
  std::cout
      << "I am loading the configuration file saved be the last user or "
         "creating one if it does not exist and displaying a welcome message"
      << "\n";
}