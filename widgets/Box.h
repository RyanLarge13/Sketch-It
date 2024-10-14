#ifndef BOX
#define BOX

#include "gtkmm.h"

class Box {
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
    BoxProps(const std::vector<Gtk::Widget*>& children, const bool& hexpand,
        const bool& vexpand, const int& spacing, const Gtk::Align& valign,
        const Gtk::Align& halign, const std::string& className,
        const Gtk::Orientation& orientation)
        : children(children),
          hexpand(hexpand),
          vexpand(vexpand),
          halign(halign),
          valign(valign),
          className(className),
          orientation(orientation) {}
  };

  Box(const BoxProps& props);

  Gtk::Box* box;

 private:
};

#endif