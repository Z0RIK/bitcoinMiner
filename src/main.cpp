#include <iostream>
#include <string> 
#include <vector>
#include <array>

#include "miner.h"


struct BlockTemplate
{
	std::string version;
	std::string prevhash;
	std::string merkle_root;
	std::string time;
	std::string nbits;
};

int main()
{
	BlockTemplate genesisBlock{
		"01000000", 
		"0000000000000000000000000000000000000000000000000000000000000000",
		"3BA3EDFD7A7B12B27AC72C3E67768F617FC81BC3888A51323A9FB8AA4B1E5E4A", 
		"29AB5F49", 
		"FFFF001D"};

	std::string expectedNonce = "1DAC2B7C"; // 497822588

	std::cout << std::hex << mine(470000000, 8, genesisBlock.version, genesisBlock.prevhash, genesisBlock.merkle_root, genesisBlock.time, genesisBlock.nbits);

	return EXIT_SUCCESS;
}