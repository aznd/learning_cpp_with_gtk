#include "gtkmm-4.0/gtkmm.h"
#include <iostream>

using namespace std;


namespace
{
Gtk::Window* pWindow = nullptr;
Glib::RefPtr<Gtk::Application> app;
Gtk::VolumeButton *mainvolume;

void on_button_clicked()
{
  cout << "You clicked me." << endl;
  cout << mainvolume->get_value();
}

void call_exec(int plusorminus)
{
  if (plusorminus == 0)
  {
    system("pactl set-sink-volume 0 +3%");
  }
  else{
    system("pactl set-sink-volume 0 -3%");
  }
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

  Gtk::Box *mainbox = refBuilder->get_widget<Gtk::Box>("mainbox");
  Gtk::ListBox *mainlist = refBuilder->get_widget<Gtk::ListBox>("newlist");
  mainvolume = refBuilder->get_widget<Gtk::VolumeButton>("cool");

  Gtk::Adjustment *adj;
  adj->set_step_increment(0.1);
  // HELP I DONT GET THIS IT LITERALLY IS A GTK::ADJUSTMENT
  mainvolume->set_adjustment(adj);


  // Get the plus/minus buttons from the volume widget and attach a signal handler
  Gtk::Button *plusbtn = mainvolume->get_plus_button();
  plusbtn->signal_clicked().connect([] () { call_exec(0); });

  Gtk::Button *minusbtn = mainvolume->get_minus_button();
  minusbtn->signal_clicked().connect([] () { call_exec(1); });

  // Correct way to programtically create a widget.
  Gtk::Label *newtextlabel = Gtk::manage(new Gtk::Label("other"));
  newtextlabel->set_text("Test");
  mainlist->append(*newtextlabel);

  // Get the GtkBuilder-instantiated button, and connect a signal handler:
  Gtk::Button *pButton = refBuilder->get_widget<Gtk::Button>("clickme");
  if (pButton)
    pButton->signal_clicked().connect([] () { on_button_clicked(); });

  app->add_window(*pWindow);
  pWindow->show();
  pWindow->set_default_size(900, 500);
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