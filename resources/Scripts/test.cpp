# include "DOGLE.hpp"
# include "Script.hpp"

class test : public Script
{
	public:

	test() : Script("test") {}
	Script* Clone() { return new test(*this); }

};
