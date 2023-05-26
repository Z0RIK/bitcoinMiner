#pragma once

#ifndef MINER_H
#define MINER_H

#include <string>
#include <vector>
#include <array>
#include <chrono>

#include "utility.h"
#include "sha256.h"

uint32_t mine(uint32_t nonceStart, uint32_t maxNonceOffset,	BlockTemplate* header);

std::array<uint32_t, 8> hashBlock(const BlockTemplate& header, const uint32_t& nonce);

#endif // !MINER_H