#include "miner.h"

uint32_t mine(	
	uint32_t nonceStart, uint32_t maxNonceOffset, BlockTemplate* header)
{
	std::vector<uint32_t> blockHeader = hexToUintVector(header->version + header->prevBlockHash + header->merkleRoot + header->timeStamp + header->nBits);
	blockHeader.push_back(nonceStart);

	std::array<uint32_t, 32> padedBlockheader = {};
	std::array<uint32_t, 16> padedHash1 = {};
	std::array<uint32_t, 8> hash2 = {};
	std::array<uint32_t, 8> target = bitsToTarget(header->nBits);

	// pading blockheader
	memcpy(&padedBlockheader[0], &blockHeader[0], sizeof(uint32_t) * 20);
	padedBlockheader[20] = ((uint32_t)0x80 << 3 * 8);
	padedBlockheader[31] = 20 * 4 * 8;

	// preparing first hash 
	memcpy(&padedHash1[0], &SHA256(padedBlockheader)[0], sizeof(uint32_t) * 8);
	padedHash1[8] = ((uint32_t)0x80 << 3 * 8);
	padedHash1[15] = 4 * 8 * 8;
	
	auto start = std::chrono::high_resolution_clock::now();

	for (uint32_t nonce = nonceStart; nonce < nonceStart + maxNonceOffset; nonce++)
	{
		padedBlockheader[19] = nonce;	// iterating nonce in the blockheader
		memcpy(&padedHash1[0], &SHA256(padedBlockheader)[0], sizeof(uint32_t) * 8);	// hashing blockheader once
		hash2 = SHA256(padedHash1);	// hashing blockheader second time

		if (hash2[7] == 0 && lessOrEqual(hash2, target))	// min target && actual target
		{
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
			
			std::cout << "Nonce: " << std::hex << nonce << std::endl;
			std::cout << "Average hashrate: " << std::dec << (nonce - nonceStart) / (duration.count() + 1) << "Mh/s" << std::endl;
			std::cout << "Resulting hash: " << hashToString(hash2) << std::endl;

			return nonce;
		}
	}

	return 0;
}

std::array<uint32_t, 8> hashBlock(const BlockTemplate& header, const uint32_t& nonce)
{
	std::vector<uint32_t> blockHeader = hexToUintVector(header.version + header.prevBlockHash + header.merkleRoot + header.timeStamp + header.nBits);
	blockHeader.push_back(nonce);

	auto hash1 = SHA256(blockHeader, 20 * 4);
	auto hash2 = SHA256(std::vector<uint32_t>(hash1.begin(), hash1.end()), 4 * 8);

	return hash2;
}
