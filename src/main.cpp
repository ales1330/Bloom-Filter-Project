#include "BloomFilter.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


// ============================================================
// DISPLAY MEMBERSHIP RESULT
// ============================================================

void checkItem(
    const BloomFilter& filter,
    const std::string& item
)
{
    bool result =
        filter.possiblyContains(item);

    std::cout
        << std::left
        << std::setw(35)
        << item
        << " -> ";

    if (result) {
        std::cout << "Possibly present";
    }
    else {
        std::cout << "Definitely not present";
    }

    std::cout << '\n';
}


// ============================================================
// MAIN BLOOM FILTER DEMONSTRATION
// ============================================================

void runDemo()
{
    std::cout
        << "========================================\n"
        << "          BLOOM FILTER DEMO\n"
        << "========================================\n\n";


    // Bloom Filter configuration.
    const std::size_t filterSize = 128;
    const std::size_t hashFunctions = 3;

    BloomFilter filter(
        filterSize,
        hashFunctions
    );


    // --------------------------------------------------------
    // CONFIGURATION
    // --------------------------------------------------------

    std::cout
        << "Bloom Filter Configuration\n"
        << "--------------------------\n"
        << "Bit array size: "
        << filter.getSize()
        << " bits\n"
        << "Hash functions: "
        << filter.getHashFunctionCount()
        << "\n\n";


    // --------------------------------------------------------
    // DATA TO INSERT
    // --------------------------------------------------------

    std::vector<std::string> knownUrls = {
        "https://example.com",
        "https://google.com",
        "https://github.com",
        "https://stackoverflow.com",
        "https://wikipedia.org",
        "https://cppreference.com",
        "https://python.org",
        "https://postgresql.org"
    };


    // --------------------------------------------------------
    // INSERT URLs
    // --------------------------------------------------------

    std::cout
        << "Inserting URLs...\n"
        << "-----------------\n";

    for (const std::string& url : knownUrls) {
        filter.insert(url);

        std::cout
            << "Inserted: "
            << url
            << '\n';
    }


    // --------------------------------------------------------
    // FILTER INFORMATION
    // --------------------------------------------------------

    std::cout << '\n';

    std::cout
        << "Number of set bits: "
        << filter.getSetBitCount()
        << " / "
        << filter.getSize()
        << '\n';

    filter.printBits();


    // --------------------------------------------------------
    // MEMBERSHIP TESTS
    // --------------------------------------------------------

    std::cout
        << "\n========================================\n"
        << "          MEMBERSHIP TESTS\n"
        << "========================================\n\n";


    std::cout << "Known URLs:\n\n";

    for (const std::string& url : knownUrls) {
        checkItem(filter, url);
    }


    // --------------------------------------------------------
    // UNKNOWN URLs
    // --------------------------------------------------------

    std::cout << "\nUnknown URLs:\n\n";

    std::vector<std::string> unknownUrls = {
        "https://openai.com",
        "https://microsoft.com",
        "https://apple.com",
        "https://amazon.com",
        "https://netflix.com"
    };

    for (const std::string& url : unknownUrls) {
        checkItem(filter, url);
    }


    // --------------------------------------------------------
    // EXPLANATION
    // --------------------------------------------------------

    std::cout
        << "\n========================================\n"
        << "          HOW IT WORKS\n"
        << "========================================\n\n";

    std::cout
        << "1. Insert:\n"
        << "   Each URL is processed by multiple\n"
        << "   hash functions.\n\n";

    std::cout
        << "2. Bit Array:\n"
        << "   Each hash function points to a\n"
        << "   position in the bit array.\n\n";

    std::cout
        << "3. Search:\n"
        << "   If any required bit is 0, the item\n"
        << "   is definitely not present.\n\n";

    std::cout
        << "4. Possible Match:\n"
        << "   If all required bits are 1, the item\n"
        << "   is possibly present.\n\n";

    std::cout
        << "Important:\n"
        << "Bloom Filters can have false positives,\n"
        << "but they cannot have false negatives.\n";
}


// ============================================================
// COMPARISON WITH HASH TABLE
// ============================================================

void showComparison()
{
    std::cout
        << "\n========================================\n"
        << "       BLOOM FILTER VS HASH TABLE\n"
        << "========================================\n\n";


    std::cout
        << std::left
        << std::setw(25)
        << "Feature"
        << std::setw(25)
        << "Bloom Filter"
        << std::setw(25)
        << "Hash Table"
        << '\n';

    std::cout
        << std::string(75, '-')
        << '\n';


    std::cout
        << std::setw(25)
        << "Membership query"
        << std::setw(25)
        << "Very fast"
        << std::setw(25)
        << "Very fast"
        << '\n';


    std::cout
        << std::setw(25)
        << "Memory usage"
        << std::setw(25)
        << "Very low"
        << std::setw(25)
        << "Higher"
        << '\n';


    std::cout
        << std::setw(25)
        << "False positives"
        << std::setw(25)
        << "Possible"
        << std::setw(25)
        << "No"
        << '\n';


    std::cout
        << std::setw(25)
        << "False negatives"
        << std::setw(25)
        << "No"
        << std::setw(25)
        << "No"
        << '\n';


    std::cout
        << std::setw(25)
        << "Stores original data"
        << std::setw(25)
        << "No"
        << std::setw(25)
        << "Yes"
        << '\n';
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    std::cout
        << "Bloom Filter Project\n"
        << "====================\n\n";


    // Run the Bloom Filter demonstration.
    runDemo();


    // Compare it with a hash table.
    showComparison();


    std::cout
        << "\n========================================\n"
        << "              DEMO COMPLETE\n"
        << "========================================\n";


    return 0;
}
