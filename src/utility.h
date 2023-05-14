#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <array>
#include <iostream>

std::string hexToString(std::string input);

std::vector<uint32_t> hexToUintVector(std::string input);

void printVector(const std::vector<uint8_t>& input);
void printVector(const std::vector<uint32_t>& input);

void printArrayHex(const std::array<uint32_t, 8>& input);

#endif // !UTIL_H