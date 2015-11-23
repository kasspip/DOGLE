#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <gtkmm.h>
#include <gtkmm/messagedialog.h>
#include <gdk/gdkkeysyms.h>
#include <gtkmm/application.h>

#include "Builder.hpp"
#include "Engine.hpp"
#include "DOGLE.hpp"
#include "../CoreClass/Application.hpp"
#include "../CoreClass/GameObject.hpp"

#include "Popup.hpp"
#include "myColumn.hpp"
#include "ToggleColumn.hpp"
#include "FileFinder.hpp"
#include "PopupInstancePrefab.hpp"
#include "PopupNewComponent.hpp"

class UI
{
public:

	UI();
	UI(Application *app);
	~UI();

	Glib::RefPtr<Gtk::Application>	GtkApp;
	Glib::RefPtr<Gtk::Builder>		builder;
	Gtk::Window						*window;

	bool							update;

	myColumn						model;
	ToggleColumn					model2;

	bool							del(GdkEventKey *e);
	void							run();
	void 							UnselectTreeView( Gtk::TreeView *treeView );
	void 							ClearListStore( Glib::RefPtr<Gtk::ListStore> list );


	// Application panel //
	void							AppInspectorDisplay();
	void							AppInspectorEdit(const Glib::ustring& index, const Glib::ustring& value);
	void							ButtonNewApp();
	void							ButtonLoadApp();
	void							ButtonSaveApp();

	Glib::RefPtr<Gtk::ListStore>	AppInspectorList;
	Gtk::TreeView					*AppInspectorTreeView;

	void							AppPrefabDisplay();
	void							AppPrefabRefresh();
	void							AppPrefabListEdit(const Glib::ustring& index, const Glib::ustring& value);
	void							AppPrefabSelection();
	void							ButtonNewPrefab();
	void							ButtonDeletePrefab();
	
	Glib::RefPtr<Gtk::ListStore>	AppPrefabList;
	Gtk::TreeView					*AppPrefabTreeView;

	void							AppSceneDisplay();
	void							AppSceneRefresh();
	void							AppSceneListEdit(const Glib::ustring& index, const Glib::ustring& value);
	void							AppSceneSelection();
	void							ButtonNewScene();
	void							ButtonDeleteScene();

	Glib::RefPtr<Gtk::ListStore>	AppScenesList;
	Gtk::TreeView					*AppScenesTreeView;
	
	Application*					app;

	// Scene panel //
	void							SceneInspectorDisplay();
	void							SceneInspectorRefresh();
	void							SceneInspectorEdit(const Glib::ustring& index, const Glib::ustring& value);
	void							ButtonNewInstance();
	void							ButtonDeleteInstance();

	Glib::RefPtr<Gtk::ListStore>	SceneInspectorList;
	Gtk::TreeView					*SceneInspectorTreeView;

	void							SceneListDisplay();
	void							SceneListRefresh();
	void							SceneListEdit(const Glib::ustring& index, const Glib::ustring& value);
	void							SceneListSelection();

	Glib::RefPtr<Gtk::ListStore>	SceneGameObjectsList;
	Gtk::TreeView					*SceneGameObjectsTreeView;

	static Scene*							scene;

	// GameObject panel //
	void							GoInspectorDisplay();
	void							GoInspectorRefresh();
	void							GoInspectorEditCol1(const Glib::ustring& index, const Glib::ustring& value);
	void							GoInspectorEditCol2(const Glib::ustring& index, const Glib::ustring& value);
	void							GoInspectorEditCol3(const Glib::ustring& index, const Glib::ustring& value);
	void							GoInspectorEditCol4(const Glib::ustring& index, const Glib::ustring& value);
	void							ButtonNewComponent();
	void							ButtonDeleteComponent();
	
	Glib::RefPtr<Gtk::ListStore>	GameObjectInspectorList;
	Gtk::TreeView					*GameObjectInspectorTreeView;

	void							GoComponentsDisplay();
	void							GoComponentsRefresh();
	void							GoComponentsSelection();


	Glib::RefPtr<Gtk::ListStore>	GameObjectComponentsList;
	Gtk::TreeView					*GameObjectComponentsTreeView;

	static GameObject*						gameObject;

	// Components //
	void							ComponentPropertyDisplay();
	void							SkinPropertyRefresh();
	void							CameraPropertyRefresh();
	void							LightPropertyRefresh();
	void							ColliderPropertyRefresh();
	void							ComponentPropertyEditCol1(const Glib::ustring& index, const Glib::ustring& value);
	void							ComponentPropertyEditCol2(const Glib::ustring& index, const Glib::ustring& value);
	void							ComponentPropertyEditCol3(const Glib::ustring& index, const Glib::ustring& value);

	Glib::RefPtr<Gtk::ListStore>	ComponentPropertyList;
	Gtk::TreeView					*ComponentPropertyTreeView;

	static IComponent*						component;


};

#endif