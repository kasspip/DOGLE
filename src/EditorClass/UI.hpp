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

	bool							del(GdkEventKey *e);
	void							run();

	// Application panel //
	void							AppInspectorDisplay();
	void							AppInspectorEdit(const Glib::ustring& path_string, const Glib::ustring& new_text);
	void							ButtonNewApp();
	void							ButtonLoadApp();
	void							ButtonSaveApp();

	void							AppPrefabDisplay();
	void							AppPrefabListEdit(const Glib::ustring& path_string, const Glib::ustring& new_text);
	void							AppPrefabSelection();
	void							ButtonNewPrefab();
	void							ButtonDeletePrefab();
	
	void							AppSceneDisplay();
	void							AppSceneListEdit(const Glib::ustring& path_string, const Glib::ustring& new_text);
	void							ButtonNewScene();
	void							ButtonDeleteScene();


	Glib::RefPtr<Gtk::ListStore>	AppListStoreInspector;
	Gtk::TreeView					*AppListStoreInspectorview;

	Gtk::TreeModel::iterator 		AppListStoreGoIt;
	Glib::RefPtr<Gtk::ListStore>	AppListStoreGo;
	Gtk::TreeView					*AppListStoreGoview;

	Gtk::TreeModel::iterator 		AppListStoreSceneIt;
	Glib::RefPtr<Gtk::ListStore>	AppListStoreScene;
	Gtk::TreeView					*AppListStoreSceneview;
	
	Application						*app;

	// Scene panel //
	void							ButtonNewInstance();
	void							ButtonDeleteInstance();



	// GameObject panel //
	void							GoInspectorDispay();
	void							GoInspectorRefresh();
	void							ButtonNewComponent();
	void							ButtonDeleteComponent();
	
	Glib::RefPtr<Gtk::ListStore>	treeGameObjectInspector;
	Gtk::TreeView					*treeViewGameObjectInspector;

	GameObject*						gameObject;

	/*MODELS*/
	myColumn						model;
	ToggleColumn					model2;
};

#endif