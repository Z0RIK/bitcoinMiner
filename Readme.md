# Bitcoin miner

This is a pet project focused on implementing the SHA-256 hash function

## Features

1. SHA256 function that can be used for hashing strings, hex-strings, and vectors.
2. Mine function that searches for a valid nonce within a specified range.
3. bitsToTarget function that converts a short target representation to the full target.

## Command line arguments for hashing strings
Usage: bitcoinMiner [OPTIONS]  
  Options:  
  --sha256 <input>     Compute the SHA256 hash of the input string.  
  --sha256hex <input>  Compute the SHA256 hash of the input hex string.  
  --help               Print help message.  
