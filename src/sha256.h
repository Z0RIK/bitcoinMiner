#pragma once

#ifndef SHA256_H
#define SHA256_H

#include <string> 
#include <vector>
#include <array>

// general use
std::array<uint32_t, 8> SHA256(const std::string& inputString);
std::array<uint32_t, 8> SHA256(const std::vector<uint32_t>& inputVector, const size_t& sizeBytes);

// optimized for mining
std::array<uint32_t, 8> SHA256(const std::array<uint32_t, 32>& padedBlockHeader);
std::array<uint32_t, 8> SHA256(const std::array<uint32_t, 16>& padedHash);

#endif // !SHA256_H