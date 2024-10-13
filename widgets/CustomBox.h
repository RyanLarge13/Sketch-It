#ifndef CUSTOM_BOX
#define CUSTOM_BOX

#include "gtkmm.h"

class CustomBox {
 public:
  struct BoxProps {
    std::vector<Gtk::Widget*> children;
    bool hexpand;
    bool vexpand;
    int spacing;
    Gtk::Align valign;
    Gtk::Align halign;
    std::string className;
    Gtk::Orientation orientation;
    BoxProps()
        : children(children),
          hexpand(hexpand),
          vexpand(vexpand),
          halign(halign),
          valign(valign),
          className(className),
          orientation(orientation) {}
  };

  CustomBox(const BoxProps& props);

  Gtk::Box* box;

 private:
};

#endif