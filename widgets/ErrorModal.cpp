#include <gtkmm.h>

#include <iostream>

// Constructor methods
ErrorModal::ErrorModal(const std::string& title, const std::string& message,
    const std::vector<ErrorModal::ErrorModalButtons>& buttons) {
  errorModal = Gtk::Window();
  errorModal.add_css_class("error-modal");
  errorModal.set_title(title);
  addLabel();
  addBtns();
}

ErrorModal::ErrorModalButtons::ErrorModalButtons(
    const std::string& txt, int id, void (*func)())
    : text(txt), id(id), func(func) {}

void ErrorModal::addLabel() {
  Gtk::Label* errorLabel = Gtk::make_managed<Gtk::Label>(message);
  errorLabel->add_css_class("error-modal-label");
  errorModal.set_child(errorLabel);
}

void ErrorModal::addBtns() {
  Gtk::Box* btnHolder =
      Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION::HORIZONTAL, 10);
  btnHolder->add_css_class("error-modal-btn-holder");
  for (ErrorModal::ErrorModalButtons btn : buttons) {
    Gtk::Button* newBtn = Gtk::make_managed<Gtk::button>(btn.text);
    newBtn->add_css_class("error-modal-btn");
    newBtn->signal_clicked().connect(sigc::mem_fun(&this, btn.func));
    btnHolder->append(newBtn);
  }
  errorModal.set_child(btnHolder);
}

// Public

// Private