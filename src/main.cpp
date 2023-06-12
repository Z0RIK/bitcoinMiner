#include <iostream>
#include <string> 
#include <vector>
#include <array>

#include "miner.h"

const char* help = 
	"Usage: bitcoinMiner [OPTIONS]\n"
    "Options:\n"
    "\t--sha256 <input>     Compute the SHA256 hash of the input string\n"
    "\t--sha256hex <input>  Compute the SHA256 hash of the input hex string.\n"
    "\t--help               Print this help message.\n";

int main(int argc, char* argv[])
{
	for(size_t i = 1; i < argc; i++)
	{
		if(!strncmp(argv[i], "--sha256", 9))
		{
			if(i + 1 < argc)
			{
				std::string argvString(argv[i + 1]);

				std::cout << "input: " << argvString << std::endl;
				std::cout << "Hash: " << hashToString(SHA256(argvString)) << std::endl;
				i++;
				continue;
			}
		}
		else if(!strncmp(argv[i], "--sha256hex", 11))
		{
			if(i + 1 < argc)
			{
				std::string argvString(argv[i + 1]);

				if(argvString.size() % 2)
				{
					std::cerr << "ERROR::Invalid hex string" << std::endl;
					return EXIT_FAILURE;
				}

				for (char& it : argvString)
				{
					it = std::tolower(it);
					if(it < '0' || ('9' < it && it < 'a') || 'f' < it)
					{
						std::cerr << "ERROR::Invalid hex string" << std::endl;
						return EXIT_FAILURE;
					}
				}

				std::cout << "input hex: " << argvString << std::endl;
				std::cout << "Hash: " << hashToString(SHA256(hexToUintVector(argvString), argvString.size() / 2)) << std::endl;
				i++;
				continue;
			}
		}
			std::cout << help << std::endl;
			break;
	}

	// bitcoin miner example
	/*
	BlockTemplate genesis{
		reverseHex("00000001"), // reverseHex converts hexString from big-endian to little-endian
		reverseHex("0000000000000000000000000000000000000000000000000000000000000000"),
		reverseHex("4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"), 
		reverseHex("495FAB29"), 
		reverseHex("1D00FFFF")};

	std::string expectedNonce = "1DAC2B7C"; // 497822588

	mine(475000000, 100000000, &genesis);
	*/

	return EXIT_SUCCESS;

}