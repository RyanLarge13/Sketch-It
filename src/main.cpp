#include <gtkmm.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../lib/config.h"
#include "../widgets/CustomWindow.h"
#include "../widgets/ErrorModal.h"

class MyWindow : public Gtk::Window {
 public:
  MyWindow() {
    set_title("Sketch it");
    signal_realize().connect(
        sigc::mem_fun(*this, &MyWindow::setDefaultScreenSize));
    applyGlobalCSS();
    Config configManager("/sketch-it/config.json");
    if (configManager.errorState) {
      Config::EventLog error = configManager.getLogAt(0);
      ErrorModal newError("Configuration Error", error.message);
      newError.addBtns(std::vector<ErrorModal::ErrorModalButtons>{
          ErrorModal::ErrorModalButtons(
              "Okay", 0, [ this ]() { this->close(); }),
          ErrorModal::ErrorModalButtons(
              "Reload App", 1, [ this ]() { this->reloadApp(); })});
      newError.errorModal.show();
      configManager.clearAllErrors();
      return;
    }
    setUpApp();
  }

 private:
  Glib::RefPtr<Gtk::CssProvider> css_provider;
  std::pair<int, int> dems = std::make_pair(1250, 900);
  std::string sessionName = "Untitled Session";

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

  void setUpApp() {
    // std::vector<Gtk::Widget*> children = {{}};
    // CustomWindow::Size size(600, 600);
    // CustomWindow setUp("Set Up", "./my-setup-icon", size, true,
    // setUpChildren);
  }

  void reloadApp() {
    this->close();
    Glib::signal_timeout().connect_once(
        []() {
          auto app = Gtk::Application::create("org.gtkmm.example");
          MyWindow newWindow;
          app->make_window_and_run<MyWindow>(0, nullptr);
        },
        100);
  }
};

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.example");
  return app->make_window_and_run<MyWindow>(argc, argv);
}
