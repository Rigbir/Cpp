//
// Created by Marat on 5.06.25.
//

#include "String.h"
#include <algorithm>
#include <string_view>
#include <cstring>

#define THROW_OUT_OF_RANGE(msg) throw std::out_of_range(std::string(msg) + \
" [File: " + __FILE__ + ", Line: " + std::to_string(__LINE__) + "]")
#define INVALID_ARGUMENT(msg) throw std::invalid_argument(std::string(msg) + \
" [File: " + __FILE__ + ", Line: " + std::to_string(__LINE__) + "]")

MyString::MyString(): arr(nullptr), StrSize_(0), StrCapacity_(0) {}

MyString::MyString(size_t size)
        : arr(new char[size + 1])
        , StrSize_(size)
        , StrCapacity_(size + 1) {
    arr[StrSize_] = '\0';
}

MyString::MyString(size_t size, char c)
        : arr(new char[size + 1])
        , StrSize_(size)
        , StrCapacity_(size + 1) {
    std::ranges::fill(arr, arr + StrSize_, c);
    arr[StrSize_] = '\0';
}

MyString::MyString(const char* str) {
    if (!str) str = "";

    arr = new char[strlen(str) + 1];
    StrSize_ = strlen(str);
    StrCapacity_ = strlen(str) + 1;

    std::memcpy(arr, str, StrSize_);
    arr[StrSize_] = '\0';
}

MyString::MyString(std::initializer_list<char> list)
        : arr(new char[list.size() + 1])
        , StrSize_(list.size())
        , StrCapacity_(list.size() + 1) {
    std::ranges::copy(list.begin(), list.end(), arr);
    arr[StrSize_] = '\0';
}

MyString::MyString(const MyString& other)
        : arr(new char[other.StrCapacity_])
        , StrSize_(other.StrSize_)
        , StrCapacity_(other.StrCapacity_) {
    std::ranges::copy(other.arr, other.arr + other.StrSize_, arr);
    arr[other.StrSize_] = '\0';
}

MyString::MyString(MyString&& other) noexcept
        : arr(other.arr)
        , StrSize_(other.StrSize_)
        , StrCapacity_(other.StrCapacity_) {
    other.arr = nullptr;
    other.StrSize_ = 0;
    other.StrCapacity_ = 0;
}

MyString& MyString::operator = (const MyString& other) {
    if (this != &other) {
        MyString temp(other);
        swap(temp);
    }
    return *this;
}

MyString& MyString::operator = (MyString&& other) noexcept {
    if (this != &other) {
        delete[] arr;

        arr = other.arr;
        StrSize_ = other.StrSize_;
        StrCapacity_ = other.StrCapacity_;

        other.arr = nullptr;
        other.StrSize_ = 0;
        other.StrCapacity_ = 0;
    }
    return *this;
}

char& MyString::operator [] (size_t index) {
    return arr[index];
}

const char& MyString::operator [] (size_t index) const {
    return arr[index];
}

char& MyString::at(size_t index) {
    validIndex(index);
    return arr[index];
}

const char& MyString::at(size_t index) const {
    validIndex(index);
    return arr[index];
}

char& MyString::front() {
    checkEmpty();
    return arr[0];
}

const char& MyString::front() const {
    checkEmpty();
    return arr[0];
}

char& MyString::back() {
    checkEmpty();
    return arr[StrSize_ - 1];
}

const char& MyString::back() const {
    checkEmpty();
    return arr[StrSize_ - 1];
}

void MyString::clear() {
    if (arr) {
        arr[0] = '\0';
    }
    StrSize_ = 0;
}

void MyString::push_back(char c) {
    if (StrSize_ >= StrCapacity_) {
        size_t newCapacity = StrSize_ == 0 ? 2 : StrCapacity_ * 2;
        reallocate(newCapacity);
    }
    arr[StrSize_++] = c;
    arr[StrSize_] ='\0';
}

void MyString::pop_back() {
    checkEmpty();
    arr[StrSize_--] = '\0';
}

void MyString::resize(size_t newSize) {
    if (newSize >= StrCapacity_) {
        size_t newCapacity = StrSize_ == 0 ? 2 : newSize * 2;
        reallocate(newCapacity);
    }

    if (newSize > StrSize_) {
        std::memset(arr + StrSize_, '\0', newSize - StrSize_);
    }

    StrSize_ = newSize;
    arr[StrSize_] = '\0';
}

void MyString::reserve(size_t newCapacity) {
    if (newCapacity > StrCapacity_) {
        reallocate(newCapacity);
    }
}

void MyString::shrink_to_fit() {
    if (StrCapacity_ > StrSize_) {
        reallocate(StrSize_);
    }
}

void MyString::swap(MyString& other) noexcept {
    std::swap(arr, other.arr);
    std::swap(StrSize_, other.StrSize_);
    std::swap(StrCapacity_, other.StrCapacity_);
}

void MyString::insert(size_t pos, char c) {
    validIndex(pos);

    if (StrSize_ + 1 >= StrCapacity_) {
        size_t newCapacity = StrSize_ == 0 ? 2 : StrCapacity_ * 2;
        reallocate(newCapacity);
    }

    std::memmove(arr + pos + 1, arr + pos, StrSize_ - pos);

    arr[pos] = c;
    ++StrSize_;
    arr[StrSize_] = '\0';
}

void MyString::erase(size_t pos) {
    validIndex(pos);

    std::memmove(arr + pos, arr + pos + 1, StrSize_ - pos);

    --StrSize_;
    arr[StrSize_] = '\0';
}

MyString MyString::operator + (const MyString& other) const {
    size_t totalSize = StrSize_ + other.StrSize_;

    MyString newString(totalSize);

    std::memcpy(newString.arr, arr, StrSize_);
    std::memcpy(newString.arr + StrSize_, other.arr, other.StrSize_);
    newString.StrSize_ = totalSize;

    return newString;
}

MyString& MyString::operator += (const MyString& other) {
    if (StrSize_ + other.StrSize_ >= StrCapacity_) {
        size_t newCapacity = StrSize_ + other.StrSize_ + 1;
        reallocate(newCapacity);
    }

    std::memcpy(arr + StrSize_, other.arr, other.StrSize_);
    StrSize_ += other.StrSize_;
    arr[StrSize_] = '\0';

    return *this;
}

bool MyString::operator == (const MyString& other) const {
    if (StrSize_ != other.StrSize_) return false;
    return std::memcmp(arr, other.arr, StrSize_) == 0;
}

bool MyString::operator != (const MyString& other) const {
    return !(*this == other);
}

bool MyString::operator < (const MyString& other) const {
    size_t minLength = std::min(StrSize_, other.StrSize_);

    int cmp = std::memcmp(arr, other.arr, minLength);
    if (cmp != 0) {
        return cmp < 0;
    }

    return StrSize_ < other.StrSize_;
}

bool MyString::operator > (const MyString& other) const {
    return other < *this;
}

bool MyString::operator <= (const MyString& other) const {
    return !(other < *this);
}

bool MyString::operator >= (const MyString& other) const {
    return !(*this < other);
}

MyString MyString::substr(size_t pos, size_t len) const {
    validIndex(pos);

    if (pos + len > StrSize_) {
        THROW_OUT_OF_RANGE("SubString out of range String.");
    }

    MyString substring(len);
    std::memcpy(substring.arr, arr + pos, len);

    return substring;
}

size_t MyString::find(char c, size_t start) const {
    for (size_t i = start; i < StrSize_; ++i) {
            if (arr[i] == c) {
                return i;
            }
    }

    return npos;
}

size_t MyString::find(const MyString& other, size_t start) const {
    if (other.StrSize_ == 0) return start;
    if ((other.StrSize_ + start) > StrSize_) return npos;
    validIndex(start);

    for (size_t i = start; i <= (StrSize_ - other.StrSize_); ++i) {
        char* first = &(arr[i]);
        char* second = &(other.arr[0]);

        if (*first == *second) {

            size_t j = 0;
            while (*first == *second && j < other.StrSize_) {
                ++j;
                ++first;
                ++second;
            }

            if (j == other.StrSize_) {
                return i;
            }
        }
    }

    return npos;
}

bool MyString::contains(const MyString& other) const {
    return find(other) != npos;
}

char* MyString::begin() {
    return &arr[0];
}

char* MyString::end() {
    return &arr[StrSize_];
}

const char* MyString::begin() const {
    return &arr[0];
}

const char* MyString::end() const {
    return &arr[StrSize_];
}

size_t MyString::size() const noexcept {
    return StrSize_;
}

size_t MyString::capacity() const noexcept {
    return StrCapacity_;
}

bool MyString::empty() const noexcept {
    return StrSize_ == 0;
}

void MyString::print() const {
    std::cout << std::string_view(arr, StrSize_) << '\n';
}

std::ostream& operator << (std::ostream& os, const MyString& str) {
    return os << str.arr;
}

std::istream& operator >> (std::istream& is, MyString& str) {
    char buffer[1024];
    is >> buffer;
    str = MyString(buffer);
    return is;
}

size_t MyString::strlen(const char* start) {
    const char* end = start;

    while (*end != '\0') {
        ++end;
    }

    return end - start;
}

void MyString::checkEmpty() const {
    if (empty()) {
        INVALID_ARGUMENT("String is empty.");
    }
}

void MyString::validIndex(size_t index) const {
    if (index >= StrSize_) {
        THROW_OUT_OF_RANGE("Index out of range.");
    }
}

void MyString::reallocate(size_t newCapacity) {
    char* newArr = new char[newCapacity + 1];

    std::memcpy(newArr, arr, StrSize_);
    newArr[StrSize_] = '\0';

    delete[] arr;
    arr = newArr;
    StrCapacity_ = newCapacity;
}

MyString::~MyString() {
    delete[] arr;
}
