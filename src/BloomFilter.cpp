#include "BloomFilter.h"

#include <functional>
#include <iostream>
#include <stdexcept>

BloomFilter::BloomFilter(
    std::size_t size,
    std::size_t hashFunctions
)
    : bits(size, false),
      numHashFunctions(hashFunctions)
{
    if (size == 0) {
        throw std::invalid_argument(
            "Bloom Filter size must be greater than 0."
        );
    }

    if (hashFunctions == 0) {
        throw std::invalid_argument(
            "Number of hash functions must be greater than 0."
        );
}


// ============================================================
// HASH FUNCTION 1
// ============================================================

std::uint64_t BloomFilter::hash1(
    const std::string& item
) const
{
    return static_cast<std::uint64_t>(
        std::hash<std::string>{}(item)
    );
}


// ============================================================
// HASH FUNCTION 2
// ============================================================

std::uint64_t BloomFilter::hash2(
    const std::string& item
) const
{
    // FNV-1a style hash.
    std::uint64_t hashValue =
        14695981039346656037ULL;

    for (unsigned char c : item) {
        hashValue ^= static_cast<std::uint64_t>(c);
        hashValue *= 1099511628211ULL;
    }

    return hashValue;
}


// ============================================================
// GET BIT ARRAY INDEX
// ============================================================

std::size_t BloomFilter::getIndex(
    const std::string& item,
    std::size_t hashNumber
) const
{
    std::uint64_t h1 = hash1(item);
    std::uint64_t h2 = hash2(item);

    /*
        Double hashing:

            h1 + i * h2

        This allows us to generate several hash positions
        from two base hash functions.
    */

    std::uint64_t combined =
        h1 + hashNumber * h2;

    return static_cast<std::size_t>(
        combined % bits.size()
    );
}


// ============================================================
// INSERT
// ============================================================

void BloomFilter::insert(
    const std::string& item
)
{
    /*
        Each hash function produces a position
        in the bit array.

        Those positions are set to 1.
    */

    for (
        std::size_t i = 0;
        i < numHashFunctions;
        ++i
    ) {
        std::size_t index =
            getIndex(item, i);

        bits[index] = true;
    }
}


// ============================================================
// MEMBERSHIP TEST
// ============================================================

bool BloomFilter::possiblyContains(
    const std::string& item
) const
{
    /*
        If even one required bit is 0,
        the item definitely was not inserted.

        If all required bits are 1,
        the item may have been inserted.
    */

    for (
        std::size_t i = 0;
        i < numHashFunctions;
        ++i
    ) {
        std::size_t index =
            getIndex(item, i);

        if (!bits[index]) {
            return false;
        }
    }

    return true;
}


// ============================================================
// GET FILTER SIZE
// ============================================================

std::size_t BloomFilter::getSize() const
{
    return bits.size();
}


// ============================================================
// GET NUMBER OF HASH FUNCTIONS
// ============================================================

std::size_t BloomFilter::getHashFunctionCount() const
{
    return numHashFunctions;
}


// ============================================================
// COUNT SET BITS
// ============================================================

std::size_t BloomFilter::getSetBitCount() const
{
    std::size_t count = 0;

    for (bool bit : bits) {
        if (bit) {
            ++count;
        }
    }

    return count;
}


// ============================================================
// DISPLAY BIT ARRAY
// ============================================================

void BloomFilter::printBits() const
{
    std::cout << "\nBit Array:\n";

    for (
        std::size_t i = 0;
        i < bits.size();
        ++i
    ) {
        std::cout << (bits[i] ? '1' : '0');

        // Add a space after every 8 bits.
        if ((i + 1) % 8 == 0) {
            std::cout << ' ';
        }
    }

    std::cout << "\n";
}
