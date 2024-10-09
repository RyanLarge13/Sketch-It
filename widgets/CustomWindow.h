#ifndef CUSTOM_WINDOW
#define CUSTOM_WINDOW

#include <gtkmm.h>

#include <iostream>

class CustomWindow : Gtk::Window {
  CustomWindow(const std::string& title, const std::string& iconName,
      const Size& defaultSize, const bool& decorated,
      std::vector<Gtk::widget*> children);

 public:
  // Member variables
  struct Size {
    int height;
    int width;
    Size(w, h) : width(w), height(h) {}
  };
  // Methods
  bool setChild();
  bool setChildren(const std::vector<Gtk::Widget*>& children);
  bool removeChild();
  Gtk::Widget* getChild();
  Gtk::Window* getWindow();

 private:
  // Constructor methods
  // Member variables
  bool decorated;
  Size defaultSize;
  Gtk::Window* window;
  std::vector<Gtk::Widget*> children;
  std::string title;
  std::string iconName;
  // Methods
};

#endif