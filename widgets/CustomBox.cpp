#include "CustomBox.h"

#include "gtkmm.h"

CustomBox::CustomBox(const CustomBox::BoxProps& props) {
  box = Gtk::make_managed<Gtk::Box>(props.orientation, props.spacing);
  box->set_hexpand(props.hexpand);
  box->set_vexpand(props.vexpand);
  box->set_valign(props.valign);
  box->set_halign(props.halign);
  box->add_css_class(props.className);
  for (Gtk::Widget* widget : props.children) {
    box->append(*widget);
  }
}