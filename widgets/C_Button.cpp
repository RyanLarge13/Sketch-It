#include "C_Button.h"

#include <iostream>

#include "gtkmm.h"

C_Button::C_Button(const std::string& text, const C_Button::BtnProps& props,
    const std::function<void()>& clickFunc) {
  button = Gtk::make_managed<Gtk::Button>(text);
  button->set_hexpand(props.hexpand);
  button->set_vexpand(props.vexpand);
  button->set_halign(props.halign);
  button->set_valign(props.valign);
  button->add_css_class(props.className);
  button->signal_clicked().connect([ clickFunc ]() { clickFunc(); });
  sigevent();
}