#include "UI.hpp"
#include <string>

Scene*			UI::scene = nullptr;
GameObject*		UI::gameObject = nullptr;
IComponent*		UI::component = nullptr;

// CONSTRUCTOR DESTRUCTOR //


UI::UI(Application *app, std::string Dfile) : 
											dogleFile(Dfile),
											AppInspectorList(0),
											AppPrefabList(0),
											app(app)
{

	GtkApp = Gtk::Application::create("Dogle.gtkmm.Editor.base", Gio::APPLICATION_FLAGS_NONE);
	builder = Gtk::Builder::create_from_file("src/EditorClass/unity_gtk.glade");
	builder->get_widget("window1", window);
	GtkApp->signal_shutdown ().connect(sigc::mem_fun(*this, &UI::OnQuitEditor));
	
	AppInspectorDisplay();
	SceneInspectorDisplay();
  	GoInspectorDisplay();
	AppPrefabDisplay();
	AppSceneDisplay();
	AppScriptDisplay();
	SceneListDisplay();
	GoComponentsDisplay();
	ComponentPropertyDisplay();
	
	update = true;
	isSaved = true;

	/*APPLICATION NEW BUTTON*/
	Gtk::Button	*new_button;
	builder->get_widget("button1", new_button);
	new_button->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonNewApp));

	/*APPLICATION LOAD BUTTON*/
	Gtk::Button	*loadButton;
	builder->get_widget("button2", loadButton);
	loadButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonLoadApp));

	/*APPLICATION SAVE BUTTON*/
	Gtk::Button	*saveButton;
	builder->get_widget("button3", saveButton);
	saveButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonSaveApp));

	/*APPLICATION NEW PREFAB*/
	Gtk::Button	*prefabNewButton;
	builder->get_widget("button4", prefabNewButton);
	prefabNewButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonNewPrefab));

	/*APPLICATION DELETE PREFAB*/
	Gtk::Button	*prefabDeleteButton;
	builder->get_widget("button8", prefabDeleteButton);
	prefabDeleteButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonDeletePrefab));

	/*APPLICATION SCENE NEW BUTTON*/
	Gtk::Button	*SceneNewButton;
	builder->get_widget("button5", SceneNewButton);
	SceneNewButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonNewScene));

	/*APPLICATION SCENE DELETE BUTTON*/
	Gtk::Button	*SceneDeleteButton;
	builder->get_widget("button11", SceneDeleteButton);
	SceneDeleteButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonDeleteScene));

	/*APPLICATION SCENE NEW BUTTON*/
	Gtk::Button	*ScriptNewButton;
	builder->get_widget("button12", ScriptNewButton);
	ScriptNewButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonNewScript));

	/*APPLICATION SCENE DELETE BUTTON*/
	Gtk::Button	*ScriptDeleteButton;
	builder->get_widget("button13", ScriptDeleteButton);
	ScriptDeleteButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonDeleteScript));

	/*SCENE INSTANCIATE BUTTON*/
	Gtk::Button	*SceneInstanciateButton;
	builder->get_widget("button6", SceneInstanciateButton);
	SceneInstanciateButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonNewInstance));

	/*SCENE REMOVE INSTANCE BUTTON*/
	Gtk::Button	*SceneRemoveInstanceButton;
	builder->get_widget("button9", SceneRemoveInstanceButton);
	SceneRemoveInstanceButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonDeleteInstance));

	/*GAME NEW COMPONENT*/
	Gtk::Button	*componentNewButton;
	builder->get_widget("button7", componentNewButton);
	componentNewButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonNewComponent));

	/*GAME REMOVE COMPONENT*/
	Gtk::Button	*componentRemoveButton;
	builder->get_widget("button10", componentRemoveButton);
	componentRemoveButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::ButtonDeleteComponent));
}

UI::~UI()
{
	delete app;
}


// APPLICATION  PANEL //


void		UI::ButtonNewApp()
{
	int		ret;
	Popup	pop = Popup("New app", this->window, "Choose an application name:");

	while ((ret = pop.run()) != Gtk::RESPONSE_CANCEL)
	{
		if (ret == Gtk::RESPONSE_OK && pop.getText().length())
		{
			if (app)
				delete app;
			app = new Application(pop.getText());
			AppInspectorDisplay();
			break ;
		}
		else
		{
			Gtk::MessageDialog warning(*this->window, "<b>You must specify a valid app name !</b>", true, Gtk::MESSAGE_WARNING);
			warning.run();
		}
	}
}

void		UI::ButtonLoadApp()
{
	Builder 	builder;

	dogleFile = FinderGetFile("./", "*.dogle");
	if (dogleFile.length() == 0 )
		return ;
	
	scene = nullptr;
	gameObject = nullptr;
	component = nullptr;
	if (app)
		delete app;

	app = builder.Build(dogleFile);

	AppInspectorRefresh();
	SceneInspectorRefresh();
  	GoInspectorRefresh();
	AppPrefabRefresh();
	AppSceneRefresh();
	SceneListRefresh();
	GoComponentsRefresh();

}

void		UI::ButtonSaveApp()
{
	if (app)
	{
		isSaved = true;
		app->Save();
	}
}

void		UI::AppInspectorDisplay()
{
	builder->get_widget("treeview1", AppInspectorTreeView);
	AppInspectorList = Gtk::ListStore::create(model);
	AppInspectorTreeView->set_model(AppInspectorList);
	
	AppInspectorTreeView->append_column("Inspector", model.m_col_name);
	AppInspectorTreeView->append_column_editable("", model.value_1);
	AppInspectorTreeView->get_column_cell_renderer(0)->set_fixed_size(100,0);

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(AppInspectorTreeView->get_column_cell_renderer(1));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::AppInspectorEdit));

	AppInspectorRefresh();
}

void		UI::AppInspectorRefresh()
{
	ClearListStore(AppInspectorList);

	if (app)
	{
		Gtk::TreeModel::iterator newRow = AppInspectorList->append();
		(*newRow)[model.m_col_name] = "Name";
		(*newRow)[model.value_1] = app->name;
		
		newRow = AppInspectorList->append();
		(*newRow)[model.m_col_name] = "Win Width";
		std::stringstream winWVal;
		winWVal << app->winW;
		(*newRow)[model.value_1] = winWVal.str();
	
		newRow = AppInspectorList->append();
		(*newRow)[model.m_col_name] = "Win Height";
		std::stringstream winHVal;
		winHVal << app->winH;
		(*newRow)[model.value_1] = winHVal.str();
	
		newRow = AppInspectorList->append();
		(*newRow)[model.m_col_name] = "Fps";
		std::stringstream FPSVal;
		FPSVal << app->FPS;
		(*newRow)[model.value_1] = FPSVal.str();
	}
}


void		UI::AppInspectorEdit(const Glib::ustring& index, const Glib::ustring& value)
{
	switch (std::stoi(index))
	{
		case 0:		app->name = value; 				break;
		case 1:		app->winW = std::stoi(value); 	break;
		case 2:		app->winH = std::stoi(value); 	break;
		case 3:		app->FPS = std::stoi(value); 	break;
	}
	isSaved = false;
}






// APP PREFAB LIST //



void		UI::AppPrefabDisplay()
{
	builder->get_widget("treeview2", AppPrefabTreeView);
	AppPrefabList = Gtk::ListStore::create(model2);
	AppPrefabTreeView->set_model(AppPrefabList);
	
	AppPrefabTreeView->append_column_editable("Prefabs :", model2.m_col_name);
	AppPrefabTreeView->append_column_editable("", model2.del);
	AppPrefabTreeView->get_column_cell_renderer(0)->set_fixed_size(300,0);

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(AppPrefabTreeView->get_column_cell_renderer(0));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::AppPrefabListEdit));

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = AppPrefabTreeView->get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &UI::AppPrefabSelection));
	
	AppPrefabRefresh();
}

void		UI::AppPrefabRefresh()
{
	ClearListStore(AppPrefabList);
	
	if (app)
	{
		for (GameObject* go : app->GetListPrefab())
		{
			Gtk::TreeModel::iterator iter = AppPrefabList->append();
			(*iter)[model2.m_col_name] = go->name;
			(*iter)[model2.del] = false;
		}
	}
}

void		UI::AppPrefabListEdit(const Glib::ustring& index, const Glib::ustring& value)
{
	int	target = std::stoi(index);
	int	counter = 0;

	for (GameObject* go : app->GetListPrefab())
	{
		if (counter == target)
		{
			go->name = value;
			break ;
		}
		counter++;
	}
	GoInspectorRefresh();
	isSaved = false;
}

void		UI::AppPrefabSelection()
{
	if (!update)
		return ;
	scene = nullptr;
	SceneInspectorRefresh();
	UnselectTreeView(AppScenesTreeView);	
	UnselectTreeView(SceneGameObjectsTreeView);
	ClearListStore(SceneGameObjectsList);

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = AppPrefabTreeView->get_selection();
	Gtk::TreeModel::iterator selection = treeSelection->get_selected();
	if(selection)
	{
		std::stringstream ss;
		ss << (*selection)[model2.m_col_name];
  		gameObject = app->FindPrefab( ss.str() );
  		GoInspectorRefresh();
	}

}

void		UI::ButtonNewPrefab()
{
	if (!app)
	{
		Gtk::MessageDialog warning(*this->window, "<b>You must instantiate an app before creating GameObjects</b>", true, Gtk::MESSAGE_WARNING);
		warning.run();
		return ;
	}
	
	int		ret;
	Popup	pop = Popup("New GameObject", this->window, "Name:");

	while ((ret = pop.run()) != Gtk::RESPONSE_CANCEL)
	{
		if (ret == Gtk::RESPONSE_OK && pop.getText().length())
		{
			if (!AppPrefabList)
			{
				builder->get_widget("treeview2", AppPrefabTreeView);
				AppPrefabList = Gtk::ListStore::create(model2);
				AppPrefabTreeView->set_model(AppPrefabList);
				
				AppPrefabTreeView->append_column_editable("Prefabs :",model2.m_col_name);
				AppPrefabTreeView->append_column_editable("",model2.del);
				AppPrefabTreeView->get_column_cell_renderer(0)->set_fixed_size(300,0);
			}
			Gtk::TreeModel::iterator newRow = AppPrefabList->append();
			(*newRow)[model2.m_col_name] = pop.getText();
			(*newRow)[model2.del] = false;
			app->AddPrefab(new GameObject(pop.getText()));
			
			isSaved = false;
			break ;
		}
		else
			PopWarning("<b>You must specify a GameObject name !</b>");
	}
}

void		UI::ButtonDeletePrefab()
{
	if (!gameObject || !gameObject->IsPrefab())
		return;

	Gtk::TreeModel::Children children = AppPrefabList->children();
	Gtk::TreeModel::Children::iterator row = children.begin();

	for (; row != children.end(); row++)
	{
		if ((*row)[model2.del] == true)
		{
			std::stringstream ss;
			ss << (*row)[model2.m_col_name];
			app->DeletePrefab( ss.str() );
		}
	}
	gameObject = nullptr;
	AppPrefabRefresh();
	GoInspectorRefresh();

	isSaved = false;
}







// APP SCENE LIST //


void		UI::AppSceneDisplay()
{
	builder->get_widget("treeview3", AppScenesTreeView);
	AppScenesList = Gtk::ListStore::create(model2);
	AppScenesTreeView->set_model(AppScenesList);

	AppScenesTreeView->append_column_editable("Scenes :",model2.m_col_name);
	AppScenesTreeView->append_column_editable("",model2.del);
	AppScenesTreeView->get_column_cell_renderer(0)->set_fixed_size(300,0);

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(AppScenesTreeView->get_column_cell_renderer(0));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::AppSceneListEdit));

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = AppScenesTreeView->get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &UI::AppSceneSelection));
	AppSceneRefresh();
}

void		UI::AppSceneRefresh()
{
	ClearListStore(AppScenesList);

	if (app)
	{
		for (Scene* scene : app->GetListScene())
		{
			Gtk::TreeModel::iterator iter = AppScenesList->append();
			(*iter)[model2.m_col_name] = scene->name;
			(*iter)[model2.del] = false;
		}
	}
}

void		UI::AppSceneListEdit(const Glib::ustring& index, const Glib::ustring& value)
{
	int	target = std::stoi(index);
	int	counter = 0;
	
	for (Scene* scene : app->GetListScene())
	{
		if (counter == target)
		{
			scene->name = value;
			break ;
		}
		counter++;
	}
  	SceneInspectorRefresh();
	isSaved = false;
}

void		UI::AppSceneSelection()
{
	if (!update)
		return ;
	UnselectTreeView(AppPrefabTreeView);
	ClearListStore(GameObjectInspectorList);


	Glib::RefPtr<Gtk::TreeSelection> treeSelection = AppScenesTreeView->get_selection();
	Gtk::TreeModel::iterator selection = treeSelection->get_selected();
	

	gameObject = nullptr;
	if(selection)
	{
		std::stringstream ss;
		ss << (*selection)[model2.m_col_name];
  		try 
  		{
  			scene = app->FindScene( ss.str() );
  		}
  		catch (DError & e ) {
  			std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) << C_DEFAULT << std::endl;
  		}
  		GoInspectorRefresh();
  		SceneInspectorRefresh();
  		SceneListRefresh();
	}
}

void		UI::ButtonNewScene()
{
	std::string sceneName = PopupGetText("New Scene","Name:","<b>You must specify a Scene name</b>");
	 
	if (sceneName.length() == 0)
		return;
	if (!AppScenesList)
	{
		builder->get_widget("treeview3", AppScenesTreeView);
		AppScenesList = Gtk::ListStore::create(model2);
		AppScenesTreeView->set_model(AppScenesList);
		
		AppScenesTreeView->append_column_editable("Prefabs :",model2.m_col_name);
		AppScenesTreeView->append_column_editable("",model2.del);
		AppScenesTreeView->get_column_cell_renderer(0)->set_fixed_size(300,0);
	}
		
	Gtk::TreeModel::iterator newRow = AppScenesList->append();
	(*newRow)[model2.m_col_name] = sceneName;
	(*newRow)[model2.del] = false;
	try 
	{
		app->AddScene(new Scene(sceneName));
	}
	catch (DError & e) {
	 	std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) << C_DEFAULT << std::endl;
	 }
	
	isSaved = false;
}

void		UI::ButtonDeleteScene()
{
	if (!scene)
		return;

	Gtk::TreeModel::Children children = AppScenesList->children();
	Gtk::TreeModel::Children::iterator row = children.begin();

	for (; row != children.end(); row++)
	{
		if ((*row)[model2.del] == true)
		{
			std::stringstream ss;
			ss << (*row)[model2.m_col_name];
			app->DeleteScene( ss.str() );
		}
	}
	if (gameObject && !gameObject->IsPrefab())
	{
		gameObject = nullptr;
		GoInspectorRefresh();
	}
	scene = nullptr;
	AppSceneRefresh();
	SceneInspectorRefresh();

	
	isSaved = false;
}






//	APP SCRIPTS LIST //


void		UI::AppScriptDisplay()
{
	builder->get_widget("treeview9", AppScriptTreeView);
	AppScriptList = Gtk::ListStore::create(model2);
	AppScriptTreeView->set_model(AppScriptList);

	AppScriptTreeView->append_column("Linked scripts :",model2.m_col_name);
	AppScriptTreeView->append_column_editable("",model2.del);
	AppScriptTreeView->get_column_cell_renderer(0)->set_fixed_size(300,0);

	// Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(AppScriptTreeView->get_column_cell_renderer(0));
	// cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::AppSceneListEdit));

	AppScriptRefresh();
}

void		UI::AppScriptRefresh()
{
	ClearListStore(AppScriptList);

	ScriptManager sm;

	for (std::string scriptName : sm.GetScriptsNames())
	{
		Gtk::TreeModel::iterator iter = AppScriptList->append();
		(*iter)[model2.m_col_name] = scriptName;
		(*iter)[model2.del] = false;
	}

}

void		UI::ButtonNewScript()
{
	std::string scriptName = PopupGetText("New Script", "Name ", "<b>You must specify a Script name</b>");
	
	if (scriptName.length() == 0)
		return;
	
	ScriptManager			scriptManager;
	scriptManager.NewScript(scriptName);
	
	AppScriptRefresh();
}

void		UI::ButtonDeleteScript()
{
	Gtk::TreeModel::Children children = AppScriptList->children();
	Gtk::TreeModel::Children::iterator row = children.begin();

	for (; row != children.end(); row++)
	{
		if ((*row)[model2.del] == true)
		{
			std::stringstream ss;
			ss << (*row)[model2.m_col_name];
		
			ScriptManager			scriptManager;
			
			scriptManager.RemoveScript( ss.str() );
			ApplicationRemoveScripts(ss.str());

			if (false == PopupGetConfirm("Unlink Script", 
				"\tDo you want to keep " + ss.str() + ".cpp ?"))
				DeleteFile("./resources/Scripts/" + ss.str() + ".cpp");
		}
	}
	
	AppScriptRefresh();
	GoInspectorRefresh();
}








// SCENE PANEL //



void		UI::SceneInspectorDisplay()
{
	builder->get_widget("treeview4", SceneInspectorTreeView);
	SceneInspectorList = Gtk::ListStore::create(model);
	SceneInspectorTreeView->set_model(SceneInspectorList);

	SceneInspectorTreeView->append_column("Inspector", model.m_col_name);
	SceneInspectorTreeView->append_column_editable("", model.value_1);
	SceneInspectorTreeView->get_column_cell_renderer(0)->set_fixed_size(100,0);


	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(SceneInspectorTreeView->get_column_cell_renderer(1));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::SceneInspectorEdit));
}

void		UI::SceneInspectorRefresh()
{
	ClearListStore(SceneInspectorList);

	if (scene)
	{	
		Gtk::TreeModel::iterator row = SceneInspectorList->append();
		(*row)[model.m_col_name] = "Name";
		(*row)[model.value_1] = scene->name;
	}
	SceneListRefresh();
}

void		UI::SceneInspectorEdit(const Glib::ustring& index, const Glib::ustring& value)
{
	switch (std::stoi(index))
	{
		case 0:		scene->name = value;	break;
	}
	AppSceneRefresh();
	isSaved = false;
}






// SCENE GAMEOBJECTS LIST //



void		UI::SceneListDisplay()
{
	builder->get_widget("treeview5", SceneGameObjectsTreeView);
	SceneGameObjectsList = Gtk::ListStore::create(model2);
	SceneGameObjectsTreeView->set_model(SceneGameObjectsList);

	SceneGameObjectsTreeView->append_column_editable("GameObjects",model2.m_col_name);
	SceneGameObjectsTreeView->append_column_editable("",model2.del);
	SceneGameObjectsTreeView->get_column_cell_renderer(0)->set_fixed_size(300,0);
	

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = SceneGameObjectsTreeView->get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &UI::SceneListSelection));

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(SceneGameObjectsTreeView->get_column_cell_renderer(0));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::SceneListEdit));

}

void		UI::SceneListRefresh()
{
	ClearListStore(SceneGameObjectsList);

	if (scene)
	{
		for (GameObject* go : scene->GetBindGameObjectList())
		{
			Gtk::TreeModel::iterator newRow = SceneGameObjectsList->append();
			(*newRow)[model2.m_col_name] = go->name;
			(*newRow)[model2.del] = false;
		}
	}
}

void		UI::SceneListEdit(const Glib::ustring& index, const Glib::ustring& value)
{
	int	target = std::stoi(index);
	int	counter = 0;

	for (GameObject* go : scene->GetBindGameObjectList())
	{
		if (counter == target)
		{
			go->name = value;
			gameObject = go; 
			break ;
		}
		counter++;
	}
	GoInspectorRefresh();
	isSaved = false;
}

void		UI::SceneListSelection()
{
	if (!update)
		return ;
	UnselectTreeView(AppPrefabTreeView);
	
	Gtk::TreeModel::iterator selection = SceneGameObjectsTreeView->get_selection()->get_selected();

	if(selection)
	{
	 	std::stringstream ss;
	 	ss << (*selection)[model2.m_col_name];
	 	try 
	 	{
 	  		gameObject = scene->FindGameObject( ss.str() );
	 	}
	 	catch (DError & e) {
	 		std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) << C_DEFAULT << std::endl;
	 	}
	 	GoInspectorRefresh();
	}
}

void		UI::ButtonNewInstance()
{
	GameObject 	*prefab;

	if (!scene)
	{
		PopWarning("No Scene Selected.");
		return;
	}
	PopupInstancePrefab	popup = PopupInstancePrefab(this->window, app);
	int i = 0;
	while (popup.run() != Gtk::RESPONSE_CANCEL)
	{
		if ((prefab = popup.GetSelection()) != nullptr)
		{
			scene->InstanciatePrefab(prefab);
			SceneListRefresh();
			isSaved = false;
			break ;
		}
		else 
		{
			if (i > 0)
				break;
			i++;
		}
	}
}

void		UI::ButtonDeleteInstance()
{
	if (!scene)
	{
		PopWarning("No Scene Selected.");
		return;
	}

	Gtk::TreeModel::Children children = SceneGameObjectsList->children();
	Gtk::TreeModel::Children::iterator row = children.begin();

	for (; row != children.end(); row++)
	{
		if ((*row)[model2.del] == true)
		{
			std::stringstream ss;
			ss << (*row)[model2.m_col_name];
			scene->DeleteInstance( ss.str() );
		}
	}

	gameObject = nullptr;
	SceneListRefresh();
	GoInspectorRefresh();

	isSaved = false;
}






// GAMEOBJECT PANEL //



void		UI::GoInspectorDisplay()
{
	builder->get_widget("treeview6", GameObjectInspectorTreeView);
	GameObjectInspectorList = Gtk::ListStore::create(model);
	GameObjectInspectorTreeView->set_model(GameObjectInspectorList);

	GameObjectInspectorTreeView->append_column("Inspector", model.m_col_name);
	GameObjectInspectorTreeView->append_column_editable("", model.value_1);
	GameObjectInspectorTreeView->append_column_editable("", model.value_2);
	GameObjectInspectorTreeView->append_column_editable("", model.value_3);
	GameObjectInspectorTreeView->append_column_editable("", model.value_4);

	GameObjectInspectorTreeView->get_column_cell_renderer(0)->set_fixed_size(100,0);
	GameObjectInspectorTreeView->get_column_cell_renderer(2)->set_fixed_size(40,0);
	GameObjectInspectorTreeView->get_column_cell_renderer(3)->set_fixed_size(40,0);
	GameObjectInspectorTreeView->get_column_cell_renderer(4)->set_fixed_size(40,0);

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(GameObjectInspectorTreeView->get_column_cell_renderer(1));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::GoInspectorEditCol1));
	cellText = static_cast<Gtk::CellRendererText*>(GameObjectInspectorTreeView->get_column_cell_renderer(2));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::GoInspectorEditCol2));
	cellText = static_cast<Gtk::CellRendererText*>(GameObjectInspectorTreeView->get_column_cell_renderer(3));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::GoInspectorEditCol3));
	cellText = static_cast<Gtk::CellRendererText*>(GameObjectInspectorTreeView->get_column_cell_renderer(4));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::GoInspectorEditCol4));
}

void		UI::GoInspectorRefresh()
{
	ClearListStore(GameObjectInspectorList);
	
	if (gameObject)
	{	
		Gtk::TreeModel::iterator row;
		std::stringstream ss;
		Transform* transform = gameObject->GetComponent<Transform>();

		row = GameObjectInspectorList->append();
		(*row)[model.m_col_name] = "Name";
		(*row)[model.value_1] = gameObject->name;

		row = GameObjectInspectorList->append();

		row = GameObjectInspectorList->append();
		(*row)[model.m_col_name] = "Position";
		ss << transform->_position.x;
		(*row)[model.value_2] = ss.str();
		ss.str(std::string());
		
		ss << transform->_position.y;
		(*row)[model.value_3] = ss.str();
		ss.str(std::string());
		
		ss << transform->_position.z;
		(*row)[model.value_4] = ss.str();
		ss.str(std::string());
		
		row = GameObjectInspectorList->append();
		(*row)[model.m_col_name] = "Rotation";
		ss << transform->_rotation.x;
		(*row)[model.value_2] = ss.str();
		ss.str(std::string());
		
		ss << transform->_rotation.y;
		(*row)[model.value_3] = ss.str();
		ss.str(std::string());
		
		ss << transform->_rotation.z;
		(*row)[model.value_4] = ss.str();
		ss.str(std::string());
		
		row = GameObjectInspectorList->append();
		(*row)[model.m_col_name] = "Scale";
		ss << transform->_scale.x;
		(*row)[model.value_2] = ss.str();
		ss.str(std::string());
		
		ss << transform->_scale.y;
		(*row)[model.value_3] = ss.str();
		ss.str(std::string());

		ss << transform->_scale.z;
		(*row)[model.value_4] = ss.str();

		GoComponentsRefresh();
	}
	else
		ClearListStore(GameObjectComponentsList);
	ClearListStore(ComponentPropertyList);
}

void		UI::GoInspectorEditCol1(const Glib::ustring& index, const Glib::ustring& value)
{
	switch (std::stoi(index))
	{
		case 0:		gameObject->name = value; 	break;
	}
	if (gameObject->IsPrefab())
		AppPrefabRefresh();
	else
		SceneListRefresh();
	isSaved = false;
}

void		UI::GoInspectorEditCol2(const Glib::ustring& index, const Glib::ustring& value)
{
	Transform* transform = gameObject->GetComponent<Transform>();
	switch (std::stoi(index))
	{
		case 2: 	transform->_position.x = std::stof(value); 	break;
		case 3: 	transform->_rotation.x = std::stof(value); 	break;
		case 4: 	transform->_scale.x = std::stof(value); 	break;
	}
	isSaved = false;
}

void		UI::GoInspectorEditCol3(const Glib::ustring& index, const Glib::ustring& value)
{
	Transform* transform = gameObject->GetComponent<Transform>();
	switch (std::stoi(index))
	{
		case 2: 	transform->_position.y = std::stof(value); 	break;
		case 3: 	transform->_rotation.y = std::stof(value); 	break;
		case 4: 	transform->_scale.y = std::stof(value);		break;
	}
	isSaved = false;
}

void		UI::GoInspectorEditCol4(const Glib::ustring& index, const Glib::ustring& value)
{
	Transform* transform = gameObject->GetComponent<Transform>();
	switch (std::stoi(index))
	{
		case 2:		transform->_position.z = std::stof(value); 	break;
		case 3:		transform->_rotation.z = std::stof(value); 	break;
		case 4:		transform->_scale.z = std::stof(value);		break;
	}
	isSaved = false;
}






// GAMEOBJECT COMPONENTS //


void		UI::GoComponentsDisplay()
{
	builder->get_widget("treeview7", GameObjectComponentsTreeView);
	GameObjectComponentsList = Gtk::ListStore::create(model2);
	
	GameObjectComponentsTreeView->set_model(GameObjectComponentsList);
	GameObjectComponentsTreeView->append_column("Components:", model2.m_col_name);
	GameObjectComponentsTreeView->append_column_editable("", model2.del);
	GameObjectComponentsTreeView->get_column_cell_renderer(0)->set_fixed_size(500,0);


	Glib::RefPtr<Gtk::TreeSelection> treeSelection = GameObjectComponentsTreeView->get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &UI::GoComponentsSelection));
}

void		UI::GoComponentsRefresh()
{
	Gtk::TreeModel::iterator selection;

	ClearListStore(GameObjectComponentsList);

	if (gameObject)
	{
		for (IComponent* compo : gameObject->GetListComponent())
		{
			if (compo->type == "Transform")
				continue ;
			Gtk::TreeModel::iterator newRow = GameObjectComponentsList->append();
			if (compo->type == "Script")
				(*newRow)[model2.m_col_name] = dynamic_cast<Script*>(compo)->name;
			else
				(*newRow)[model2.m_col_name] = compo->type;
			(*newRow)[model2.del] = false;
		}
	}
}

void		UI::GoComponentsSelection()
{
	if (!update)
		return ;
	Gtk::TreeModel::iterator selection = GameObjectComponentsTreeView->get_selection()->get_selected();
	if(selection)
	{
		ClearListStore(ComponentPropertyList);
		std::stringstream ss;
		ss << (*selection)[model2.m_col_name];
	 	std::string type = ss.str();

	 	// 1 - add type here and create <name>PropertyRefresh() function
		if (type == "Skin")
	 		SkinPropertyRefresh();
	 	else if (type == "Camera")
	 		CameraPropertyRefresh();
	 	else if (type == "Light")
	 		LightPropertyRefresh();
	 	else if (type == "Collider")
	 		ColliderPropertyRefresh();
	 	else if (gameObject->GetScript(type))
	 		ScriptPropertyRefresh(gameObject->GetScript(type));
	}
	else
		component = nullptr;
}

void		UI::ButtonNewComponent()
{
	if (!gameObject)
	{
		PopWarning("No GameObject Selected.");
		return;
	}
	
	PopupNewComponent	popup = PopupNewComponent(this->window);
	int i = 0;
	std::string compoType;
	while (popup.run() != Gtk::RESPONSE_CANCEL)
	{
		if ((compoType = popup.GetSelection()).length() > 0)
		{
			CreateComponent(compoType);
			GoComponentsRefresh();
			isSaved = false;
			break ;
		}
		else 
		{
			if (i > 0)
				break;
			i++;
		}
	}
}

void		UI::ButtonDeleteComponent()
{
	if (!component)
	{
		PopWarning("No Component Selected.");
		return;
	}

	Gtk::TreeModel::Children children = GameObjectComponentsList->children();
	Gtk::TreeModel::Children::iterator row = children.begin();

	for (; row != children.end(); row++)
	{
		if ((*row)[model2.del] == true)
		{
			std::stringstream ss;
			ss << (*row)[model2.m_col_name];
			gameObject->DeleteComponent( ss.str() );
		}
	}
	GoInspectorRefresh();
	component = nullptr;
	isSaved = false;
}

void		UI::CreateComponent(std::string type)
{
	// 2 - Create and Link function creation

	if (type == "Camera")
		CreateCamera();
	else if (type == "Light")
		CreateLight();
	else if (type == "Skin")
		CreateSkin();
	else if (type == "Script")
		CreateScript();
	else if (type == "Collider")
		CreateCollider();
}

void		UI::CreateCamera()
{
	if (gameObject->GetComponent<Camera>())
	{
		PopWarning("Your GameObject has already a Camera Component");
		return ;
	}
	
	gameObject->AddComponent(new Camera);
}

void		UI::CreateLight()
{
	if (gameObject->GetComponent<Light>())
	{
		PopWarning("Your GameObject has already a Light Component");
		return ;
	}
	
	gameObject->AddComponent(new Light);
}

void		UI::CreateSkin()
{
	if (gameObject->GetComponent<Skin>())
	{
		PopWarning("Your GameObject has already a Skin Component");
		return ;
	}
	
	std::string file = FinderGetFile("./resources/3D Objects", "*.dae");
	if (file.length() == 0 )
		return;

	std::string skinFile = FileGetName(file);
	
	try {
		gameObject->AddComponent(new Skin( skinFile ));
	}
	catch (DError & e ) {
		std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) << C_DEFAULT << std::endl;
	}
}

void		UI::CreateScript()
{
	ScriptManager sm;
	std::string scriptFile;
	std::string scriptName;
	size_t separator;


	std::string file = FinderGetFile("./resources/Scripts", "*.cpp");
	if (file.length() == 0 )
		return ;
	
	scriptFile = FileGetName(file);
 	separator = scriptFile.find_last_of(".");
	scriptName = scriptFile.substr(0, separator);
	
	if (sm.ScriptExists(scriptName) == false)
	{
		std::cout << "linking " << scriptName << " to ScriptManager." << std::endl;
		sm.NewScript(scriptName);
		AppScriptRefresh();
	}

	try {
		gameObject->AddComponent(new Script( scriptName ));
	}
	catch (DError & e ) {
		std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) << C_DEFAULT << std::endl;
	}
}

void		UI::CreateCollider()
{
	if (gameObject->GetComponent<Collider>())
	{
		PopWarning("Your GameObject already has a Collider Component");
		return ;
	}
	
	std::cout << "NOT IMPLEMENTED" << std::endl;
}





// COMPONENT PROPERTY //


void		UI::ComponentPropertyDisplay()
{
	builder->get_widget("treeview8", ComponentPropertyTreeView);
	ComponentPropertyList = Gtk::ListStore::create(model);
	
	ComponentPropertyTreeView->set_model(ComponentPropertyList);
	ComponentPropertyTreeView->append_column("Properties:", model.m_col_name);
	ComponentPropertyTreeView->append_column_editable("", model.value_1);
	ComponentPropertyTreeView->append_column_editable("", model.value_2);
	ComponentPropertyTreeView->append_column_editable("", model.value_3);
	ComponentPropertyTreeView->append_column_editable("", model.value_4);

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(ComponentPropertyTreeView->get_column_cell_renderer(1));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::ComponentPropertyEditCol1));
	cellText = static_cast<Gtk::CellRendererText*>(ComponentPropertyTreeView->get_column_cell_renderer(2));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::ComponentPropertyEditCol2));
	cellText = static_cast<Gtk::CellRendererText*>(ComponentPropertyTreeView->get_column_cell_renderer(3));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::ComponentPropertyEditCol3));
}

void		UI::SkinPropertyRefresh()
{
	Skin* skin;
	try 
	{
 	  	skin = gameObject->GetComponent<Skin>();
 	  	component = skin;
	}catch (DError & e) {
	 	std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) << C_DEFAULT << std::endl;
	}
	
	Gtk::TreeModel::iterator row;
	std::stringstream ss;

	row = ComponentPropertyList->append();
	(*row)[model.m_col_name] = "3DFile";
	ss << skin->dae_file;
	(*row)[model.value_1] = ss.str();
	ss.str(std::string());

}

void		UI::ScriptPropertyRefresh(Script * script)
{
  	component = script;

	Gtk::TreeModel::iterator row;
	std::stringstream ss;

	row = ComponentPropertyList->append();
	(*row)[model.m_col_name] = "Name";
	ss << script->name;
	(*row)[model.value_1] = ss.str();
	ss.str(std::string());

}

void		UI::CameraPropertyRefresh()
{
	Camera* camera;
	try 
	{
 	  	camera = gameObject->GetComponent<Camera>();
 	  	component = camera;
	}catch (DError & e) {
	 	std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) << C_DEFAULT << std::endl;
	}
	
	Gtk::TreeModel::iterator row;
	std::stringstream ss;

	row = ComponentPropertyList->append();
	(*row)[model.m_col_name] = "Fov";
	ss << camera->fov;
	(*row)[model.value_1] = ss.str();
	ss.str(std::string());

	row = ComponentPropertyList->append();
	(*row)[model.m_col_name] = "Clip near";
	ss << camera->clipNear;
	(*row)[model.value_1] = ss.str();
	ss.str(std::string());

	row = ComponentPropertyList->append();
	(*row)[model.m_col_name] = "Clip far";
	ss << camera->clipFar;
	(*row)[model.value_1] = ss.str();
	ss.str(std::string());

}

void		UI::LightPropertyRefresh()
{
	Light* light;
	try 
	{
 	  	light = gameObject->GetComponent<Light>();
 	  	component = light;
	}catch (DError & e) {
	 	std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) << C_DEFAULT << std::endl;
	}
	
	Gtk::TreeModel::iterator row;
	std::stringstream ss;

	// row = ComponentPropertyList->append();
	// (*row)[model.m_col_name] = "3DFile";
	// ss << skin->dae_file;
	// (*row)[model.value_1] = ss.str();
	// ss.str(std::string());

}

void		UI::ColliderPropertyRefresh()
{
	Collider* collider;
	try 
	{
 	  	collider = gameObject->GetComponent<Collider>();
 	  	component = collider;
	}catch (DError & e) {
	 	std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) << C_DEFAULT << std::endl;
	}
	
	Gtk::TreeModel::iterator row;
	std::stringstream ss;

	row = ComponentPropertyList->append();
	(*row)[model.m_col_name] = "Mass";
	ss << collider->mass;
	(*row)[model.value_1] = ss.str();
	ss.str(std::string());

	if (collider->IsSkinned() == false)
	{
		row = ComponentPropertyList->append();
		(*row)[model.m_col_name] = "Center";
		ss << collider->center.x;
		(*row)[model.value_1] = ss.str();
		ss.str(std::string());
		
		ss << collider->center.y;
		(*row)[model.value_2] = ss.str();
		ss.str(std::string());
		
		ss << collider->center.z;
		(*row)[model.value_3] = ss.str();
		ss.str(std::string());
	
		row = ComponentPropertyList->append();
		(*row)[model.m_col_name] = "Size";
		ss << collider->size.x;
		(*row)[model.value_1] = ss.str();
		ss.str(std::string());
		
		ss << collider->size.y;
		(*row)[model.value_2] = ss.str();
		ss.str(std::string());
		
		ss << collider->size.z;
		(*row)[model.value_3] = ss.str();
		ss.str(std::string());
	}
}


void		UI::ComponentPropertyEditCol1(const Glib::ustring& index, const Glib::ustring& value)
{
	switch (std::stoi(index))
	{
		// 3 - add edition here
		// 4 - add choice selection in PopupNewComponent.cpp
		case 0:
			if (component->type == "Skin")
				dynamic_cast<Skin*>(component)->dae_file = value;	
			else if (component->type == "Camera")
				dynamic_cast<Camera*>(component)->fov = std::stof(value);
			else if (component->type == "Collider")
				dynamic_cast<Collider*>(component)->mass = std::stof(value);
			else if (component->type == "Script")
			{
				std::string oldName = dynamic_cast<Script*>(component)->name;

				if (PopupGetConfirm("Edit Name", 
					"\n\tEditing script name is not recommended : "
					"\n\tIt will perform an find and replace on several file AND save your app."
					"\n\tIt can overwrite variable's name similar to the previous script name."
					"\n\n\tAre you sure you want to proceed ?") == true)
				{
					ScriptManager sm;
					sm.EditScriptName(oldName, value, dogleFile);
					ReplaceScriptName(oldName, value);
					app->Save();
					AppScriptRefresh();
				}
			} 																		break;
		case 1:
			if (component->type == "Camera")
				dynamic_cast<Camera*>(component)->clipNear = std::stof(value);
			else if (component->type == "Collider")
				dynamic_cast<Collider*>(component)->center.x = std::stof(value); 	break;
		
		case 2:
			if (component->type == "Camera")
				dynamic_cast<Camera*>(component)->clipFar = std::stof(value);
			else if (component->type == "Collider")
				dynamic_cast<Collider*>(component)->size.x = std::stof(value); 		break;
	}
	GoInspectorRefresh();
	isSaved = false;
}

void		UI::ComponentPropertyEditCol2(const Glib::ustring& index, const Glib::ustring& value)
{
	switch (std::stoi(index))
	{
		case 1:
			if (component->type == "Collider")
				dynamic_cast<Collider*>(component)->center.y = std::stof(value); 	break;
		
		case 2:
			if (component->type == "Collider")
				dynamic_cast<Collider*>(component)->size.y = std::stof(value); 		break;
	}
	GoInspectorRefresh();
	isSaved = false;
}

void		UI::ComponentPropertyEditCol3(const Glib::ustring& index, const Glib::ustring& value)
{
	switch (std::stoi(index))
	{
		case 1:
			if (component->type == "Collider")
				dynamic_cast<Collider*>(component)->center.z = std::stof(value); 	break;
		
		case 2:
			if (component->type == "Collider")
				dynamic_cast<Collider*>(component)->size.z = std::stof(value); 		break;
	}
	GoInspectorRefresh();
	isSaved = false;
}






// OTHER //

void 		UI::UnselectTreeView( Gtk::TreeView *treeView )
{
	update = false;
	Gtk::TreeModel::iterator selection = treeView->get_selection()->get_selected();
	if (selection)
		treeView->get_selection()->unselect(selection);
	update = true;
}

void 		UI::ClearListStore( Glib::RefPtr<Gtk::ListStore> list )
{
	update = false;
	if (list)
		list->clear();
	update = true;
}

void		UI::run()
{
	GtkApp->run(*window);
}

bool		UI::del(GdkEventKey *e)
{
	std::cout << e->keyval << std::endl;
	return true;
}

std::string		UI::FinderGetFile(std::string folder, std::string extensionPattern)
{
	Glib::RefPtr< Gtk::FileFilter > filterDae = Gtk::FileFilter::create() ;
	filterDae->set_name(extensionPattern);
	filterDae->add_pattern(extensionPattern);

	Gtk::FileChooserDialog finder("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
	finder.set_transient_for(*window);
	finder.set_current_folder(folder);
	finder.add_filter(filterDae);
	finder.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	finder.add_button("Select", Gtk::RESPONSE_OK);

	if (finder.run() == Gtk::RESPONSE_OK)
		return finder.get_filename();

	return "";
}

std::string		UI::PopupGetText(std::string win_name, std::string label, const Glib::ustring warn)
{
	int		ret;
	Popup	pop = Popup(win_name, window, label);
	while ((ret = pop.run()) != Gtk::RESPONSE_CANCEL)
	{
		if (ret == Gtk::RESPONSE_OK && pop.getText().length())
			return pop.getText();
		else
		{
			Gtk::MessageDialog warning(*window, warn, true, Gtk::MESSAGE_WARNING);
			warning.run();
		}
	}
	return std::string("");
}

bool			UI::PopupGetConfirm(std::string win_name, std::string question)
{
	int		ret;
	
	PopupConfirmation confim(win_name, window, question);
	while ((ret = confim.run()) != Gtk::RESPONSE_CANCEL)
	{
		if (ret == Gtk::RESPONSE_OK)
			return true;
	}
	return false;
}

void			UI::PopWarning(const Glib::ustring warn)
{
	Gtk::MessageDialog warning(*window, warn, true, Gtk::MESSAGE_WARNING);
	warning.run();
}


void			UI::OnQuitEditor()
{
	if (isSaved == false && PopupGetConfirm("Quit Editor", 
		"\tSome change has not been saved.\n\n\tWould you like to save it ?") == true)
		app->Save();
}

void			UI::ReplaceScriptName(std::string oldName, std::string newName)
{
	Script *script;

	for(GameObject* prefab : app->GetListPrefab())
	{
		for (IComponent* compo : prefab->GetListComponent())
		{
			if ((script = dynamic_cast<Script*>(compo)) && script->name == oldName)
				script->name = newName;
		}
	}

	for (Scene* scene : app->GetListScene())
	{
		for(GameObject* go : scene->GetBindGameObjectList())
		{
			for (IComponent* compo : go->GetListComponent())
			{
				if ((script = dynamic_cast<Script*>(compo)) && script->name == oldName)
					script->name = newName;
			}
		}
		for(GameObject* go : scene->GetGameObjectList())
		{
			for (IComponent* compo : go->GetListComponent())
			{
				if ((script = dynamic_cast<Script*>(compo)) && script->name == oldName)
					script->name = newName;
			}
		}
	}
}

std::string		UI::FileGetName(std::string& filePath)
{
	size_t lastSeparator;
 	
 	lastSeparator = filePath.find_last_of("/");
 	
 	return filePath.substr(lastSeparator + 1);
}

std::string		UI::FileGetPath(std::string& filePath)
{
	size_t lastSeparator;
 	
 	lastSeparator = filePath.find_last_of("/");
  	if (lastSeparator == std::string::npos)
  		return "";
 	
 	return filePath.substr(0, lastSeparator);
}

void 			UI::ApplicationRemoveScripts(std::string name)
{
	std::list<GameObject*>	gameObjects = app->GetListPrefab();
	std::list<GameObject*>::iterator it = gameObjects.begin();
	for(; it != gameObjects.end() ; it++)
		(*it)->DeleteComponent(name);

	std::list<Scene*> scenes = app->GetListScene();
	std::list<Scene*>::iterator it_scene = scenes.begin();

	for (; it_scene != scenes.end(); it_scene++)
	{
		gameObjects = (*it_scene)->GetBindGameObjectList();
		it = gameObjects.begin();
		for(; it != gameObjects.end() ; it++)
			(*it)->DeleteComponent(name);
		
		gameObjects = (*it_scene)->GetGameObjectList();
		it = gameObjects.begin();
		for(; it != gameObjects.end() ; it++)
			(*it)->DeleteComponent(name);
	}
}

void		UI::DeleteFile(std::string file)
{
	std::ofstream Ocppfile(file);
	if (Ocppfile.is_open())
		Ocppfile.close();
	else
	{
		PopWarning("Cannot find file: " + file);
		return ;
	}

	FILE *in;
    char buff[512];
    std::string cmdReturn;

	in = popen(("git ls-files " + file + ".cpp").c_str(), "r");

	while(fgets(buff, sizeof(buff), in)!=NULL)
	    cmdReturn += buff;
	pclose(in);

	if (cmdReturn.length() > 0)
	{
		std::cout << "git rm -f " + file << std::endl;
		system(("git rm -f " + file).c_str());
	}
	else
	{
		std::cout << "rm -f " + file << std::endl;
		std::remove((file).c_str());
	}
}

int main(int ac, char **av)
{
	try 
	{
		Builder 	builder;

		if (ac == 2)
		{
			UI			ui(builder.Build(av[1]), std::string(av[1]));
			ui.run();
		}
		else
		{
			UI			ui(new Application("<AppName>"));
			ui.run();
		}

	}
	catch (DError & e ) {
		std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) << C_DEFAULT << std::endl;
	}
	return 0;
}
