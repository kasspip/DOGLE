#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <gtkmm.h>
#include "../CoreClass/Application.hpp"
#include "Popup.hpp"
#include "myColumn.hpp"
#include <gtkmm/messagedialog.h>

class UI
{
public:
	UI();
	UI(int ac, char **av);
	~UI();
	void							run();
	void							button_new_func();
	void							button_load_func();
	Glib::RefPtr<Gtk::Application>	GtkApp;
	Glib::RefPtr<Gtk::Builder>		builder;
	Gtk::Window						*window;

	/*APPLICATION*/
	Glib::RefPtr<Gtk::ListStore>    AppListStoreInspector;
	Gtk::TreeView					*AppListStoreInspectorview;

	/* DATA */
	Application						*app;


	myColumn						model;
};

#endif