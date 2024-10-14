#include "Text.h"

Text::Text(const std::string& txt, const std::string& className) {
  label = Gtk::make_managed<Gtk::Label>(txt);
  label->add_css_class(className);
}

void Text::changeText(const std::string& txt) {}