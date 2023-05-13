#include "sha256.h"

// init K values
static std::array<uint32_t, 64> K = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// H values
static std::array<uint32_t, 8> H;

// words array
static std::array<uint32_t, 64> W;

// buffers
static uint32_t a, b, c, d, e, f, g, h, t1, t2;

std::vector<uint32_t> stringToUint32Vector(const std::string& inputString)
{
	std::vector<uint32_t> result;
	result.reserve((((inputString.size() / 4) + 2) / 16 + 1) * 16);

	for (uint64_t i = 0, div = 0, mod = 0, current = 0; i < inputString.size(); i++)
	{
		mod = i & 3;
		div = i >> 2;
		current = inputString[i];
		if (!mod) result.push_back(0);
		result[div] |= (current << (3 - mod) * 8);
	}

	return result;
}

void padUint32Array(std::vector<uint32_t>& inputArray, uint64_t sizeBytes)
{
	uint64_t sizeBits = sizeBytes * 8;

	if (sizeBits % 512 != 448)
	{
		sizeBytes;

		uint64_t mod = sizeBytes & 3;
		uint64_t div = sizeBytes >> 2;

		if (!mod) inputArray.push_back(0);
		inputArray[div] |= ((uint32_t)0x80 << (3 - mod) * 8);

		while (inputArray.size() % 16 != 14)
			inputArray.push_back(0);
	}

	inputArray.push_back((sizeBits >> 4 * 8) & 0xFFFFFFFF);
	inputArray.push_back(sizeBits & 0xFFFFFFFF);
}

inline uint32_t rotateRight(const uint32_t& target, const uint8_t& amount)
{
	return (target >> amount) | (target << (32 - amount));
}

inline uint32_t sigma0(const uint32_t& input)
{
	return rotateRight(input, 7) ^ rotateRight(input, 18) ^ (input >> 3);
}

inline uint32_t sigma1(const uint32_t& input)
{
	return rotateRight(input, 17) ^ rotateRight(input, 19) ^ (input >> 10);
}

inline uint32_t ep0(const uint32_t& input)
{
	return rotateRight(input, 2) ^ rotateRight(input, 13) ^ rotateRight(input, 22);
}

inline uint32_t ep1(const uint32_t& input)
{
	return rotateRight(input, 6) ^ rotateRight(input, 11) ^ rotateRight(input, 25);
}

inline uint32_t choose(const uint32_t& decisionMask, uint32_t a, uint32_t b)
{
	return (a & decisionMask) | (b & ~decisionMask);
}

inline uint32_t majority(const uint32_t& a, const uint32_t& b, const uint32_t& c)
{
	return ((a & b) ^ (a & c) ^ (b & c));
}

// general use
std::array<uint32_t, 8> SHA256(const std::string& inputString)
{
	// char string to uint32_t vector
	std::vector<uint32_t> inputUint32 = stringToUint32Vector(inputString);

	// pad input
	padUint32Array(inputUint32, inputString.size());

	// init H values
	H = {
		0x6a09e667,
		0xbb67ae85,
		0x3c6ef372,
		0xa54ff53a,
		0x510e527f,
		0x9b05688c,
		0x1f83d9ab,
		0x5be0cd19
	};

	// loop over 512 bit blocks
	for (int blockIndex = 0; blockIndex != inputString.size() / 64 + 1; blockIndex++)
	{
		// init buffers
		a = H[0];
		b = H[1];
		c = H[2];
		d = H[3];
		e = H[4];
		f = H[5];
		g = H[6];
		h = H[7];

		// init words
		for (int i = 0; i < 16; i++)
			W[i] = inputUint32[i + blockIndex * 16];

		for (int i = 16; i < 64; i++)
		{
			W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i - 16];
		}

		// compute hash
		for (int t = 0; t < 64; t++)
		{
			t1 = h + ep1(e) + choose(e, f, g) + K[t] + W[t];
			t2 = ep0(a) + majority(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;
		}

		// update H values
		H[0] = a + H[0];
		H[1] = b + H[1];
		H[2] = c + H[2];
		H[3] = d + H[3];
		H[4] = e + H[4];
		H[5] = f + H[5];
		H[6] = g + H[6];
		H[7] = h + H[7];
	}

	return H;
}

std::array<uint32_t, 8> SHA256(const std::vector<uint32_t>& inputVector, const size_t& sizeBytes)
{
	// pad input
	std::vector<uint32_t> padedInput(inputVector);
	padUint32Array(padedInput, sizeBytes);

	// init H values
	H = {
		0x6a09e667,
		0xbb67ae85,
		0x3c6ef372,
		0xa54ff53a,
		0x510e527f,
		0x9b05688c,
		0x1f83d9ab,
		0x5be0cd19
	};

	// loop over 512 bit blocks
	for (int blockIndex = 0; blockIndex != sizeBytes / 64 + 1; blockIndex++)
	{
		// init buffers
		a = H[0];
		b = H[1];
		c = H[2];
		d = H[3];
		e = H[4];
		f = H[5];
		g = H[6];
		h = H[7];

		// init words
		for (int i = 0; i < 16; i++)
			W[i] = padedInput[i + blockIndex * 16];

		for (int i = 16; i < 64; i++)
		{
			W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i - 16];
		}

		// compute hash
		for (int t = 0; t < 64; t++)
		{
			t1 = h + ep1(e) + choose(e, f, g) + K[t] + W[t];
			t2 = ep0(a) + majority(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;
		}

		// update H values
		H[0] = a + H[0];
		H[1] = b + H[1];
		H[2] = c + H[2];
		H[3] = d + H[3];
		H[4] = e + H[4];
		H[5] = f + H[5];
		H[6] = g + H[6];
		H[7] = h + H[7];
	}

	return H;
}

// optimized for mining
std::array<uint32_t, 8> SHA256(const std::array<uint32_t, 32>& padedBlockHeader)
{

	// init H values
	H = {
		0x6a09e667,
		0xbb67ae85,
		0x3c6ef372,
		0xa54ff53a,
		0x510e527f,
		0x9b05688c,
		0x1f83d9ab,
		0x5be0cd19
	};

	// loop over 512 bit blocks
	for (int blockIndex = 0; blockIndex < 2; blockIndex++)
	{
		// init buffers
		a = H[0];
		b = H[1];
		c = H[2];
		d = H[3];
		e = H[4];
		f = H[5];
		g = H[6];
		h = H[7];

		// init words
		for (int i = 0; i < 16; i++)
			W[i] = padedBlockHeader[i + blockIndex * 16];

		for (int i = 16; i < 64; i++)
		{
			W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i - 16];
		}

		// compute hash
		for (int t = 0; t < 64; t++)
		{
			t1 = h + ep1(e) + choose(e, f, g) + K[t] + W[t];
			t2 = ep0(a) + majority(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;
		}

		// update H values
		H[0] = a + H[0];
		H[1] = b + H[1];
		H[2] = c + H[2];
		H[3] = d + H[3];
		H[4] = e + H[4];
		H[5] = f + H[5];
		H[6] = g + H[6];
		H[7] = h + H[7];
	}

	return H;
}

std::array<uint32_t, 8> SHA256(const std::array<uint32_t, 16>& padedHash)
{

	// init H values
	H = {
		0x6a09e667,
		0xbb67ae85,
		0x3c6ef372,
		0xa54ff53a,
		0x510e527f,
		0x9b05688c,
		0x1f83d9ab,
		0x5be0cd19
	};

	// init buffers
	a = H[0];
	b = H[1];
	c = H[2];
	d = H[3];
	e = H[4];
	f = H[5];
	g = H[6];
	h = H[7];

	// init words
	for (int i = 0; i < 16; i++)
		W[i] = padedHash[i];

	for (int i = 16; i < 64; i++)
	{
		W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i - 16];
	}

	// compute hash
	for (int t = 0; t < 64; t++)
	{
		t1 = h + ep1(e) + choose(e, f, g) + K[t] + W[t];
		t2 = ep0(a) + majority(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	// update H values
	H[0] = a + H[0];
	H[1] = b + H[1];
	H[2] = c + H[2];
	H[3] = d + H[3];
	H[4] = e + H[4];
	H[5] = f + H[5];
	H[6] = g + H[6];
	H[7] = h + H[7];

	return H;
}