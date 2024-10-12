#ifndef C_BUTTON
#define C_BUTTON

#include "gtkmm.h"

class C_Button {
 public:
  struct BtnProps {
    bool hexpand;
    bool vexpand;
    Gtk::Align valign;
    Gtk::Align halign;
    std::string className;

    BtnProps(const bool& hexpand, const bool& vexpand, const Gtk::Align& valign,
        const Gtk::Align& halign, const std::string& className)
        : hexpand(hexpand),
          vexpand(vexpand),
          valign(valign),
          halign(halign),
          className(className) {}
  };

  C_Button(const std::string& text, const BtnProps& props,
      const std::function<void()>& clickFunc);

  Gtk::Button* button;

 private:
};

#endif