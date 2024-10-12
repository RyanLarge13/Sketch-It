#ifndef ERROR_MODAL
#define ERROR_MODAL

#include <gtkmm.h>

#include <iostream>
#include <vector>

class ErrorModal {
 public:
  // Constructor
  ErrorModal(const std::string& t, const std::string& m);
  // Member variables
  struct ErrorModalButtons {
    std::string txt;
    int id;
    std::function<void()> func;
    ErrorModalButtons(std::string txt, int id, std::function<void()> func)
        : txt(txt), id(id), func(func) {}
  };
  std::string title;
  std::string message;
  std::vector<ErrorModalButtons> buttons;
  Gtk::Window errorModal;

  // Methods
  void addBtns(const std::vector<ErrorModalButtons>& btns);

 private:
  // Member variables

  // Methods
  void addLabel();
};

#endif