#include <gtkmm.h>

#include <fstream>
#include <iostream>

#include "../lib/config.h"

class MyWindow : public Gtk::Window {
 public:
  MyWindow() {
    set_title("Sketch it");
    signal_realize().connect(
        sigc::mem_fun(*this, &MyWindow::setDefaultScreenSize));
    applyGlobalCSS();
    pullConfig();
  }

 private:
  enum APP_STATE { FREE_DRAW, STORY, SETUP, SETTINGS, ABOUT };
  Glib::RefPtr<Gtk::CssProvider> css_provider;
  std::pair<int, int> dems = std::make_pair(1250, 900);

  void setDefaultScreenSize() {
    auto display = Gdk::Display::get_default();
    if (!display) {
      set_default_size(dems.first, dems.second);
      return;
    }
    auto monitor = display->get_monitor_at_surface(get_surface());
    if (!monitor) {
      set_default_size(dems.first, dems.second);
      return;
    }
    Gdk::Rectangle monitor_geometry;
    monitor->get_geometry(monitor_geometry);
    const size_t width = monitor_geometry.get_width();
    const size_t height = monitor_geometry.get_height();
    set_default_size(width, height);
    dems.first = width;
    dems.second = height;
  }

  void applyGlobalCSS() {
    css_provider = Gtk::CssProvider::create();
    try {
      css_provider->load_from_path("../styles/global.css");
    } catch (const Glib::Error& err) {
      std::cerr << "Error loading css files: " << err.what() << "\n";
    }
    auto display = Gdk::Display::get_default();
    Gtk::StyleContext::add_provider_for_display(
        display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  }

  void pullConfig() {}
};

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.example");
  MyWindow window;
  return app->make_window_and_run<MyWindow>(argc, argv);
}
