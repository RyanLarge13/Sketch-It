#ifndef WIN
#define WIN

#include <gtkmm.h>

#include <iostream>

class Win {
 public:
  struct Size {
    int width;
    int height;
    Size(int w, int h) : width(w), height(h) {}
  };

  Win(const std::string& title, const std::string& iconName,
      const Size& defaultSize, const bool& decorated,
      const std::vector<Gtk::Widget*>& children);

  bool decorated;
  Size defaultSize;
  Gtk::Window* window;
  std::vector<Gtk::Widget*> children;
  std::string title;
  std::string iconName;

  bool setChild(const Gtk::Widget*& child);
  void setChildren();
  bool removeChild();
  Gtk::Widget* getChild();

 private:
  void addChildren();
};

#endif