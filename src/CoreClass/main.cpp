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
				app->AddPrefab(camera);

			GameObject *object3D = new GameObject("Object3D");
				object3D->AddComponent( new Skin("cube.dae") );
				object3D->AddComponent( new MaClass("MaClass") );
				app->AddPrefab(object3D);

			Scene *scene1 = new Scene("Level1");
				scene1->InstanciatePrefab( app->FindPrefab("Object3D") );
				scene1->InstanciatePrefab( app->FindPrefab("Camera") );
				app->AddScene(scene1);

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
