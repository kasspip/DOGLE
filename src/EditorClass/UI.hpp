#ifndef UI_HPP
#define UI_HPP

#include <iostream>

#include <gtkmm/messagedialog.h>
#include <gdk/gdkkeysyms.h>
#include <gtkmm/application.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/builder.h>
#include <gtkmm/filefilter.h>
#include <gtkmm/filechooserdialog.h>

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
#include "PopupConfirmation.hpp"
#include "PopupSelectItems.hpp"
#include "ScriptManager.hpp"


class UI
{
	
public:

	UI();
	UI(Application *app, std::string Dfile = "");
	~UI();

	Glib::RefPtr<Gtk::Application>	GtkApp;
	Glib::RefPtr<Gtk::Builder>		builder;
	Gtk::Window						*window;
	bool							update;
	bool							isSaved;
	myColumn						model;
	ToggleColumn					model2;
	std::string						dogleFile;

	void							run();
	bool							del(GdkEventKey *e);
	void							OnQuitEditor();
	void 							UnselectTreeView( Gtk::TreeView *treeView );
	void 							ClearListStore( Glib::RefPtr<Gtk::ListStore> list );
	std::string						PopupGetText(std::string win_name, std::string label, const Glib::ustring warning);
	bool							PopupGetConfirm(std::string win_name, std::string question);
	void							PopWarning(const Glib::ustring warn);
	std::string						PopupGetItem( std::list<std::string> items );
	std::string						FinderGetFile(std::string folder, std::string extensionPattern);
	std::string						FileGetName(std::string& filePath);
	std::string						FileGetPath(std::string& filePath);
	void							ReplaceScriptName(std::string oldName, std::string newName);
	void 							ApplicationRemoveScripts(std::string name);
	void							DeleteFile(std::string file);


	// Application panel //
	void							AppInspectorDisplay();
	void							AppInspectorRefresh();
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
	
	void							AppScriptDisplay();
	void							AppScriptRefresh();
	void							ButtonImportScript();
	void							ButtonNewScript();
	void							ButtonDeleteScript();

	Glib::RefPtr<Gtk::ListStore>	AppScriptList;
	Gtk::TreeView					*AppScriptTreeView;

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

	static Scene*					scene;

	// GameObject panel //
	void							GoInspectorDisplay();
	void							GoInspectorRefresh();
	void							GoInspectorEditCol1(const Glib::ustring& index, const Glib::ustring& value);
	void							GoInspectorEditCol2(const Glib::ustring& index, const Glib::ustring& value);
	void							GoInspectorEditCol3(const Glib::ustring& index, const Glib::ustring& value);
	void							GoInspectorEditCol4(const Glib::ustring& index, const Glib::ustring& value);
	void							ButtonNewComponent();
	void							ButtonDeleteComponent();

	void							CreateComponent(std::string type);
	void							CreateCamera();
	void							CreateLight();
	void							CreateText();
	void							CreateSkin();
	void							CreateScript();
	void							CreateCollider();

	Glib::RefPtr<Gtk::ListStore>	GameObjectInspectorList;
	Gtk::TreeView					*GameObjectInspectorTreeView;

	void							GoComponentsDisplay();
	void							GoComponentsRefresh();
	void							GoComponentsSelection();

	Glib::RefPtr<Gtk::ListStore>	GameObjectComponentsList;
	Gtk::TreeView					*GameObjectComponentsTreeView;

	static GameObject*				gameObject;

	// Components //
	void							ComponentPropertyDisplay();
	void							SkinPropertyRefresh();
	void							CameraPropertyRefresh();
	void							LightPropertyRefresh();
	void							ColliderPropertyRefresh();
	void							TextPropertyRefresh();
	void							ScriptPropertyRefresh(Script* script);
	void							ComponentPropertyEditCol1(const Glib::ustring& index, const Glib::ustring& value);
	void							ComponentPropertyEditCol2(const Glib::ustring& index, const Glib::ustring& value);
	void							ComponentPropertyEditCol3(const Glib::ustring& index, const Glib::ustring& value);

	Glib::RefPtr<Gtk::ListStore>	ComponentPropertyList;
	Gtk::TreeView					*ComponentPropertyTreeView;

	static IComponent*				component;


};

#endif