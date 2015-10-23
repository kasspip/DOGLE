#ifndef UI_HPP
#define UI_HPP

#include <gtkmm.h>

class UI
{
public:
	UI();
	UI(int ac, char **av);
	~UI();
	void							run();
	void							new_button_func();
	Glib::RefPtr<Gtk::Application>	app;
	Glib::RefPtr<Gtk::Builder>		builder;
	Gtk::Window						*window;
	
};

#endif