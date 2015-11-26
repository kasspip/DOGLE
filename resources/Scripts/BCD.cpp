# include "DOGLE.hpp"
# include "Script.hpp"

class BCD: public Script
{
	public:

	BCD() : Script("BCD") {}
	Script* Clone() { return new BCD(*this); }

};
