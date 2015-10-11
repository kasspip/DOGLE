#include "DOGLE.hpp"
#include "Application.hpp"
#include "Engine.hpp"
#include "Skin.hpp"

int main (void)
{
	Application app("42run");
	Scene 		scene("TestTriangle");
	GameObject 	go("Triangle");

	app.AddScene(&scene);
	scene.AddGameObject(&go);
	try 
	{
		go.AddComponent(new Skin("triangle.dae")); //components on the heap else segfault

		Engine		EG;
		EG.StartOpenGL();
		EG.RunApplication(app);
		EG.StopOpenGL();
		//throw DError() << msg("TEST");
	}
	catch (DError & e ) 
	{
		std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) 
					<< C_DEFAULT << std::endl;
	}
	return (0);
}
