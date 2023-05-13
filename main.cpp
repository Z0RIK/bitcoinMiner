#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <vector>
#include <array>
#include <cmath>

#include "sha256.h"
#include "utility.h"

inline bool zeroesCount(const std::array<uint32_t, 8>& hash, const uint32_t& difficulty)
{
	for (size_t i = 0; i < difficulty / 8; i++)
		if (hash[7 - i] != 0) return false;
	for (size_t i = 0; i < difficulty % 8; i++)
		if (hash[7 - difficulty / 8] << i);

}

uint32_t mine(	uint32_t nonce,
				uint32_t difficulty,
				const std::string& version,
				const std::string& prevHash,
				const std::string& merkleRoot,
				const std::string& time,
				const std::string& nBits
)
{
	std::vector<uint32_t> blockHeader = hexToUintVector(version + prevHash + merkleRoot + time + nBits);
	blockHeader.push_back(nonce);

	std::array<uint32_t, 32> padedBlockheader = {};
	std::array<uint32_t, 16> padedHash1 = {};
	std::array<uint32_t, 8> hash2 = {};
	
	// pading blockheader
	memcpy(&padedBlockheader[0], &blockHeader[0], sizeof(uint32_t) * 20);
	padedBlockheader[20] = ((uint32_t)0x80 << 3 * 8);
	padedBlockheader[31] = 20 * 4 * 8;

	// preparing first hash 
	memcpy(&padedHash1[0], &SHA256(padedBlockheader)[0], sizeof(uint32_t) * 8);
	padedHash1[8] = ((uint32_t)0x80 << 3 * 8);
	padedHash1[15] = 4 * 8 * 8;

	for (nonce; nonce < 500000000; nonce++)
	{
		padedBlockheader[19] = nonce;												// iterating nonce in the blockheader
		memcpy(&padedHash1[0], &SHA256(padedBlockheader)[0], sizeof(uint32_t) * 8); // hashing blockheader once
		hash2 = SHA256(padedHash1);													// hashing blockheader second time

		//if (zeroesCount(hash2, difficulty)) return nonce;

		if (hash2[7] == 0) return nonce;
	}

	//printArrayHex(SHA256(padedBlockheader));
	//printArrayHex(SHA256(padedHash1));

	return 0;
}

struct block
{
	std::string version = "20018000";
	std::string prevhash = "0000000000000000000000000000000000000000000000000000000000000000";
	std::string merkle_root = "7c30d512dfc8c8d20e532307b286536a8789d6fd51f93766a6ac222d79bf8a96";
	std::string time = "29AB5F49";
	std::string nbits = "FFFF001D";
	std::string nonce = "1DAC2B7C"; // 497822588
};

int main()
{
	std::string version = "01000000";
	std::string prevhash = "0000000000000000000000000000000000000000000000000000000000000000";
	std::string merkle_root = "3BA3EDFD7A7B12B27AC72C3E67768F617FC81BC3888A51323A9FB8AA4B1E5E4A";
	std::string time = "29AB5F49";
	std::string nbits = "FFFF001D";
	std::string nonce = "1DAC2B7C"; // 497822588
	std::string blockHeaderHex = version + prevhash + merkle_root + time + nbits + nonce;
	std::vector<uint32_t> blockHeaderVector = hexToUintVector(blockHeaderHex);
	std::cout << blockHeaderHex << "|end" << "\n";
	std::array<uint32_t, 8> hash1 = SHA256(blockHeaderVector, 80);
	std::array<uint32_t, 8> hash2 = SHA256(std::vector<uint32_t>(hash1.begin(), hash1.end()), 8*4);
	printArrayHex(hash1);
	printArrayHex(hash2);

	std::cout << std::hex << mine(400000000, 8, version, prevhash, merkle_root, time, nbits);

	return EXIT_SUCCESS;
}