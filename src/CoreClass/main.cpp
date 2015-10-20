#include "DOGLE.hpp"
#include "Engine.hpp"

// ASSEMBLAGE //
#include "SCRIPTS.hpp"
#include "Script.hpp"
#include "Application.hpp"
#include "Skin.hpp"

int		main(void)
{
	try 
	{
		// ASSEMBLAGE //

		Application *app = new Application("42run");


			GameObject *camera1 = new GameObject("Camera1");
				camera1->AddComponent( new Camera );
				camera1->AddComponent( new ControlCamera );
				app->AddPrefab(camera1);

			GameObject *camera2 = new GameObject("Camera2");
				camera2->AddComponent( new Camera );
				camera2->AddComponent( new ControlCamera );
				app->AddPrefab(camera2);


			GameObject *MonCube = new GameObject("MonCube");
				MonCube->AddComponent( new Skin("cube.dae") );
				MonCube->AddComponent( new MyCube );
				app->AddPrefab(MonCube);


			Scene *scene1 = new Scene("Level1");
				scene1->InstanciatePrefab( app->FindPrefab("MonCube"), Transform(glm::vec3(0, 0, 0)));
				scene1->InstanciatePrefab( app->FindPrefab("Camera1") );
				app->AddScene(scene1);

			Scene *scene2 = new Scene("Level2");
				scene2->InstanciatePrefab( app->FindPrefab("MonCube"), Transform(glm::vec3(-1, 0, 0)));
				scene2->InstanciatePrefab( app->FindPrefab("MonCube"), Transform(glm::vec3(1, 0, 0)));
				scene2->InstanciatePrefab( app->FindPrefab("Camera2") );
				app->AddScene(scene2);

		// INTERPRETATION //

		Engine		EG;
		EG.RunApplication(app);

	}
	catch (DError & e ) 
	{
		std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) 
					<< C_DEFAULT << std::endl;
	}
	return (0);
}
