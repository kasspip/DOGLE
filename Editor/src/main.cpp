#include "WindowClass.hpp"
#include <gtkmm/main.h>

int
main(int ac, char **av)
{
	Gtk::Main	app(ac, av);
	Window		win;

	Gtk::Main::run(win);
	return 0;
}
