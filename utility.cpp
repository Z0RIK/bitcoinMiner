#include "utility.h"

std::string hexToString(std::string input)
{
	for (auto& it : input)
		it = std::tolower(it);

	std::string result;
	result.reserve(input.size() / 2);

	for (size_t i = 0; i < input.size() / 2; i++)
	{
		char c = ((input[i * 2] <= '9') ? input[i * 2] - '0' : input[i * 2] - 'a' + 10) << 4;
		c |= (input[i * 2 + 1] <= '9') ? input[i * 2 + 1] - '0' : input[i * 2 + 1] - 'a' + 10;
		result.push_back(c);
	}

	return result;
}

std::vector<uint32_t> hexToUintVector(std::string input)
{
	for (char& it : input)
		it = std::tolower(it);

	std::vector<uint32_t> result;
	result.reserve(input.size() / 8 + 1);

	for (size_t i = 0, mod = 0, div = 0; i < input.size() / 2; i++)
	{
		uint8_t current;

		current = ((input[i * 2] <= '9') ? input[i * 2] - '0' : input[i * 2] - 'a' + 10) << 4;
		current |= (input[i * 2 + 1] <= '9') ? input[i * 2 + 1] - '0' : input[i * 2 + 1] - 'a' + 10;

		mod = i & 3;	// i % 4
		div = i >> 2;	// i / 4

		if (!mod) result.push_back(0);

		result[div] |= (current << (3 - mod) * 8);
	}

	return result;
}

void printVector(const std::vector<uint8_t>& input)
{
	for (const auto& it : input)
		std::cout << (char)it << ' ';
	std::cout << std::endl;
}

void printVector(const std::vector<uint32_t>& input)
{
#if 0
	for (const auto& it : input)
		std::cout << it << ' ';
	std::cout << std::endl;
#else

	for (const auto& it : input)
	{
		std::cout << std::hex << (int)((it >> 3 * 8) & 0xFF) << ' ';
		std::cout << std::hex << (int)((it >> 2 * 8) & 0xFF) << ' ';
		std::cout << std::hex << (int)((it >> 1 * 8) & 0xFF) << ' ';
		std::cout << std::hex << (int)((it >> 0 * 8) & 0xFF) << ' ';
		std::cout << '\n';
	}

	std::cout << std::endl;
#endif
}

void printArrayHex(const std::array<uint32_t, 8>& input)
{
	for (const uint32_t& it : input)
	{
		std::cout << std::hex << it << ' ';
	}
	std::cout << std::endl;
}