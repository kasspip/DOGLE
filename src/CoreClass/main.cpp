#include "DOGLE.hpp"
#include "Application.hpp"

int main (void)
{
	Application app;
	Scene scene;
	Scene scene1("FUCK WILL");
	GameObject go;

	scene.AddGameObject(&go);
	scene1.AddGameObject(&go);
	app.AddScene(&scene);
	app.AddScene(&scene1);
	app.Save();
	return (0);
}
