//
// Created by Marat on 5.06.25.
//

#include "String.h"
#include <algorithm>
#include <string_view>
#include <complex>

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
        char* newArr = new char[other.StrCapacity_];
        std::ranges::copy(other.arr, other.arr + other.StrSize_, newArr);
        newArr[other.StrSize_] = '\0';

        delete[] arr;
        arr = newArr;
        StrSize_ = other.StrSize_;
        StrCapacity_ = other.StrCapacity_;
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

char& MyString::front() const {
    checkEmpty();
    return arr[0];
}

char &MyString::back() const {
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
    arr[StrSize_--] = '\0';
}

void MyString::resize(size_t newSize) {
    if (newSize >= StrCapacity_) {
        size_t newCapacity = StrSize_ == 0 ? 2 : newSize * 2;
        reallocate(newCapacity);
    }

    for (size_t i = 0; i < newSize; ++i) {
        arr[i] = '0';
    }

    StrSize_ = newSize;
    arr[StrSize_] = '\0';
}

void MyString::reserve(size_t newCapacity) {
    StrCapacity_ = newCapacity;
}

void MyString::shrink_to_fit() {
    if (StrCapacity_ > StrSize_) {
        reallocate(StrSize_);
    }
}

void MyString::insert(size_t pos, char c) {
    validIndex(pos);

    if (StrSize_ + 1 >= StrCapacity_) {
        size_t newCapacity = StrSize_ == 0 ? 2 : StrCapacity_ * 2;
        reallocate(newCapacity);
    }

    for (size_t i = StrSize_; i > pos; --i) {
        arr[i] = arr[i - 1];
    }

    arr[pos] = c;
    ++StrSize_;
    arr[StrSize_] = '\0';
}

void MyString::erase(size_t pos) {
    validIndex(pos);

    for (size_t i = pos; i < StrSize_; ++i) {
        arr[i] = arr[i + 1];
    }

    --StrSize_;
    arr[StrSize_] = '\0';
}

MyString MyString::operator + (const MyString& other) const {
    size_t totalSize = this->StrSize_ + other.StrSize_;

    MyString newString(totalSize);

    for (size_t i = 0; i < this->StrSize_; ++i) {
        newString[i] = this->arr[i];
    }

    for (size_t i = 0; i < other.StrSize_; ++i) {
        newString[i + this->StrSize_] = other.arr[i];
    }

    newString[totalSize] = '\0';
    return newString;
}

MyString& MyString::operator += (const MyString& other) {
    if (other.StrSize_ > (this->StrCapacity_ - this->StrSize_)) {
        size_t newCapacity = this->StrSize_ + other.StrSize_ + 1;
        reallocate(newCapacity);
    }

    for (size_t i = 0; i < other.StrSize_; ++i) {
        this->arr[i + this->StrSize_] = other.arr[i];
    }

    this->StrSize_ += other.StrSize_;
    this->arr[StrSize_] = '\0';
    return *this;
}

bool MyString::operator == (const MyString& other) const {
    if (this->StrSize_ != other.StrSize_) return false;

    for (size_t i = 0; i < this->StrSize_; ++i) {
        if (this->arr[i] != other.arr[i]) {
            return false;
        }
    }

    return true;
}

bool MyString::operator != (const MyString& other) const {
    return !(*this == other);
}

bool MyString::operator < (const MyString& other) const {
    size_t minLength = std::min(this->StrSize_, other.StrSize_);

    for (size_t i = 0; i < minLength; ++i) {
        if (this->arr[i] < other.arr[i]) return true;
        if (this->arr[i] > other.arr[i]) return false;
    }

    return this->StrSize_ < other.StrSize_;
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

    if (pos + len > this->StrSize_) {
        THROW_OUT_OF_RANGE("SubString out of range String.");
    }

    MyString substring(len);

    for (size_t i = 0; i < len; ++i) {
        substring.arr[i] = this->arr[pos + i];
    }

    return substring;
}

size_t MyString::find(char c, size_t start) const {
    for (size_t i = start; i < this->StrSize_; ++i) {
            if (this->arr[i] == c) {
                return i;
            }
    }

    return npos;
}

size_t MyString::find(const MyString& other, size_t start) const {
    if (other.StrSize_ == 0) return start;
    if ((other.StrSize_ + start) > this->StrSize_) return npos;
    validIndex(start);

    for (size_t i = start; i <= (this->StrSize_ - other.StrSize_); ++i) {
        char* first = &(this->arr[i]);
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

    for (size_t i = 0; i < StrSize_; ++i) {
        newArr[i] = arr[i];
    }
    newArr[StrSize_] = '\0';

    delete[] arr;
    arr = newArr;
    StrCapacity_ = newCapacity;
}

MyString::~MyString() {
    delete[] arr;
}
