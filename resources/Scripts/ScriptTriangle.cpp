# include "DOGLE.hpp"
# include "Script.hpp"

	class ScriptTriangle : public Script
	{
		public:
			
			ScriptTriangle() : Script("ScriptTriangle") {}
			Script* Clone() { return new ScriptTriangle(*this); }

		// GameObject* obj = nullptr;

		// void			Update()
		// {
		// 	PopObj();
		// 	RemoveObj();
		// }

		// void			PopObj()
		// {
		// 	if (!obj && Inputs::singleton->KeyDown(GLFW_KEY_E))
		// 		obj = Application::singleton->GetCurrentScene()->InstanciatePrefab(Application::singleton->FindPrefab("MonTriangle"), *transform);
		// }

		// void			RemoveObj()
		// {
		// 	if (obj && Inputs::singleton->KeyDown(GLFW_KEY_R))
		// 	{
		// 		Destroy(obj);
		// 		obj = nullptr;
		// 	}
		// }
	};
