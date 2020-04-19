#pragma once

#include <cstdint>
#include <vector>
#include <cstring>
#include <ostream>

class LibString {
public:
    uint64_t strLen = 0;
    std::vector<char> data;

private:
    void popNull();
public:
    LibString();
    LibString(const char* string);

    void append(const char* string);
    void append(void* strData);
    void append(char strData);
    uint64_t findLast(LibString searchFor);
    LibString substring(uint64_t begin, uint64_t end);
    void remove(uint64_t begin, uint64_t end);

    std::vector<char> getData() const;
    uint64_t size() const;
    uint64_t length() const;
    uint64_t sizeWithTermination() const;
    uint64_t lengthWithTermination() const;

    const char* toString() const;
    bool contains(const char* searchFor) const;
    void popBack();
    void popBack(uint64_t size);
    void toLower();
    void toUpper();
    void clear();

public: //operator overloading
    LibString& operator= (const char* string);
    LibString& operator= (const LibString& string);
    void operator+= (const char* string);
    friend std::ostream& operator<<(std::ostream& os, const LibString& string);
};