#pragma once

#ifndef MINER_H
#define MINER_H

#include <string>
#include <vector>
#include <array>

#include "utility.h"
#include "sha256.h"

uint32_t mine(uint32_t nonce,
	uint32_t difficulty,
	const std::string& version,
	const std::string& prevHash,
	const std::string& merkleRoot,
	const std::string& time,
	const std::string& nBits
);

#endif // !MINER_H