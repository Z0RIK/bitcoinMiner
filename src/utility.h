#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <array>
#include <iostream>

struct BlockTemplate
{
	std::string version;
	std::string prevBlockHash;
	std::string merkleRoot;
	std::string timeStamp;
	std::string nBits;
};

std::string hexToString(std::string input);

inline uint32_t reverse32(const uint32_t& input);

std::array<uint32_t, 8> reverse256(const std::array<uint32_t, 8>& input);

std::array<uint32_t, 8> bitsToTarget(std::string bitsHex);

std::string reverseHex(const std::string& input);

std::vector<uint32_t> hexToUintVector(std::string input);

bool lessOrEqual(const std::array<uint32_t, 8>& hash, const std::array<uint32_t, 8>& target);

#endif // !UTIL_H