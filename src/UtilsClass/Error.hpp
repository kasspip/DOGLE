#ifndef ERROR_HPP
# define ERROR_HPP

# include <boost/exception/all.hpp>

	typedef boost::error_info<struct tag_msg, std::string> msg; 
	struct DError: virtual boost::exception, virtual std::exception 
	{	}; 

# endif