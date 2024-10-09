#include "./MessageDialog.h"

#include <gtkmm.h>

#include <iostream>

MessageDialog::MessageDialog(const std::string& message, const bool& err,
    const void() & action, const std::string& cancelString,
    const std::string& acceptString, const int& defaultRes)
    : defaultAction(action),
      message(message),
      err(err),
      acceptString(acceptString),
      cancelString(cancelString),
      defaultRes(defaultRes) {
  dialogWidget = Gtk::make_managed<Gtk::Dialog>(message);
  dialogWidget.add_button(cancelString, 0);
  dialogWidget.add_button(acceptString, 1);
  dialogWidget.set_default_response(defaultRes);
  if (err) {
    dialogWidget.get_style_context().set_style("dialog-error");
  };
}

Gtk::Dialog* MessageDialog::getDialogWidget() {
  return *dialogWidget || nullptr;
}
