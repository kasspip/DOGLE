#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <gtkmm.h>
#include "../CoreClass/Application.hpp"
# include "../CoreClass/GameObject.hpp"
#include "Popup.hpp"
#include "myColumn.hpp"
#include "ToggleColumn.hpp"
#include <gtkmm/messagedialog.h>
#include <gdk/gdkkeysyms.h>

#include "Builder.hpp"
#include "Engine.hpp"
#include "DOGLE.hpp"

class UI
{
public:
	UI();
	UI(Application *app);
	~UI();

	Glib::RefPtr<Gtk::Application>	GtkApp;
	Glib::RefPtr<Gtk::Builder>		builder;
	Gtk::Window						*window;

	void							EditList(const Glib::ustring& path_string, const Glib::ustring& new_text);

	bool							del(GdkEventKey *e);

	void							displayApp();
	void							displayGo();
	void							displayScene();

	void							run();

	/*BUTTONS_CALLBACK*/
	void							button_new_func();
	void							button_load_func();
	void							button_save_func();
	void							button_GoNew_func();
	void							button_SceneNew_func();
	void							button_SceneInstanciateButton_func();
	void							button_GameObjectNewButton_func();

	/*APPLICATION*/
	Glib::RefPtr<Gtk::ListStore>	AppListStoreInspector;
	Gtk::TreeView					*AppListStoreInspectorview;

	Gtk::TreeModel::iterator 		AppListStoreGoIt;
	Glib::RefPtr<Gtk::ListStore>	AppListStoreGo;
	Gtk::TreeView					*AppListStoreGoview;

	Gtk::TreeModel::iterator 		AppListStoreSceneIt;
	Glib::RefPtr<Gtk::ListStore>	AppListStoreScene;
	Gtk::TreeView					*AppListStoreSceneview;

	/*MODELS*/
	myColumn						model;
	ToggleColumn					model2;

	/* DATA */
	Application						*app;
};

#endif