#pragma once
#include <iostream>
#include <vector>

struct OverFlowException : public std::exception
{
	const char * what() const throw ()
	{
		return "OverFlow";
	}
};

namespace ChangeScale {
	///10-->16
	std::string ten2sixtenn(int val, bool captialFlag = true);

	///10->8
	std::string ten2eight(int val);

	///10->2
	std::string ten2two(int val);

	///2->10
	int two2ten(std::string str);

	///8->10
	int eight2ten(std::string str);

	///16->10
	int sixtenn2ten(std::string str);

	///16->2
	std::string sixtenn2two(std::string str);

	///8->2
	std::string eight2two(std::string str);

	///16->8
	std::string sixtenn2eight(std::string str);

	///8->16
	std::string eight2sixtenn(std::string str, bool captialFlag = true);

	///2->16
	std::string two2sixtenn(std::string str, bool captialFlag = true);

	///2->8
	std::string two2eight(std::string str);
}