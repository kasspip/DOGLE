#include "UI.hpp"


UI::UI(int ac, char **av)
{
	GtkApp = Gtk::Application::create(ac, av, "jean.michel");
	builder = Gtk::Builder::create_from_file("unity_gtk.glade");
	builder->get_widget("window1", window);
	Gtk::Button	*new_button;
	builder->get_widget("button1", new_button);
	new_button->signal_clicked().connect(sigc::mem_fun(*this, &UI::button_new_func));

	Gtk::Button	*loadButton;
	builder->get_widget("button2", loadButton);
	loadButton->signal_clicked().connect(sigc::mem_fun(*this, &UI::button_load_func));
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
			builder->get_widget("treeview1", AppListStoreInspectorview);
			AppListStoreInspector = Gtk::ListStore::create(model);
			AppListStoreInspectorview->set_model(AppListStoreInspector);
			Gtk::TreeModel::iterator 		tmp;
			tmp = AppListStoreInspector->append();
			(*tmp)[model.m_col_name] = "blabla";
			(*tmp)[model.m_col_value] = "toto";
			(*tmp)[model.del] = false;
			AppListStoreInspectorview->append_column_editable("",model.m_col_name);
			AppListStoreInspectorview->append_column_editable("",model.m_col_value);
			AppListStoreInspectorview->append_column_editable("",model.del);
			tmp = AppListStoreInspector->append();
			(*tmp)[model.m_col_name] = "blabla2";
			(*tmp)[model.m_col_value] = "toto2";
			(*tmp)[model.del] = false;
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
	std::cout << "ON LOAD" << std::endl;
	Glib::RefPtr<Gtk::TreeSelection>		tmp;
	Gtk::ListStore::iterator 				it;

	// Gtk::ListStore::iterator 		tmp;
	// tmp = AppListStoreInspector->get_iter("0");

	// while (tmp)
	// {
	// 	if ((*tmp)[model.del])
	// 		tmp = AppListStoreInspector->erase(tmp);
	// 	else
	// 		tmp++;
	// }

	tmp = AppListStoreInspectorview->get_selection();
	tmp->signal_changed().connect(sigc::mem_fun(*this, &UI::button_new_func));
	it = tmp->get_selected();
	std::cout << (*it)[model.m_col_name] << std::endl;
}

void		UI::run()
{
	GtkApp->run(*window);
}

int			main(int ac, char **av)
{
	UI	*ui = new UI(ac, av);
	ui->run();
}
