# Bloom Filter Project

## A Fast Way to Test Whether an Item Exists

## Project Overview

This project implements a **Bloom Filter**, a probabilistic data structure designed for fast and memory-efficient membership testing.

A Bloom Filter can answer whether an item is:

* **Definitely not present**, or
* **Possibly present**

The important property of a Bloom Filter is that it can produce **false positives**, but it does not produce false negatives.

For example, if a URL is inserted into the Bloom Filter, searching for that URL will always return "possibly present." However, another URL that was never inserted may also return "possibly present" if it happens to produce the same bit positions.

This project uses URLs as a practical example of membership testing.

---

## Data Structure Implemented

The main data structure implemented in this project is a **Bloom Filter**.

The Bloom Filter consists of:

1. A bit array.
2. Multiple hash functions.
3. An insertion operation.
4. A membership-testing operation.

When an item is inserted, each hash function generates a position in the bit array. Those positions are changed from `0` to `1`.

When searching for an item, the same hash functions are used to calculate the positions.

If any required position contains `0`, the item is definitely not present.

If all required positions contain `1`, the item is possibly present.

---

## Why Bloom Filters?

Many applications need to quickly determine whether an item has already been seen.

Examples include:

* Web caching
* Database systems
* Distributed storage
* Search systems
* Cybersecurity
* URL checking

Storing millions of items in a traditional data structure can require significant memory.

A Bloom Filter provides a memory-efficient alternative when a small possibility of false positives is acceptable.

The Bloom Filter does not store the original items. It only stores information about which positions in the bit array have been set.

---

## How This Project Works

The project uses:

* **128 bits** in the bit array.
* **3 hash functions** for each item.

The demonstration inserts several URLs:

```text
https://example.com
https://google.com
https://github.com
https://stackoverflow.com
https://wikipedia.org
https://cppreference.com
https://python.org
https://postgresql.org
```

The program then checks both known and unknown URLs.

A known URL should return:

```text
Possibly present
```

An unknown URL will normally return:

```text
Definitely not present
```

Because Bloom Filters are probabilistic, an unknown URL could also return "possibly present." This would be a false positive.

---

## Hashing

The implementation uses two base hash functions.

The project then uses **double hashing** to generate multiple positions in the bit array:

```text
h1 + i × h2
```

where:

* `h1` is the first hash value.
* `h2` is the second hash value.
* `i` represents the hash-function number.

This allows the implementation to generate several hash positions without having to write a completely separate hash function for every position.

---

## Main Operations

### Insert

The `insert()` operation processes the item using all hash functions and sets the corresponding bits to `1`.

```cpp
filter.insert("https://github.com");
```

### Membership Test

The `possiblyContains()` operation checks all required positions.

```cpp
filter.possiblyContains("https://github.com");
```

It returns:

* `false` → definitely not present
* `true` → possibly present

---

## False Positives

A Bloom Filter can produce a false positive.

For example:

```text
Item was never inserted
        ↓
Hash functions calculate positions
        ↓
All calculated bits happen to be 1
        ↓
Result: Possibly present
```

The result does not mean the item definitely exists.

This is the main trade-off of the Bloom Filter.

---

## False Negatives

A Bloom Filter does not produce false negatives.

If an item was inserted, all of its required bits were set to `1`.

Therefore, when the same item is searched later, those bits will still be `1`.

The result will always be:

```text
Possibly present
```

---

## Bloom Filter vs. Hash Table

| Feature              | Bloom Filter | Hash Table |
| -------------------- | ------------ | ---------- |
| Membership query     | Very fast    | Very fast  |
| Memory usage         | Very low     | Higher     |
| False positives      | Possible     | No         |
| False negatives      | No           | No         |
| Stores original data | No           | Yes        |

The Bloom Filter is useful when memory efficiency is important and occasional false positives are acceptable.

A hash table is preferable when the application needs to retrieve the actual stored data and requires exact membership results.

---

## Project Structure

```text
Bloom-Filter-Project/
│
├── README.md
├── .gitignore
│
└── src/
    ├── BloomFilter.h
    ├── BloomFilter.cpp
    └── main.cpp
```

### File Descriptions

**`BloomFilter.h`**

Contains the Bloom Filter class declaration and function definitions that are available to the rest of the program.

**`BloomFilter.cpp`**

Contains the implementation of the Bloom Filter, including hashing, insertion, membership testing, and bit-array operations.

**`main.cpp`**

Runs the demonstration and displays the results and comparison with a hash table.

---

## Requirements

To compile the project, you need a C++ compiler that supports **C++17** or later.

Examples include:

* GCC
* Clang
* Microsoft Visual C++

No external libraries are required.

---

## How to Run

### 1. Clone the repository

```bash
git clone <YOUR-GITHUB-REPOSITORY-URL>
```

### 2. Enter the project directory

```bash
cd Bloom-Filter-Project
```

### 3. Compile the project

Using GCC:

```bash
g++ -std=c++17 src/main.cpp src/BloomFilter.cpp -o bloom_filter
```

### 4. Run the program

On Linux or macOS:

```bash
./bloom_filter
```

On Windows:

```bash
bloom_filter.exe
```

---

## Expected Output

The program displays:

1. Bloom Filter configuration.
2. URLs being inserted.
3. The current bit array.
4. Membership tests for known URLs.
5. Membership tests for unknown URLs.
6. An explanation of how the Bloom Filter works.
7. A comparison between a Bloom Filter and a hash table.

Example:

```text
Bloom Filter Configuration
--------------------------
Bit array size: 128 bits
Hash functions: 3

Inserting URLs...
-----------------
Inserted: https://example.com
Inserted: https://google.com
Inserted: https://github.com

...

Known URLs:

https://example.com                 -> Possibly present
https://google.com                  -> Possibly present
https://github.com                  -> Possibly present

Unknown URLs:

https://openai.com                  -> Definitely not present
https://microsoft.com               -> Definitely not present
```

The exact bit-array contents may vary depending on the C++ implementation because the project uses `std::hash`.

---

## Complexity

Let:

* `k` = number of hash functions.
* `m` = size of the bit array.

### Insertion

Each item is processed by `k` hash functions.

```text
Time: O(k)
```

### Membership Test

The membership test also checks `k` positions.

```text
Time: O(k)
```

### Space

The Bloom Filter stores a bit array rather than the original items.

```text
Space: O(m)
```

The number of hash functions is normally kept small, so the operations are effectively very fast.

---

## Project Goal

The goal of this project is to demonstrate how a Bloom Filter provides fast, memory-efficient membership testing and to understand the trade-off between memory efficiency and the possibility of false positives.

The project also demonstrates why Bloom Filters can be useful in large-scale systems where checking whether an item exists is more important than storing and retrieving the original item.

---

## Author

Data Structures and Algorithms Project

**Language:** C++

**Data Structure:** Bloom Filter
