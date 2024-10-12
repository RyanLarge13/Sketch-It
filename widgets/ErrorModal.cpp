#include "ErrorModal.h"

#include <gtkmm.h>

#include <iostream>

// Constructor methods
ErrorModal::ErrorModal(const std::string& t, const std::string& m)
    : title(t), message(m) {
  errorModal = Gtk::Window();
  errorModal.add_css_class("error-modal");
  errorModal.set_title(title);
  errorModal.set_decorated(false);
  addLabel();
}

void ErrorModal::addLabel() {
  Gtk::Label* errorLabel = Gtk::make_managed<Gtk::Label>(message);
  errorLabel->add_css_class("error-modal-label");
  errorModal.set_child(*errorLabel);
}

// Public

void ErrorModal::addBtns(
    const std::vector<ErrorModal::ErrorModalButtons>& btns) {
  buttons = btns;
  Gtk::Box* btnHolder =
      Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  btnHolder->add_css_class("error-modal-btn-holder");
  for (ErrorModal::ErrorModalButtons btn : buttons) {
    Gtk::Button* newBtn = Gtk::make_managed<Gtk::Button>(btn.txt);
    newBtn->add_css_class("error-modal-btn");
    newBtn->signal_clicked().connect([ btn ]() { btn.func(); });
    btnHolder->append(*newBtn);
  }
  errorModal.set_child(*btnHolder);
}

// Private