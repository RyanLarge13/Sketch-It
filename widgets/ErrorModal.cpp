#include "ErrorModal.h"

#include <gtkmm.h>

#include <iostream>

#include "Btn.h"

// Constructor methods
ErrorModal::ErrorModal(const std::string& t, const std::string& m)
    : title(t), message(m) {
  errorModal = Gtk::make_managed<Gtk::Window>();
  container = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  container->set_valign(Gtk::Align::CENTER);
  errorModal->set_default_size(600, 400);
  errorModal->add_css_class("error-modal");
  errorModal->set_title(title);
  addLabel();
  errorModal->set_child(*container);
  errorModal->set_focusable(true);
  errorModal->show();
  errorModal->present();
  errorModal->grab_focus();
}

void ErrorModal::addLabel() {
  Gtk::Label* modalLabel = Gtk::make_managed<Gtk::Label>(message);
  modalLabel->add_css_class("error-modal-label");
  container->append(*modalLabel);
}

// Public

void ErrorModal::addBtns(
    const std::vector<ErrorModal::ErrorModalButtons>& btns) {
  buttons = btns;
  Gtk::Box* btnHolder =
      Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  btnHolder->set_hexpand(true);
  btnHolder->set_vexpand(true);
  btnHolder->set_valign(Gtk::Align::CENTER);
  btnHolder->add_css_class("error-modal-btn-holder");
  for (ErrorModal::ErrorModalButtons btn : buttons) {
    Btn::BtnProps props(
        true, false, Gtk::Align::FILL, Gtk::Align::FILL, "error-modal-btn");
    Btn newBtn(btn.txt, props, btn.func);
    btnHolder->append(*newBtn.button);
  }
  container->append(*btnHolder);
}

// Private