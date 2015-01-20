#ifndef __Serveur__StringUtils__
#define __Serveur__StringUtils__

#include <sstream>
#include <string>

namespace StringUtils
{
    /** @brief convert string to any type T	**/
	template <typename T>
	T FromString( const string_t & str )
	{
		std::istringstream iss( str );
		T n;
		iss >> n;
		return n;
	}

	/** @brief convert any type T into a string	**/
	template < typename T >
	string_t ToString( const T & value )
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}
}

#endif /* defined(__Serveur__StringUtils__) */
