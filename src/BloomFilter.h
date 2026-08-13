#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

class BloomFilter {
private:
    // Bit array used by the Bloom Filter.
    std::vector<bool> bits;

    // Number of hash functions used for each item.
    std::size_t numHashFunctions;

    // Two base hash functions.
    std::uint64_t hash1(const std::string& item) const;
    std::uint64_t hash2(const std::string& item) const;

    // Generates a bit-array position using double hashing.
    std::size_t getIndex(
        const std::string& item,
        std::size_t hashNumber
    ) const;

public:
    // Creates a Bloom Filter with the given number of bits
    // and hash functions.
    BloomFilter(
        std::size_t size,
        std::size_t hashFunctions
    );

    // Adds an item to the Bloom Filter.
    void insert(const std::string& item);

    // Returns false if the item is definitely not present.
    // Returns true if the item is possibly present.
    bool possiblyContains(
        const std::string& item
    ) const;

    // Returns the size of the bit array.
    std::size_t getSize() const;

    // Returns the number of hash functions.
    std::size_t getHashFunctionCount() const;

    // Returns the number of bits currently set to 1.
    std::size_t getSetBitCount() const;

    // Displays the bit array.
    void printBits() const;
};

#endif
