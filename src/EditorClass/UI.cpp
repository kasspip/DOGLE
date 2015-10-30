#include "UI.hpp"

bool		UI::del(GdkEventKey *e)
{
	std::cout << e->keyval << std::endl;
	return true;
}

UI::UI(Application *app) : AppListStoreInspector(0),
							AppListStoreGo(0),
							app(app)
{
	GtkApp = Gtk::Application::create("jean.michel");
	builder = Gtk::Builder::create_from_file("src/EditorClass/unity_gtk.glade");
	builder->get_widget("window1", window);
	displayApp();
	displayGo();
	displayScene();


	// AppListStoreInspectorview->add_events(Gdk::KEY_PRESS_MASK);
	// AppListStoreInspectorview->signal_key_press_event().connect(sigc::mem_fun(*this, &UI::del));



	/*APPLICATION NEW BUTTON*/
	Gtk::Button	*new_button;
	builder->get_widget("button1", new_button);
	new_button->signal_clicked().connect(sigc::mem_fun(*this, &UI::button_new_func));

	/*APPLICATION LOAD BUTTON*/
	Gtk::Button	*loadButton;
	builder->get_widget("button2", loadButton);
	loadButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::button_load_func));

	/*APPLICATION SAVE BUTTON*/
	Gtk::Button	*saveButton;
	builder->get_widget("button3", saveButton);
	saveButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::button_save_func));

	/*APPLICATION GO NEW BUTTON*/
	Gtk::Button	*GoNewButton;
	builder->get_widget("button4", GoNewButton);
	GoNewButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::button_GoNew_func));

	/*APPLICATION SCENE NEW BUTTON*/
	Gtk::Button	*SceneNewButton;
	builder->get_widget("button5", SceneNewButton);
	SceneNewButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::button_SceneNew_func));

	/*SCENE INSTANCIATE BUTTON*/
	Gtk::Button	*SceneInstanciateButton;
	builder->get_widget("button6", SceneInstanciateButton);
	SceneInstanciateButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::button_SceneInstanciateButton_func));

	/*GAME OBJECT NEW BUTTON*/
	Gtk::Button	*GameObjectNewButton;
	builder->get_widget("button7", GameObjectNewButton);
	GameObjectNewButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::button_GameObjectNewButton_func));
}

UI::~UI(){}

 // void cellrenderer_validated_on_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);

void		UI::EditList(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
	(void)path_string;
	std::cout << new_text << std::endl;
}

void		UI::displayApp()
{
	builder->get_widget("treeview1", AppListStoreInspectorview);
	AppListStoreInspector = Gtk::ListStore::create(model);
	AppListStoreInspectorview->set_model(AppListStoreInspector);
	Gtk::TreeModel::iterator 		tmp;
	tmp = AppListStoreInspector->append();
	(*tmp)[model.m_col_name] = "NAME";
	(*tmp)[model.m_col_value] = app->name;
	AppListStoreInspectorview->append_column("______________ATTRIBUTS______________",model.m_col_name);
	AppListStoreInspectorview->append_column_editable("_______________VALUES_______________",model.m_col_value);

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

	// Glib::RefPtr<Gtk::TreeSelection>		tmp2;
	// Gtk::ListStore::iterator 				it;
	// tmp2 = AppListStoreInspector->get_iter("0");
	// tmp2 = AppListStoreInspectorview->get_selection();

	// AppListStoreInspectorview->get_column_cell_renderer(0)->property_editable() = true;
	Gtk::CellRendererText*  tmp2 = static_cast<Gtk::CellRendererText*>(AppListStoreInspectorview->get_column_cell_renderer(1));
	tmp2->signal_edited().connect(sigc::mem_fun(*this, &UI::EditList));
	// (*tmp)[model.m_col_value].signal_edited().connect( sigc::mem_fun(*this, &UI::EditList));

}

void		UI::button_new_func()
{
	int		ret;
	Popup	pop = Popup("New app", this->window, "Choose an application name:");

	while ((ret = pop.run()) != Gtk::RESPONSE_CANCEL)
	{
		if (ret == Gtk::RESPONSE_OK && pop.getText().length())
		{
			app = new Application(pop.getText());
			displayApp();
			break ;
		}
		else
		{
			Gtk::MessageDialog warning(*this->window, "<b>You must specify a valid app name !</b>", true, Gtk::MESSAGE_WARNING);
			warning.run();
		}
	}
}

void		UI::button_load_func()
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

void		UI::button_save_func()
{
	std::cout << "APPLICATION SAVE BUTTON" << std::endl;
}

void		UI::displayGo()
{
	builder->get_widget("treeview2", AppListStoreGoview);
	AppListStoreGo = Gtk::ListStore::create(model2);
	AppListStoreGoview->set_model(AppListStoreGo);
	AppListStoreGoview->append_column_editable("______________ATTRIBUTS______________",model2.m_col_name);
	AppListStoreGoview->append_column_editable("_______________SELECT_______________",model2.del);
	for (GameObject* go : app->GetListPrefab())
	{
		AppListStoreGoIt = AppListStoreGo->append();
		(*AppListStoreGoIt)[model2.m_col_name] = go->name;
		(*AppListStoreGoIt)[model2.del] = false;
	}
}

void		UI::button_GoNew_func()
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

void		UI::displayScene()
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

void		UI::button_SceneNew_func()
{
	std::cout << "APPLICATION SCENE NEW BUTTON" << std::endl;
}

void		UI::button_SceneInstanciateButton_func()
{
	std::cout << "SCENE INSTANCIATE BUTTON" << std::endl;
}

void		UI::button_GameObjectNewButton_func()
{
	std::cout << "GAME OBJECT NEW BUTTON" << std::endl;
}

void		UI::run()
{
	GtkApp->run(*window);
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
