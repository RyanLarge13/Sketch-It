#ifndef MESSAGE_DIALOG
#define MESSAGE_DIALOG

#include <gtkmm.h>

#include <iostream>

class MessageDialog : Gtk::Dialog {
 public:
  // Constructor methods
  MessageDialog(const std::string& message, const bool& err,
      const void() & action, const std::string& cancelString,
      const std::string& acceptString);
  // Member variables
  // Methods
  Gtk::Dialog* getDialogWidget();

 private:
  void(*action());
  bool err;
  int defaultRes;
  std::string message;
  std::string acceptString;
  std::string cancelString;
  Gtk::Dialog dialogWidget;
};

#endif