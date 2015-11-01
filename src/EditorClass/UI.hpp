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
	/*MODELS*/
	myColumn						model;
	ToggleColumn					model2;

	bool							del(GdkEventKey *e);
	void							run();

	// Application panel //
	void							AppInspectorDisplay();
	void							AppInspectorEdit(const Glib::ustring& index, const Glib::ustring& value);
	void							ButtonNewApp();
	void							ButtonLoadApp();
	void							ButtonSaveApp();

	void							AppPrefabDisplay();
	void							AppPrefabRefresh();
	void							AppPrefabListEdit(const Glib::ustring& index, const Glib::ustring& value);
	void							AppPrefabSelection();
	void							ButtonNewPrefab();
	void							ButtonDeletePrefab();
	
	void							AppSceneDisplay();
	void							AppSceneRefresh();
	void							AppSceneListEdit(const Glib::ustring& index, const Glib::ustring& value);
	void							AppSceneSelection();
	void							ButtonNewScene();
	void							ButtonDeleteScene();


	Glib::RefPtr<Gtk::ListStore>	AppListStoreInspector;
	Gtk::TreeView					*AppListStoreInspectorview;

	Glib::RefPtr<Gtk::ListStore>	AppListStoreGo;
	Gtk::TreeView					*AppListStoreGoview;

	Glib::RefPtr<Gtk::ListStore>	AppListStoreScene;
	Gtk::TreeView					*AppListStoreSceneview;
	
	Application*					app;

	// Scene panel //
	void							SceneInspectorDisplay();
	void							SceneInspectorRefresh();
	void							SceneInspectorEdit(const Glib::ustring& index, const Glib::ustring& value);
	void							ButtonNewInstance();
	void							ButtonDeleteInstance();

	void							SceneListDisplay();
	void							SceneListRefresh();
	void							SceneListEdit(const Glib::ustring& index, const Glib::ustring& value);
	void							SceneListSelection();

	Glib::RefPtr<Gtk::ListStore>	treeSceneInspector;
	Gtk::TreeView					*treeViewSceneInspector;

	Glib::RefPtr<Gtk::ListStore>	treeSceneList;
	Gtk::TreeView					*treeViewSceneList;
	Gtk::TreeModel::iterator 		selectionGameObject;

	static Scene*							scene;

	// GameObject panel //
	void							GoInspectorDisplay();
	void							GoInspectorRefresh();
	void							GoInspectorClear();
	void							GoInspectorEdit(const Glib::ustring& index, const Glib::ustring& value);

	void							ButtonNewComponent();
	void							ButtonDeleteComponent();
	
	Glib::RefPtr<Gtk::ListStore>	treeGameObjectInspector;
	Gtk::TreeView					*treeViewGameObjectInspector;

	static GameObject*						gameObject;


};

#endif