//
// Created by Marat on 5.06.25.
//

#pragma once

#include <initializer_list>
#include <iostream>
#include <memory>

class MyString {
public:

    MyString();
    explicit MyString(size_t size);
    explicit MyString(size_t size, char c);
    MyString(const char* str);
    MyString(std::initializer_list<char> list);
    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    ~MyString();

    MyString& operator = (const MyString& other);
    MyString& operator = (MyString&& other) noexcept;

    char& operator [] (size_t index);
    const char& operator [] (size_t index) const;
    [[nodiscard]] char& at(size_t index);
    [[nodiscard]] const char& at(size_t index) const;
    [[nodiscard]] char& front();
    [[nodiscard]] const char& front() const;
    [[nodiscard]] char& back();
    [[nodiscard]] const char& back() const;

    void clear();
    void push_back(char c);
    void pop_back();
    void resize(size_t newSize);
    void reserve(size_t newCapacity);
    void shrink_to_fit();
    void swap(MyString& other) noexcept;

    void insert(size_t pos, char c);
    void erase(size_t pos);
    MyString operator + (const MyString& other) const;
    MyString& operator += (const MyString& other);
    bool operator == (const MyString& other) const;
    bool operator != (const MyString& other) const;
    bool operator < (const MyString& other) const;
    bool operator > (const MyString& other) const;
    bool operator <= (const MyString& other) const;
    bool operator >= (const MyString& other) const;
    MyString substr(size_t pos, size_t len) const;

    static constexpr size_t npos = static_cast<size_t>(-1);
    size_t find(char c, size_t start = 0) const;
    size_t find(const MyString& other, size_t start = 0) const;
    bool contains(const MyString& other) const;

    char* begin();
    char* end();
    const char* begin() const;
    const char* end() const;

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] size_t capacity() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

    void print() const;
    friend std::ostream& operator << (std::ostream& os, const MyString& str);
    friend std::istream& operator >> (std::istream& is, MyString& str);

private:
    struct Data {
        char* arr;
        size_t StrSize_;
        size_t StrCapacity_;

        Data(size_t capacity);
        Data(const char* str, size_t size);
        ~Data();

        Data(const Data& other) = delete;
        Data& operator = (const Data& other) = delete;
    };

    std::shared_ptr<Data> data_;

    void detach();
    char* get_arr() const;
    size_t get_size() const;
    size_t get_capacity() const;

    static size_t strlen(const char* start);
    void checkEmpty() const;
    void validIndex(size_t index) const;
    void reallocate(size_t newCapacity);
};