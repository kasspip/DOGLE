#include "UI.hpp"
#include <string>

Scene*			UI::scene = nullptr;
GameObject*		UI::gameObject = nullptr;
IComponent*		UI::component = nullptr;

// CONSTRUCTOR DESTRUCTOR //


UI::UI(Application *app) : AppInspectorList(0),
							AppPrefabList(0),
							app(app)
{

	GtkApp = Gtk::Application::create("GTK");
	builder = Gtk::Builder::create_from_file("src/EditorClass/unity_gtk.glade");
	builder->get_widget("window1", window);
	
	AppInspectorDisplay();
	SceneInspectorDisplay();
  	GoInspectorDisplay();
	AppPrefabDisplay();
	AppSceneDisplay();
	SceneListDisplay();
	GoComponentsDisplay();
	ComponentPropertyDisplay();

	update = true;

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
	std::cout << "APPLICATION LOAD BUTTON NOT IMPLEMENTED" << std::endl;
	// // Glib::RefPtr<Gtk::Application> finder = Gtk::Application::create("org.gtkmm.example");
	// FileFinder						fileFinder;

	// GtkApp->add_window(fileFinder);
	// GtkApp->run(fileFinder);
}

void		UI::ButtonSaveApp()
{
	if (app)
		app->Save();
}

void		UI::AppInspectorDisplay()
{
	builder->get_widget("treeview1", AppInspectorTreeView);
	AppInspectorList = Gtk::ListStore::create(model);
	AppInspectorTreeView->set_model(AppInspectorList);
	
	AppInspectorTreeView->append_column("Inspector", model.m_col_name);
	AppInspectorTreeView->append_column_editable("", model.value_1);
	AppInspectorTreeView->get_column_cell_renderer(0)->set_fixed_size(100,0);

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

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(AppInspectorTreeView->get_column_cell_renderer(1));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::AppInspectorEdit));
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
	
	for (GameObject* go : app->GetListPrefab())
	{
		Gtk::TreeModel::iterator iter = AppPrefabList->append();
		(*iter)[model2.m_col_name] = go->name;
		(*iter)[model2.del] = false;
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
			break ;
		}
		else
		{
			Gtk::MessageDialog warning(*this->window, "<b>You must specify a GameObject name !</b>", true, Gtk::MESSAGE_WARNING);
			warning.run();
		}
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

	for (Scene* scene : app->GetListScene())
	{
		Gtk::TreeModel::iterator iter = AppScenesList->append();
		(*iter)[model2.m_col_name] = scene->name;
		(*iter)[model2.del] = false;
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
  		try {
  			scene = app->FindScene( ss.str() );
  		}
  		catch (DError & e ) {
  			std::cout << "app->FindScene() failed" << std::endl;
  		}
  		GoInspectorRefresh();
  		SceneInspectorRefresh();
  		SceneListRefresh();
	}
}

void		UI::ButtonNewScene()
{
	int		ret;
	Popup	pop = Popup("New Scene", this->window, "Name:");

	while ((ret = pop.run()) != Gtk::RESPONSE_CANCEL)
	{
		if (ret == Gtk::RESPONSE_OK && pop.getText().length())
		{
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
			(*newRow)[model2.m_col_name] = pop.getText();
			(*newRow)[model2.del] = false;
			app->AddScene(new Scene(pop.getText()));
			break ;
		}
		else
		{
			Gtk::MessageDialog warning(*this->window, "<b>You must specify a Scene name !</b>", true, Gtk::MESSAGE_WARNING);
			warning.run();
		}
	}
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
	 	try {
 	  		gameObject = scene->FindGameObject( ss.str() );
	 	}
	 	catch (DError & e) {
	 		std::cout << "scene->FindGameObject() failed." << std::endl;
	 	}
	 	GoInspectorRefresh();
	}
}

void		UI::ButtonNewInstance()
{
	int			ret;
	GameObject 	*prefab;

	if (!scene)
	{
		std::cout << "No Scene Selected." << std::endl;
		return;
	}
	PopupInstancePrefab	popup = PopupInstancePrefab(this->window, app);
	int i = 0;
	while ((ret = popup.run()) != Gtk::RESPONSE_CANCEL)
	{
		if ((prefab = popup.GetSelection()) != nullptr)
		{
			scene->InstanciatePrefab(prefab);
			SceneListRefresh();
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
	std::cout << "SCENE DELETE BUTTON NOT IMPLEMENTED" << std::endl;
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
	GameObjectInspectorTreeView->get_column_cell_renderer(2)->set_fixed_size(25,0);
	GameObjectInspectorTreeView->get_column_cell_renderer(3)->set_fixed_size(25,0);
	GameObjectInspectorTreeView->get_column_cell_renderer(4)->set_fixed_size(25,0);

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
}

void		UI::ButtonNewComponent()
{
	std::cout << "COMPONENT NEW BUTTON NOT IMPLEMENTED" << std::endl;
}

void		UI::ButtonDeleteComponent()
{
	std::cout << "COMPONENT NEW BUTTON NOT IMPLEMENTED" << std::endl;
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

	for (IComponent* compo : gameObject->GetListComponent())
	{
		if (compo->type == "Transform")
			continue ;
		Gtk::TreeModel::iterator newRow = GameObjectComponentsList->append();
		(*newRow)[model2.m_col_name] = compo->type;
		(*newRow)[model2.del] = false;
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
		
	 	// 1 - add here and create <name>PropertyRefresh()
		if (type == "Skin")
	 		SkinPropertyRefresh();
	 	else if (type == "Camera")
	 		CameraPropertyRefresh();
	 	else if (type == "Light")
	 		LightPropertyRefresh();
	}
}






// COMPONENT PROPERTY //


void		UI::ComponentPropertyDisplay()
{
	builder->get_widget("treeview8", ComponentPropertyTreeView);
	ComponentPropertyList = Gtk::ListStore::create(model);
	
	ComponentPropertyTreeView->set_model(ComponentPropertyList);
	ComponentPropertyTreeView->append_column("Properties:", model.m_col_name);
	ComponentPropertyTreeView->append_column_editable("", model.value_1);
	ComponentPropertyTreeView->get_column_cell_renderer(0)->set_fixed_size(100,0);

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(ComponentPropertyTreeView->get_column_cell_renderer(1));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::ComponentPropertyEdit));
}

void		UI::SkinPropertyRefresh()
{
	Skin* skin;
	try {
 	  	skin = gameObject->GetComponent<Skin>();
 	  	component = skin;
	}catch (DError & e) {
	 	std::cout << "gameObject->GetComponent<Skin>() failed." << std::endl;
	}
	
	Gtk::TreeModel::iterator row;
	std::stringstream ss;

	row = ComponentPropertyList->append();
	(*row)[model.m_col_name] = "3DFile";
	ss << skin->dae_file;
	(*row)[model.value_1] = ss.str();
	ss.str(std::string());

}

void		UI::CameraPropertyRefresh()
{
	Camera* camera;
	try {
 	  	camera = gameObject->GetComponent<Camera>();
 	  	component = camera;
	}catch (DError & e) {
	 	std::cout << "gameObject->GetComponent<Camera>() failed." << std::endl;
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
	try {
 	  	light = gameObject->GetComponent<Light>();
 	  	component = light;
	}catch (DError & e) {
	 	std::cout << "gameObject->GetComponent<Light>() failed." << std::endl;
	}
	
	Gtk::TreeModel::iterator row;
	std::stringstream ss;

	// row = ComponentPropertyList->append();
	// (*row)[model.m_col_name] = "3DFile";
	// ss << skin->dae_file;
	// (*row)[model.value_1] = ss.str();
	// ss.str(std::string());

}

void		UI::ComponentPropertyEdit(const Glib::ustring& index, const Glib::ustring& value)
{
	switch (std::stoi(index))
	{
		// add here on edit	
		case 0:
			if (component->type == "Skin")
				dynamic_cast<Skin*>(component)->dae_file = value;	
			else if (component->type == "Camera")
				dynamic_cast<Camera*>(component)->fov = std::stof(value); 		break;
		case 1:
			if (component->type == "Camera")
				dynamic_cast<Camera*>(component)->clipNear = std::stof(value); 	break;
		
		case 2:
			if (component->type == "Camera")
				dynamic_cast<Camera*>(component)->clipFar = std::stof(value); 	break;
	}
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







int main(int ac, char **av)
{
	Builder 	builder;

	try 
	{
		if (ac == 2)
		{
			UI			ui(builder.Build(av[1]));
			ui.run();
		}
		else
			std::cout << "Usage: " << av[0] << " <.dogle file>";
	}
	catch (DError & e )
	{
		std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) 
					<< C_DEFAULT << std::endl;
	}
	return 0;
}
