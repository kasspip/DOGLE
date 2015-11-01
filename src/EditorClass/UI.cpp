#include "UI.hpp"
#include <string>

GameObject*	UI::gameObject = nullptr;
Scene*		UI::scene = nullptr;

// CONSTRUCTOR DESTRUCTOR //


UI::UI(Application *app) : AppListStoreInspector(0),
							AppListStoreGo(0),
							app(app)
{

	GtkApp = Gtk::Application::create("jean.michel");
	builder = Gtk::Builder::create_from_file("src/EditorClass/unity_gtk.glade");
	builder->get_widget("window1", window);
	
	AppInspectorDisplay();
	SceneInspectorDisplay();
  	GoInspectorDisplay();

	AppPrefabDisplay();
	AppSceneDisplay();
	SceneListDisplay();


	// AppListStoreInspectorview->add_events(Gdk::KEY_PRESS_MASK);
	// AppListStoreInspectorview->signal_key_press_event().connect(sigc::mem_fun(*this, &UI::del));

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
	std::cout << "APPLICATION LOAD BUTTON" << std::endl;
	// Glib::RefPtr<Gtk::TreeSelection>		tmp;
	// Gtk::ListStore::iterator 				it;

	// Gtk::ListStore::iterator 		tmp;
	// tmp = AppListStoreInspector->get_iter("0");

	// while (tmp)
	// {
	// 	if ((*tmp)[model.del])
	// 		tmp = AppListStoreInspector->erase(tmp);
	// 	else
	// 		tmp++;
	// }

	// tmp = AppListStoreInspectorview->get_selection();
	// tmp->signal_changed().connect(sigc::mem_fun(*this, &UI::button_new_func));
	// it = tmp->get_selected();
	// std::cout << (*it)[model.m_col_name] << std::endl;
}

void		UI::ButtonSaveApp()
{
	if (app)
		app->Save();
}

void		UI::AppInspectorDisplay()
{
	builder->get_widget("treeview1", AppListStoreInspectorview);
	AppListStoreInspector = Gtk::ListStore::create(model);
	AppListStoreInspectorview->set_model(AppListStoreInspector);
	
	AppListStoreInspectorview->append_column("               ", model.m_col_name);
	AppListStoreInspectorview->append_column_editable("               ", model.m_col_value);

	Gtk::TreeModel::iterator newRow = AppListStoreInspector->append();
	(*newRow)[model.m_col_name] = "NAME";
	(*newRow)[model.m_col_value] = app->name;
	
	newRow = AppListStoreInspector->append();
	(*newRow)[model.m_col_name] = "WIN HEIGHT";
	std::stringstream winHVal;
	winHVal << app->winH;
	(*newRow)[model.m_col_value] = winHVal.str();

	newRow = AppListStoreInspector->append();
	(*newRow)[model.m_col_name] = "WIN WIDTH";
	std::stringstream winWVal;
	winWVal << app->winW;
	(*newRow)[model.m_col_value] = winWVal.str();

	newRow = AppListStoreInspector->append();
	(*newRow)[model.m_col_name] = "FPS";
	std::stringstream FPSVal;
	FPSVal << app->FPS;
	(*newRow)[model.m_col_value] = FPSVal.str();

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(AppListStoreInspectorview->get_column_cell_renderer(1));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::AppInspectorEdit));
}

void		UI::AppInspectorEdit(const Glib::ustring& index, const Glib::ustring& value)
{
	switch (std::stoi(index))
	{
		case 0:
			app->name = value;		
			break;
		case 1:
			app->winW = std::stoi(value);
			break;
		case 2:
			app->winH = std::stoi(value);
			break;
		case 3:
			app->FPS = std::stoi(value);
			break;
	}
}



// APP PREFAB LIST //



void		UI::AppPrefabDisplay()
{
	builder->get_widget("treeview2", AppListStoreGoview);
	AppListStoreGo = Gtk::ListStore::create(model2);
	AppListStoreGoview->set_model(AppListStoreGo);
	AppListStoreGoview->append_column_editable("Prefabs :", model2.m_col_name);
	AppListStoreGoview->append_column_editable("", model2.del);
	
	for (GameObject* go : app->GetListPrefab())
	{
		Gtk::TreeModel::iterator iter = AppListStoreGo->append();
		(*iter)[model2.m_col_name] = go->name;
		(*iter)[model2.del] = false;
	}

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(AppListStoreGoview->get_column_cell_renderer(0));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::AppPrefabListEdit));

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = AppListStoreGoview->get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &UI::AppPrefabSelection));
}

void		UI::AppPrefabRefresh()
{
	Gtk::TreeModel::Children children = AppListStoreGoview->get_model()->children();
	Gtk::TreeModel::Children::iterator iter = children.begin();
	if (children.size() > 0)
	{
		for (GameObject* go : app->GetListPrefab())
		{
			(*iter)[model2.m_col_name] = go->name;
			if (iter == children.end())
				break;
			iter++;
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
}

void		UI::AppPrefabSelection()
{
	Glib::RefPtr<Gtk::TreeSelection> treeSelection = AppListStoreGoview->get_selection();
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
	Popup	pop = Popup("New game object", this->window, "Choose a prefab name:");

	while ((ret = pop.run()) != Gtk::RESPONSE_CANCEL)
	{
		if (ret == Gtk::RESPONSE_OK && pop.getText().length())
		{
			if (!AppListStoreGo)
			{
				builder->get_widget("treeview2", AppListStoreGoview);
				AppListStoreGo = Gtk::ListStore::create(model2);
				AppListStoreGoview->set_model(AppListStoreGo);
				AppListStoreGoview->append_column_editable("Prefabs :",model2.m_col_name);
				AppListStoreGoview->append_column_editable("",model2.del);
			}
			Gtk::TreeModel::iterator newRow = AppListStoreGo->append();
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
	std::cout << "PREFAB NEW BUTTON" << std::endl;
}


// APP SCENE LIST //


void		UI::AppSceneDisplay()
{
	builder->get_widget("treeview3", AppListStoreSceneview);
	AppListStoreScene = Gtk::ListStore::create(model2);
	AppListStoreSceneview->set_model(AppListStoreScene);
	AppListStoreSceneview->append_column_editable("Scenes :",model2.m_col_name);
	AppListStoreSceneview->append_column_editable("",model2.del);
	for (Scene* scene : app->GetListScene())
	{
		Gtk::TreeModel::iterator iter = AppListStoreScene->append();
		(*iter)[model2.m_col_name] = scene->name;
		(*iter)[model2.del] = false;
	}

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(AppListStoreSceneview->get_column_cell_renderer(0));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::AppSceneListEdit));

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = AppListStoreSceneview->get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &UI::AppSceneSelection));
}

void		UI::AppSceneRefresh()
{
	Gtk::TreeModel::Children children = AppListStoreSceneview->get_model()->children();
	Gtk::TreeModel::Children::iterator iter = children.begin();
	if (children.size() > 0)
	{
		for (Scene* scene : app->GetListScene())
		{
			(*iter)[model2.m_col_name] = scene->name;
			if (iter == children.end())
				break;
			iter++;
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
}

void		UI::AppSceneSelection()
{
	Glib::RefPtr<Gtk::TreeSelection> treeSelection = AppListStoreSceneview->get_selection();
	Gtk::TreeModel::iterator selection = treeSelection->get_selected();
	// if(selectionGameObject)
	// 	treeViewSceneList->get_selection()->unselect(selectionGameObject);
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
  		SceneInspectorRefresh();
  		SceneListRefresh();
	}
}

void		UI::ButtonNewScene()
{
	std::cout << "SCENE NEW BUTTON" << std::endl;
}

void		UI::ButtonDeleteScene()
{
	std::cout << "SCENE DELETE BUTTON" << std::endl;
}



// SCENE PANEL //



void		UI::SceneInspectorDisplay()
{
	builder->get_widget("treeview4", treeViewSceneInspector);
	treeSceneInspector = Gtk::ListStore::create(model);
	
	treeViewSceneInspector->set_model(treeSceneInspector);
	treeViewSceneInspector->append_column("", model.m_col_name);
	treeViewSceneInspector->append_column_editable("", model.m_col_value);

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(treeViewSceneInspector->get_column_cell_renderer(1));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::SceneInspectorEdit));
}

void		UI::SceneInspectorRefresh()
{
	if (scene)
	{	
		Gtk::TreeModel::Children children = treeViewSceneInspector->get_model()->children();
		Gtk::TreeModel::Children::iterator iter = children.begin();
		if (children.size() == 0)
		{
			Gtk::TreeModel::iterator row = treeSceneInspector->append();
			(*row)[model.m_col_name] = "NAME";
			(*row)[model.m_col_value] = scene->name;
		}
		else
			(*iter)[model.m_col_value] = scene->name;
	}
}

void		UI::SceneInspectorEdit(const Glib::ustring& index, const Glib::ustring& value)
{
	switch (std::stoi(index))
	{
		case 0:
			scene->name = value;		
			break;
	}
	AppSceneRefresh();
}

void		UI::ButtonNewInstance()
{
	std::cout << "SCENE INSTANCIATE BUTTON" << std::endl;
}

void		UI::ButtonDeleteInstance()
{
	std::cout << "SCENE DELETE BUTTON" << std::endl;
}



// SCENE GAMEOBJECTS LIST //



void		UI::SceneListDisplay()
{
	builder->get_widget("treeview5", treeViewSceneList);
	treeSceneList = Gtk::ListStore::create(model2);
	
	treeViewSceneList->set_model(treeSceneList);
	treeViewSceneList->append_column_editable("GameObjects :\t\t",model2.m_col_name);
	treeViewSceneList->append_column_editable("",model2.del);
	
	Glib::RefPtr<Gtk::TreeSelection> treeSelection = treeViewSceneList->get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &UI::SceneListSelection));

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(treeViewSceneList->get_column_cell_renderer(0));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::SceneListEdit));
}

void		UI::SceneListRefresh()
{
	//std::cout << "test-1 " << gameObject->name << std::endl;
	treeSceneList->clear();
	//std::cout << "test-2 " << gameObject->name << std::endl;

	for (GameObject* go : scene->GetBindGameObjectList())
	{
		Gtk::TreeModel::iterator newRow = treeSceneList->append();
		(*newRow)[model2.m_col_name] = go->name;
		(*newRow)[model2.del] = false;
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
	selectionGameObject = treeViewSceneList->get_selection()->get_selected();
	
	if(selectionGameObject)
	{
	 	std::stringstream ss;
	 	ss << (*selectionGameObject)[model2.m_col_name];
	 	try {
 	  		gameObject = scene->FindGameObject( ss.str() );
	 	}
	 	catch (DError & e) {
	 		std::cout << "scene->FindGameObject() failed." << std::endl;
	 	}
	 	GoInspectorRefresh();
	}
}



// GAMEOBJECT PANEL //



void		UI::GoInspectorDisplay()
{
	builder->get_widget("treeview6", treeViewGameObjectInspector);
	treeGameObjectInspector = Gtk::ListStore::create(model);
	
	treeViewGameObjectInspector->set_model(treeGameObjectInspector);
	treeViewGameObjectInspector->append_column("", model.m_col_name);
	treeViewGameObjectInspector->append_column_editable("", model.m_col_value);

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(treeViewGameObjectInspector->get_column_cell_renderer(1));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::GoInspectorEdit));
}

void		UI::GoInspectorRefresh()
{
	if (gameObject)
	{	
		Gtk::TreeModel::Children children = treeViewGameObjectInspector->get_model()->children();
		Gtk::TreeModel::Children::iterator iter = children.begin();
		if (children.empty())
		{
			Gtk::TreeModel::iterator row = treeGameObjectInspector->append();
			(*row)[model.m_col_name] = "NAME";
			(*row)[model.m_col_value] = gameObject->name;
		}
		else
			(*iter)[model.m_col_value] = gameObject->name;
	}
}

void		UI::GoInspectorClear()
{
	treeGameObjectInspector->clear();


}

void		UI::GoInspectorEdit(const Glib::ustring& index, const Glib::ustring& value)
{
	switch (std::stoi(index))
	{
		case 0:
			gameObject->name = value;		
			break;
	}
	if (gameObject->IsPrefab())
		AppPrefabRefresh();
	else
		SceneListRefresh();
}

void		UI::ButtonNewComponent()
{
	std::cout << "COMPONENT NEW BUTTON" << std::endl;
}

void		UI::ButtonDeleteComponent()
{
	std::cout << "COMPONENT NEW BUTTON" << std::endl;
}



// OTHER //

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
