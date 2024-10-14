#include "Box.h"

#include <iostream>

#include "gtkmm.h"

Box::Box(const Box::BoxProps& props) {
  box = Gtk::make_managed<Gtk::Box>(props.orientation, props.spacing);
  box->set_hexpand(props.hexpand);
  box->set_vexpand(props.vexpand);
  box->set_valign(props.valign);
  box->set_halign(props.halign);
  box->add_css_class(props.className);
  std::cout << props.children.size();
  for (Gtk::Widget* widget : props.children) {
    if (widget) {
      box->append(*widget);
    }
  }
}