#ifndef ERROR_MODAL
#define ERROR_MODAL

#include <gtkmm.h>

#include <iostream>

class ErrorModal {
  ErrorModal(const std::string& t, const std::string& m,
      const std::vector<ErrorModalButtons>& b)
      : title(t), message(m), buttons(b) {}

 public:
  // Member variables
  struct ErrorModalButtons {
    std::string txt;
    int id;
    void (*func)();
    ErrorModalButtons(std::string txt, int id, void (*func)())
        : text(txt), id(id), func(func) {}
  };

 private:
  // Member variables
  std::string title;
  std::string message;
  std::vector<ErrorModalButtons> buttons;
  Gtk::Window errorModal;

  // Methods
  void addBtns();
  void addLabel();
};

#endif