/*
 * utils.cpp
 *
 *  Created on: Jun 17, 2018
 *      Author: nikolaj
 */

#include "../include/utils.h"
#include <iomanip>
#include <sstream>

// split the data up
void basic_utils::split(const std::string& s, char delim, std::vector<std::string>& v)
{
	if(s.size() == 0)
	{
		return;
	}
	size_t i = 0;
	auto pos = s.find(delim);
	while(pos != std::string::npos)
	{
		v.push_back(s.substr(i, pos - i));
		i = ++pos;
		pos = s.find(delim, pos);

		if(pos == std::string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}
// split the data up
std::vector<std::string> basic_utils::split(const std::string& s, const std::string& delim)
{
	std::vector<std::string> vec;
	if(s.size() == 0)
	{
		return vec;
	}
	size_t i = 0;
	auto pos = s.find(delim);
	while(pos != std::string::npos)
	{
		vec.push_back(s.substr(i, pos - i));
		i = ++pos;
		pos = s.find(delim, pos);

		if(pos == std::string::npos)
			vec.push_back(s.substr(i, s.length()));
	}
	return vec;
}
std::string intToString(int number)
{
	std::ostringstream oss;

	// Works just like cout
	oss << number;

	// Return the underlying string

	return oss.str();
}

std::string timeToString(time_t number)
{
	std::ostringstream oss;

	// Works just like cout
	oss << number;

	// Return the underlying string

	return oss.str();
}

std::string uint8ToString(uint8_t number)
{
	std::ostringstream oss;

	// Works just like cout
	oss << number;

	// Return the underlying string

	return oss.str();
}

std::string floatToString(float number)
{
	std::ostringstream oss;

	// Works just like cout
	oss << std::fixed << std::setprecision(3) << number;

	// Return the underlying string
	return oss.str();
}

std::string floatToString(float number, int precision)
{
	std::ostringstream oss;

	// Works just like cout
	oss << std::fixed << std::setprecision(precision) << number;

	// Return the underlying string
	return oss.str();
}

std::string uintToString(uint8_t number)
{
	std::ostringstream oss;

	// Works just like cout
	oss << number;

	// Return the underlying string
	return oss.str();
}

// assumes little endian
/*
 * prints out a register of xx size. usage:
 *  uint16_t controlRegister1;
 *  printBits(sizeof(controlRegister1),&controlRegister1);
 */
void printBits(size_t const size, void const* const ptr)
{
	unsigned char* b = (unsigned char*)ptr;
	unsigned char byte;
	size_t i, j;

	for(i = size - 1; i != 0; i--)
	{
		for(j = 7; j != 0; j--)
		{
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
	puts("");
}

bool basic_utils::is_even(int16_t expr)
{
	// evaluate if this even or odd
	return (expr & 0x01) ? false : true;
}

/*@brief
 * change the least significan byte of a uint16_t dataset
 * @return
 * return the new dataset
 */

uint16_t basic_utils::leastSignificantByteExchange(uint16_t data, uint8_t exchange)
{
	return static_cast<uint16_t>((data & 0xff00) + exchange);
}

uint8_t basic_utils::getLeastSignificantByte(uint16_t data)
{
	return static_cast<uint8_t>(data & (uint16_t)0x00ff);
}

uint32_t basic_utils::shift8BitTo32(const uint8_t& b1, const uint8_t& b2, const uint8_t& b3,
									const uint8_t& b4)
{
	return (b1 << 24 | b2 << 16 | b3 << 8 | b4);
}

general_err_t basic_utils::shift32BitTo8(const uint32_t& b32, uint8_t& b1, uint8_t& b2, uint8_t& b3,
										 uint8_t& b4)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> enclosing_method >> ");
#endif
	// Executable code:

	b1 = static_cast<uint8_t>(b32 >> 24);
	b2 = static_cast<uint8_t>(b32 >> 16);
	b3 = static_cast<uint8_t>(b32 >> 8);
	b4 = static_cast<uint8_t>(b32);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< enclosing_method << ");
#endif

	return GE_OK;
}
static bool random_first = true;
// psudo random : range [min,max]
int basic_utils::random(int min, int max)
{
	if(random_first)
	{
		srand(time(NULL));
		random_first = false;
	}
	return min + rand() % ((max + 1) - min);
}
