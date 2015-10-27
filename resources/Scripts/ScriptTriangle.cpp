# include "DOGLE.hpp"
# include "Script.hpp"

	class ScriptTriangle : public Script
	{
		public:

			ScriptTriangle() : Script("ScriptTriangle") {}
			Script* Clone() { return new ScriptTriangle(*this); }



			void	Update()
			{

			}



	};
