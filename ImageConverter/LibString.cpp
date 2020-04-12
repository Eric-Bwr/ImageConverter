#include "LibString.h"


void LibString::popNull() {
    if(strLen > 0 || data.size() > 0)
        if(data.at(data.size() - 1) == '\0')
            data.pop_back();
}

LibString::LibString() {
    append("");
}

LibString::LibString(const char* string) {
    append(string);
}

void LibString::append(const char* string) {
    popNull();

    auto len = strlen(string);
    strLen += len;
    data.reserve(len + 1);
    for(uint64_t i = 0; i < len; i++) {
        data.emplace_back(string[i]);
    }

    data.emplace_back('\0');
}

void LibString::append(void* strData) {
    char* string = (char*)strData;
    append(string);
}

void LibString::append(char strData) {
    popNull();
    strLen++;
    data.emplace_back(strData);
    data.emplace_back('\0');
}

void LibString::remove(uint64_t begin, uint64_t end) {
    popNull();

    strLen -= end - begin;
    if(end > strLen)
        end = strLen;
    for(uint64_t i = begin; i < end; i++)
        data.erase(data.begin() + begin);

    data.emplace_back('\0');
}

std::vector<char> LibString::getData() const { return data; };
uint64_t LibString::size() const { return strLen; }
uint64_t LibString::length() const { return data.size() - 1; }
uint64_t LibString::sizeWithTermination() const { return strLen + 1; }
uint64_t LibString::lengthWithTermination() const { return data.size(); }

const char* LibString::toString() const { return data.data(); }

bool LibString::contains(const char* searchFor) const {
    uint64_t forLen = strlen(searchFor);

    for(uint64_t i =  0; i < strLen; i ++) {
        if(data[i] == searchFor[0]) {
            for(uint64_t j = 0; j < forLen; j++) {
                if(data[i + j] != searchFor[j]) {
                    break;
                } else {
                    if(j == forLen - 1) return true;
                }
            }
        }
    }

    return false;
}

void LibString::popBack() {
    for(short i = 0; i < 2; i++) {
        data.pop_back();
    }
    strLen--;
    data.emplace_back('\0');
}

void LibString::popBack(uint64_t size) {
    if(size > strLen) clear();
    for(uint64_t i = 0; i < size + 1; i++) {
        data.pop_back();
    }
    data.emplace_back('\0');
}

void LibString::toLower() {
    for(uint64_t i = 0; i < strLen; i++) {
        data.at(i) = tolower(data.at(i));
    }
}

void LibString::toUpper() {
    for(uint64_t i = 0; i < strLen; i++) {
        data.at(i) = toupper(data.at(i));
    }
}

void LibString::clear() { data.clear(); strLen = 0; }


LibString& LibString::operator= (const char* string) {
    this->clear();
    this->append(string);
    return *this;
}

LibString& LibString::operator= (const LibString& string) {
    this->clear();
    this->append(string.toString());
    return *this;
}

void LibString::operator+= (const char* string) {
    this->append(string);
}

std::ostream& operator<<(std::ostream& os, const LibString& string) {
    return os << string.toString();
}
