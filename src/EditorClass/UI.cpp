#include <iostream>
#include "UI.hpp"

UI::UI(int ac, char **av) {
	app = Gtk::Application::create(ac, av, "jean.michel");
	builder = Gtk::Builder::create_from_file("unity_gtk.glade");
	builder->get_widget("window1", window);
	Gtk::Button	*new_button;
	builder->get_widget("button1", new_button);
	new_button->signal_clicked().connect(sigc::mem_fun(*this, &UI::new_button_func));
}

void		UI::new_button_func() {
	std::cout << "New_button" << std::endl;
}

void		UI::run() {
	app->run(*window);
}

int			main(int ac, char **av) {
	UI	*ui = new UI(ac, av);
	ui->run();
}