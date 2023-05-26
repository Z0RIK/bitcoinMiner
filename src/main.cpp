#include <iostream>
#include <string> 
#include <vector>
#include <array>

#include "miner.h"

size_t curlWriteCallback(char* content, size_t size, size_t nmemb, std::string* response)
{
	size_t totalSize = size * nmemb;
	response->append(content, totalSize);
	return totalSize;
}

int main()
{
	BlockTemplate genesis{
		reverseHex("00000001"), // reverseHex converts hexString from big-endian to little-endian
		reverseHex("0000000000000000000000000000000000000000000000000000000000000000"),
		reverseHex("4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"), 
		reverseHex("495FAB29"), 
		reverseHex("1D00FFFF")};

	std::string expectedNonce = "1DAC2B7C"; // 497822588

	mine(497022588, 100000000, &genesis);
	
	return EXIT_SUCCESS;
}