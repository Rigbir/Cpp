//
// Created by Marat on 5.06.25.
//

#include "String.h"
#include <string_view>
#include <algorithm>
#include <cstring>

#define THROW_OUT_OF_RANGE(msg) throw std::out_of_range(std::string(msg) + \
" [File: " + __FILE__ + ", Line: " + std::to_string(__LINE__) + "]")
#define INVALID_ARGUMENT(msg) throw std::invalid_argument(std::string(msg) + \
" [File: " + __FILE__ + ", Line: " + std::to_string(__LINE__) + "]")

MyString::Data::Data(size_t capacity)
        : arr(new char[capacity])
        , StrSize_(0)
        , StrCapacity_(capacity) {
    arr[StrSize_] = '\0';
}

MyString::Data::Data(const char* str, size_t size)
        : arr(new char[size + 1])
        , StrSize_(size)
        , StrCapacity_(size + 1) {
    std::memcpy(arr, str, size);
    arr[size] = '\0';
}

MyString::Data::~Data() {
    delete[] arr;
}

void MyString::detach() {
    if (!data_ || data_.use_count() == 1) {
        return; 
    }
    
    auto newData = std::make_shared<Data>(data_->StrCapacity_);
    newData->StrSize_ = data_->StrSize_;
    std::memcpy(newData->arr, data_->arr, data_->StrSize_ + 1);
    data_ = newData; 
}

MyString::MyString()
        : data_(std::make_shared<Data>(1)) {}

MyString::MyString(size_t size)
        : data_(std::make_shared<Data>(size + 1)) {
    data_->StrSize_ = size;
    data_->arr[size] = '\0';
}

MyString::MyString(size_t size, char c)
        : data_(std::make_shared<Data>(size + 1)) {
    data_->StrSize_ = size;
    std::fill(data_->arr, data_->arr + size, c);
    data_->arr[size] = '\0';
}

MyString::MyString(const char* str) {
    if (!str) str = "";
    size_t len = strlen(str);
    data_ = std::make_shared<Data>(str, len);
}

MyString::MyString(std::initializer_list<char> list)
        : data_(std::make_shared<Data>(list.size() + 1)) {
    data_->StrSize_ = list.size();
    std::copy(list.begin(), list.end(), data_->arr);
    data_->arr[list.size()] = '\0';
}

MyString::MyString(const MyString& other)
        : data_(other.data_) {}

MyString::MyString(MyString&& other) noexcept
        : data_(std::move(other.data_)) {
    other.data_ = nullptr;
}

MyString& MyString::operator = (const MyString& other) {
    if (this != &other) {
        data_ = other.data_;  
    }
    return *this;
}

MyString& MyString::operator = (MyString&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        other.data_ = nullptr;
    }
    return *this;
}

char& MyString::operator [] (size_t index) {
    detach();
    return data_->arr[index];
}

const char& MyString::operator [] (size_t index) const {
    return data_->arr[index];
}

char& MyString::at(size_t index) {
    detach();  
    validIndex(index);
    return data_->arr[index];
}

const char& MyString::at(size_t index) const {
    validIndex(index);
    return data_->arr[index];
}

char& MyString::front() {
    detach(); 
    checkEmpty();
    return data_->arr[0];
}

const char& MyString::front() const {
    checkEmpty();
    return data_->arr[0];
}

char& MyString::back() {
    detach();  
    checkEmpty();
    return data_->arr[data_->StrSize_ - 1];
}

const char& MyString::back() const {
    checkEmpty();
    return data_->arr[data_->StrSize_ - 1];
}

void MyString::clear() {
    detach();  
    if (data_) {
        data_->arr[0] = '\0';
        data_->StrSize_ = 0;
    }
}

void MyString::push_back(char c) {
    detach();

    if (data_->StrSize_ >= data_->StrCapacity_) {
        size_t newCapacity = data_->StrSize_ == 0 ? 2 : data_->StrCapacity_ * 2;
        reallocate(newCapacity);
    }
    data_->arr[data_->StrSize_++] = c;
    data_->arr[data_->StrSize_] = '\0';
}

void MyString::pop_back() {
    detach();  
    checkEmpty();
    data_->arr[--data_->StrSize_] = '\0';
}

void MyString::resize(size_t newSize) {
    detach(); 
    if (newSize >= data_->StrCapacity_) {
        size_t newCapacity = data_->StrSize_ == 0 ? 2 : newSize * 2;
        reallocate(newCapacity);
    }

    if (newSize > data_->StrSize_) {
        std::memset(data_->arr + data_->StrSize_, '\0', newSize - data_->StrSize_);
    }

    data_->StrSize_ = newSize;
    data_->arr[newSize] = '\0';
}

void MyString::reserve(size_t newCapacity) {
    detach();  
    if (newCapacity > data_->StrCapacity_) {
        reallocate(newCapacity);
    }
}

void MyString::shrink_to_fit() {
    detach(); 
    if (data_->StrCapacity_ > data_->StrSize_) {
        reallocate(data_->StrSize_);
    }
}

void MyString::swap(MyString& other) noexcept {
    data_.swap(other.data_);
}

void MyString::insert(size_t pos, char c) {
    detach();  
    validIndex(pos);

    if (data_->StrSize_ + 1 >= data_->StrCapacity_) {
        size_t newCapacity = data_->StrSize_ == 0 ? 2 : data_->StrCapacity_ * 2;
        reallocate(newCapacity);
    }

    std::memmove(data_->arr + pos + 1, data_->arr + pos, data_->StrSize_ - pos);

    data_->arr[pos] = c;
    ++data_->StrSize_;
    data_->arr[data_->StrSize_] = '\0';
}

void MyString::erase(size_t pos) {
    detach(); 
    validIndex(pos);

    std::memmove(data_->arr + pos, data_->arr + pos + 1, data_->StrSize_ - pos);

    --data_->StrSize_;
    data_->arr[data_->StrSize_] = '\0';
}

MyString MyString::operator + (const MyString& other) const {
    size_t totalSize = get_size() + other.get_size();

    MyString newString(totalSize);

    std::memcpy(newString.data_->arr, data_->arr, get_size());
    std::memcpy(newString.data_->arr + get_size(), other.data_->arr, other.get_size());
    newString.data_->StrSize_ = totalSize;
    newString.data_->arr[totalSize] = '\0';

    return newString;
}

MyString& MyString::operator += (const MyString& other) {
    detach();  
    if (data_->StrSize_ + other.data_->StrSize_ >= data_->StrCapacity_) {
        size_t newCapacity = data_->StrSize_ + other.data_->StrSize_ + 1;
        reallocate(newCapacity);
    }

    std::memcpy(data_->arr + data_->StrSize_, other.data_->arr, other.data_->StrSize_);
    data_->StrSize_ += other.data_->StrSize_;
    data_->arr[data_->StrSize_] = '\0';

    return *this;
}

bool MyString::operator == (const MyString& other) const {
    if (get_size() != other.get_size()) return false;
    return std::memcmp(data_->arr, other.data_->arr, get_size()) == 0;
}

bool MyString::operator != (const MyString& other) const {
    return !(*this == other);
}

bool MyString::operator < (const MyString& other) const {
    size_t minLength = std::min(get_size(), other.get_size());

    int cmp = std::memcmp(data_->arr, other.data_->arr, minLength);
    if (cmp != 0) {
        return cmp < 0;
    }

    return get_size() < other.get_size();
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

    if (pos + len > get_size()) {
        THROW_OUT_OF_RANGE("SubString out of range String.");
    }

    MyString substring(len);
    std::memcpy(substring.data_->arr, data_->arr + pos, len);
    substring.data_->arr[len] = '\0';

    return substring;
}

size_t MyString::find(char c, size_t start) const {
    for (size_t i = start; i < get_size(); ++i) {
            if (data_->arr[i] == c) {
                return i;
            }
    }

    return npos;
}

size_t MyString::find(const MyString& other, size_t start) const {
    if (other.get_size() == 0) return start;
    if ((other.get_size() + start) > get_size()) return npos;
    validIndex(start);

    for (size_t i = start; i <= (get_size() - other.get_size()); ++i) {
        char* first = &(data_->arr[i]);
        char* second = &(other.data_->arr[0]);

        if (*first == *second) {

            size_t j = 0;
            while (*first == *second && j < other.get_size()) {
                ++j;
                ++first;
                ++second;
            }

            if (j == other.get_size()) {
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
    detach(); 
    return data_ ? &data_->arr[0] : nullptr;
}

char* MyString::end() {
    detach(); 
    return data_ ? &data_->arr[data_->StrSize_] : nullptr;
}

const char* MyString::begin() const {
    return data_ ? &data_->arr[0] : nullptr;
}

const char* MyString::end() const {
    return data_ ? &data_->arr[data_->StrSize_] : nullptr;
}

size_t MyString::size() const noexcept {
    return get_size();
}

size_t MyString::capacity() const noexcept {
    return get_capacity();
}

bool MyString::empty() const noexcept {
    return get_size() == 0;
}

void MyString::print() const {
    if (data_) {
        std::cout << std::string_view(data_->arr, data_->StrSize_) << '\n';
    }
}

std::ostream& operator << (std::ostream& os, const MyString& str) {
    if (str.data_) {
        return os << str.data_->arr;
    }
    return os;
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
    if (index >= get_size()) {
        THROW_OUT_OF_RANGE("Index out of range.");
    }
}

void MyString::reallocate(size_t newCapacity) {
    auto newData = std::make_shared<Data>(newCapacity);
    newData->StrSize_ = data_->StrSize_;
    std::memcpy(newData->arr, data_->arr, data_->StrSize_ + 1);
    data_ = newData;
}

char* MyString::get_arr() const {
    return data_ ? data_->arr : nullptr;
}

size_t MyString::get_size() const {
    return data_ ? data_->StrSize_ : 0;
}

size_t MyString::get_capacity() const {
    return data_ ? data_->StrCapacity_ : 0;
}

MyString::~MyString() {

}
