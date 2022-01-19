#include "gtkmm-4.0/gtkmm.h"
#include <iostream>

using namespace std;

namespace
{
Gtk::Window* pDialog = nullptr;
Glib::RefPtr<Gtk::Application> app;

void on_button_clicked()
{
  if (pDialog)
    pDialog->hide(); //hide() will cause Gtk::Application::run() to end.
}

void on_app_activate()
{
  // Load the GtkBuilder file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("spotgtk.glade");
  }
  catch(const Glib::FileError& ex)
  {
    cerr << "FileError: " << ex.what() << endl;
    return;
  }
  catch(const Glib::MarkupError& ex)
  {
    cerr << "MarkupError: " << ex.what() << endl;
    return;
  }
  catch(const Gtk::BuilderError& ex)
  {
    cerr << "BuilderError: " << ex.what() << endl;
    return;
  }

  // Get the GtkBuilder-instantiated dialog:
  pDialog = refBuilder->get_widget<Gtk::Window>("mainwindow");
  if (!pDialog)
  {
    cerr << "Could not get the dialog" << endl;
    return;
  }

  // Get the GtkBuilder-instantiated button, and connect a signal handler:
  auto pButton = refBuilder->get_widget<Gtk::Button>("mainbutton");
  if (pButton)
    pButton->signal_clicked().connect([] () { on_button_clicked(); });

  // It's not possible to delete widgets after app->run() has returned.
  // Delete the dialog with its child widgets before app->run() returns.
  pDialog->signal_hide().connect([] () { delete pDialog; });

  app->add_window(*pDialog);
  pDialog->show();
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