#ifndef TEXT
#define TEXT

#include "gtkmm/label.h"

class Text {
 public:
  Text(const std::string& txt, const std::string& className);
  Gtk::Label* label;

  void changeText(const std::string& txt);

 private:
};

#endif