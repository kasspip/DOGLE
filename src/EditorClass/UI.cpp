#include "UI.hpp"
#include <string>

// CONSTRUCTOR DESTRUCTOR //


UI::UI(Application *app) : AppListStoreInspector(0),
							AppListStoreGo(0),
							app(app)
{
	gameObject = nullptr;

	GtkApp = Gtk::Application::create("jean.michel");
	builder = Gtk::Builder::create_from_file("src/EditorClass/unity_gtk.glade");
	builder->get_widget("window1", window);
	
	AppInspectorDisplay();
	AppPrefabDisplay();
	AppSceneDisplay();
  	GoInspectorDispay();


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

UI::~UI(){}


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
	
	Gtk::TreeModel::iterator 		tmp;
	tmp = AppListStoreInspector->append();
	
	(*tmp)[model.m_col_name] = "NAME";
	(*tmp)[model.m_col_value] = app->name;
	
	AppListStoreInspectorview->append_column("______________ATTRIBUTS______________", model.m_col_name);
	AppListStoreInspectorview->append_column_editable("_______________VALUES_______________", model.m_col_value);

	tmp = AppListStoreInspector->append();
	(*tmp)[model.m_col_name] = "WIN HEIGHT";
	std::stringstream winHVal;
	winHVal << app->winH;
	(*tmp)[model.m_col_value] = winHVal.str();

	tmp = AppListStoreInspector->append();
	(*tmp)[model.m_col_name] = "WIN WIDTH";
	std::stringstream winWVal;
	winWVal << app->winW;
	(*tmp)[model.m_col_value] = winWVal.str();

	tmp = AppListStoreInspector->append();
	(*tmp)[model.m_col_name] = "FPS";
	std::stringstream FPSVal;
	FPSVal << app->FPS;
	(*tmp)[model.m_col_value] = FPSVal.str();

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

void		UI::AppPrefabDisplay()
{
	builder->get_widget("treeview2", AppListStoreGoview);
	AppListStoreGo = Gtk::ListStore::create(model2);
	AppListStoreGoview->set_model(AppListStoreGo);
	AppListStoreGoview->append_column_editable("______________PREFABS______________", model2.m_col_name);
	AppListStoreGoview->append_column_editable("_______________SELECT_______________", model2.del);
	
	for (GameObject* go : app->GetListPrefab())
	{
		AppListStoreGoIt = AppListStoreGo->append();
		(*AppListStoreGoIt)[model2.m_col_name] = go->name;
		(*AppListStoreGoIt)[model2.del] = false;
	}

	Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(AppListStoreGoview->get_column_cell_renderer(0));
	cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::AppPrefabListEdit));

	Glib::RefPtr<Gtk::TreeSelection> treeSelection = AppListStoreGoview->get_selection();
	treeSelection->signal_changed().connect(sigc::mem_fun(*this, &UI::AppPrefabSelection));
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
				AppListStoreGoview->append_column_editable("______________ATTRIBUTS______________",model2.m_col_name);
				AppListStoreGoview->append_column_editable("_______________SELECT_______________",model2.del);
			}
			AppListStoreGoIt = AppListStoreGo->append();
			(*AppListStoreGoIt)[model2.m_col_name] = pop.getText();
			(*AppListStoreGoIt)[model2.del] = false;
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

void		UI::AppSceneDisplay()
{
	builder->get_widget("treeview3", AppListStoreSceneview);
	AppListStoreScene = Gtk::ListStore::create(model2);
	AppListStoreSceneview->set_model(AppListStoreScene);
	AppListStoreSceneview->append_column_editable("______________ATTRIBUTS______________",model2.m_col_name);
	AppListStoreSceneview->append_column_editable("_______________SELECT_______________",model2.del);
	for (Scene* scene : app->GetListScene())
	{
		AppListStoreSceneIt = AppListStoreScene->append();
		(*AppListStoreSceneIt)[model2.m_col_name] = scene->name;
		(*AppListStoreSceneIt)[model2.del] = false;
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


void		UI::ButtonNewInstance()
{
	std::cout << "SCENE INSTANCIATE BUTTON" << std::endl;
}

void		UI::ButtonDeleteInstance()
{
	std::cout << "SCENE DELETE BUTTON" << std::endl;
}


// GAMEOBJECT PANEL //

void		UI::GoInspectorDispay()
{
	builder->get_widget("treeview6", treeViewGameObjectInspector);
	treeGameObjectInspector = Gtk::ListStore::create(model);
	
	treeViewGameObjectInspector->set_model(treeGameObjectInspector);
	treeViewGameObjectInspector->append_column("______________ATTRIBUTS______________", model.m_col_name);
	treeViewGameObjectInspector->append_column_editable("_______________VALUES_______________", model.m_col_value);
	
	Gtk::TreeModel::iterator 		row;
	
	row = treeGameObjectInspector->append();
	(*row)[model.m_col_name] = "NAME";
	(*row)[model.m_col_value] = "";
	//Gtk::CellRendererText*  cellText = static_cast<Gtk::CellRendererText*>(AppListStoreInspectorview->get_column_cell_renderer(1));
	//cellText->signal_edited().connect(sigc::mem_fun(*this, &UI::AppInspectorEdit));
}

void		UI::GoInspectorRefresh()
{
	if (gameObject)
	{	
		//Gtk::TreeModel::iterator row = treeGameObjectInspector-> ;

	}
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
