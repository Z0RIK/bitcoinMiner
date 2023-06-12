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
	std::vector<uint32_t> result;
	result.reserve(input.size() / 8 + 1);

	for (char& it : input)
		it = std::tolower(it);

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

inline uint32_t reverse32(const uint32_t& input)
{
	uint32_t result{};
	for (size_t i = 0; i < 4; i++)
		result |= ((input >> i * 8) & 0xFF) << (3 - i) * 8;
	return result;
}

std::array<uint32_t, 8> reverse256(const std::array<uint32_t, 8>& input)
{
	std::array<uint32_t, 8> result = {};

	for (size_t i = 0; i < 8; i++)
		result[i] = reverse32(input[7 - i]);

	return result;
}

std::string reverseHex(const std::string& input)
{
	std::string result(input.size(), ' ');

	for (size_t i = 0, n = input.size(); i < input.size(); i += 2)
	{
		char a = input[n - 2 - i];
		char b = input[n - 1 - i];
		result[i] = a;
		result[i + 1] = b;
	}

	return result;
}

std::array<uint32_t, 8> bitsToTarget(std::string bitsHex)
{
	if (bitsHex.size() != 8) 
		std::cerr << "ERROR::bitsToTarget::wrong input: " << bitsHex << std::endl;

	std::array<uint32_t, 8> result;
	std::string hexTarget(64, '0');
	uint8_t length{};

	for (auto& it : bitsHex) it = std::tolower(it);

	length = ((bitsHex[6] <= '9') ? bitsHex[6] - '0' : bitsHex[6] - 'a' + 10) << 4;
	length |= (bitsHex[7] <= '9') ? bitsHex[7] - '0' : bitsHex[7] - 'a' + 10;

	memcpy(&hexTarget[length * 2 - 6], &bitsHex[0], sizeof(char) * 6);
	memcpy(&result[0], &hexToUintVector(hexTarget)[0], sizeof(uint32_t) * 8);

	return result;
}

bool lessOrEqual(const std::array<uint32_t, 8>& hash, const std::array<uint32_t, 8>& target)
{
	for (int i = 7; i >= 0; i--)
	{
		if (reverse32(hash[i]) > reverse32(target[i])) return false;
		if (reverse32(hash[i]) < reverse32(target[i])) return true;
	}

	return true;
}

std::string hashToString(std::array<uint32_t, 8> inputHash)
{
	std::string result;

	auto decToHex = [](const uint8_t& inputDec) -> char {
		if (inputDec < 10) return '0' + inputDec;
		else return 'A' + inputDec % 10;
	};

	for (auto& it : inputHash)
	{
		for (size_t i = 0; i < 4; i++)
		{
			uint8_t current = it >> (3 - i) * 8 & 0xFF;
			result.push_back(decToHex(current >> 4 & 0xF));
			result.push_back(decToHex(current & 0xF));
		}
	}

	return result;
}