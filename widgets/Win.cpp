#include "Win.h"

#include <gtkmm.h>

#include <vector>
// Constructor methods
Win::Win(const std::string& title, const std::string& iconName,
    const Win::Size& defaultSize, const bool& decorated,
    const std::vector<Gtk::Widget*>& children)
    : title(title),
      iconName(iconName),
      defaultSize(defaultSize),
      decorated(decorated),
      children(children) {
  window = Gtk::make_managed<Gtk::Window>();
  window->set_default_size(defaultSize.width, defaultSize.height);
  window->set_title(title);
  window->set_decorated(decorated);
  window->set_focusable(true);
  window->show();
  window->present();
  window->grab_focus();
  addChildren();
}

// Public methods

bool Win::setChild(const Gtk::Widget*& child) { return false; };

void Win::setChildren() {
  for (Gtk::Widget* child : children) {
    window->set_child(*child);
  }
}

bool Win::removeChild() { return false; }

// Gtk::Widget* Window::getChild() { return Gtk::Widget(); }

// Private methods

void Win::addChildren() {
  for (Gtk::Widget* widget : children) {
    window->set_child(*widget);
  }
}