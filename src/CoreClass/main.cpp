#include "DOGLE.hpp"
#include "Engine.hpp"
#include "Builder.hpp"

int main(int ac, char **av)
{
	Builder 		builder;
	Engine			EG;

	try 
	{
		if (ac == 2)
			EG.RunApplication(builder.Build(av[1]));
		else
			std::cout << "Usage: " << av[0] << " <.dogle file>";
	}
	catch (DError & e ) 
	{
		std::cerr 	<< C_YELLOW << "DOGLE Exception : " << *(boost::get_error_info<msg>(e)) 
					<< C_DEFAULT << std::endl;
	}
	return 0;
}
