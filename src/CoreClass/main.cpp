#include "DOGLE.hpp"
#include "Application.hpp"
#include "Engine.hpp"
#include "Skin.hpp"

int main (void)
{
	try 
	{
		Application *app = new Application( "42run" );
			GameObject *object3D = new GameObject( "Object3D" ); 
				app->AddPrefab(object3D);
				object3D->AddComponent( new Skin("triangle.dae") );
			
			GameObject *camera = new GameObject( "Camera" );
				app->AddPrefab(camera);
				camera->AddComponent( new Camera );

			Scene *scene1 = new Scene( "Level1" );
				app->AddScene(scene1);
				scene1->InstanciatePrefab( app->FindPrefab("Object3D") );
				scene1->InstanciatePrefab( app->FindPrefab("Camera") );

		Engine		EG;
		EG.StartOpenGL();
		EG.RunApplication(*app);
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
