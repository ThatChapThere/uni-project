#include "myarea.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();

protected:
  MyArea m_area;
};

ExampleWindow::ExampleWindow()
{
  set_title("DrawingArea");
  set_child(m_area);
}

int main(int argc, char** argv)
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  return app->make_window_and_run<ExampleWindow>(argc, argv);
}
