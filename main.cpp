#include "gtkmm-4.0/gtkmm.h"
#include <iostream>

using namespace std;

namespace
{
Gtk::Window* pWindow = nullptr;
Glib::RefPtr<Gtk::Application> app;

void on_button_clicked()
{
  cout << "You clicked me." << endl;
}

void on_app_activate()
{
  // Load the GtkBuilder file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file("spotgtk.glade");

  // Get the main window
  pWindow = refBuilder->get_widget<Gtk::Window>("mainwindow");
  if (!pWindow)
  {
    cerr << "Could not get the main window." << endl;
    return;
  }

  auto treeview = refBuilder->get_widget<Gtk::Widget>("treeview");

  // Get the GtkBuilder-instantiated button, and connect a signal handler:
  auto pButton = refBuilder->get_widget<Gtk::Button>("clickme");
  if (pButton)
    pButton->signal_clicked().connect([] () { on_button_clicked(); });

  app->add_window(*pWindow);
  pWindow->show();
}
} // anonymous namespace

int main(int argc, char** argv)
{
  app = Gtk::Application::create("org.gtkmm.example");

  // Instantiate a dialog when the application has been activated.
  // This can only be done after the application has been registered.
  // It's possible to call app->register_application() explicitly, but
  // usually it's easier to let app->run() do it for you.
  app->signal_activate().connect([] () { on_app_activate(); });

  return app->run(argc, argv);
}