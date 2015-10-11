#include "DOGLE.hpp"
#include "Application.hpp"
#include "Engine.hpp"

int main (void)
{
	Application app;
	Scene 		scene;
	Scene 		scene1("FUCK WILL");
	GameObject 	go;
	

	scene.AddGameObject(&go);
	scene1.AddGameObject(&go);
	app.AddScene(&scene);
	app.AddScene(&scene1);
	// app.Save();
	try 
	{
		Engine		EG(app);
		throw DError() << msg("TEST.\n");
	}
	catch (DError & e ) 
	{
		std::cerr << "DOGLE Exception : " << *(boost::get_error_info<msg>(e));
	}
	return (0);
}
