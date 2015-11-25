# include "DOGLE.hpp"
# include "Script.hpp"

class again: public Script
{
	public:

	again() : Script("again") {}
	Script* Clone() { return new again(*this); }

};
