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
			
			GameObject *camera = new GameObject("Camera");
				camera->AddComponent( new Camera );
				camera->AddComponent( new MaClass );
				app->AddPrefab(camera);

			GameObject *object3D = new GameObject("Object3D");
				object3D->AddComponent( new Skin("cube.dae") );
				object3D->AddComponent( new MyCube );
				app->AddPrefab(object3D);

			Scene *scene1 = new Scene("Level1");
			//Transform tr;
			//Transform tr;
			//tr.position.x = 0.5;
				scene1->InstanciatePrefab( app->FindPrefab("Object3D"), Transform(glm::vec3(0, 0.0, -3.0)));
				GameObject *tmp = scene1->InstanciatePrefab( app->FindPrefab("Camera") );
				app->AddScene(scene1);
			Camera::SetMainCamera(tmp);

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
