#include "miner.h"

uint32_t mine(uint32_t nonceStart,
	uint32_t difficulty,			// TODO add difficulty
	const std::string& version,
	const std::string& prevHash,
	const std::string& merkleRoot,
	const std::string& time,
	const std::string& nBits
)
{
	std::vector<uint32_t> blockHeader = hexToUintVector(version + prevHash + merkleRoot + time + nBits);
	blockHeader.push_back(nonceStart);

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

	for (size_t nonce = nonceStart; nonce < nonceStart + 100000000; nonce++)
	{
		padedBlockheader[19] = nonce;																// iterating nonce in the blockheader
		memcpy(&padedHash1[0], &SHA256(padedBlockheader)[0], sizeof(uint32_t) * 8);	// hashing blockheader once
		hash2 = SHA256(padedHash1);																	// hashing blockheader second time

		if (hash2[7] == 0) return nonce;
	}

	return 0;
}