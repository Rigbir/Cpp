//
// Created by Marat on 25.09.25.
//

#include <algorithm>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
private:
    T* ptr_;
    [[no_unique_address]] Deleter del_;

    template <typename U, typename... Args>
    friend unique_ptr<U> make_unique(Args&&... args);

public:
    constexpr unique_ptr() noexcept: ptr_(ptr_), del_() {}
    constexpr explicit unique_ptr(std::nullptr_t) noexcept: ptr_(nullptr), del_() {}

    explicit  unique_ptr(T* ptr) noexcept: ptr_(ptr), del_() {}
    explicit  unique_ptr(T* ptr, Deleter del) noexcept: ptr_(ptr), del_(std::move(del)) {}

    ~unique_ptr() {
        del_(ptr_);
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    constexpr unique_ptr(unique_ptr&& other) noexcept
            : ptr_(other.ptr_), del_(std::move(other.del_)) {
        other.ptr_ = nullptr;
    }

    constexpr unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr_ = other.ptr_;
            del_ = std::move(other.del_);
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T* release() noexcept {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void reset(T* ptr = nullptr) noexcept {
        if (ptr_ != ptr) {
            del_(ptr_);
            ptr_ = ptr;
        }
    }

    void swap(unique_ptr& other) noexcept {
        std::swap(ptr_, other.ptr_);
        std::swap(del_, other.del_);
    }

    Deleter& get_deleter() noexcept {
        return del_;
    }

    const Deleter& get_deleter() const noexcept {
        return del_;
    }

    explicit operator bool() const noexcept {
        return get() != nullptr;
    }

    T& operator*() noexcept {
        return *ptr_;
    }
    const T& operator*() const noexcept {
        return *ptr_;
    }

    T* operator->() noexcept {
        return ptr_;
    }
    const T* operator->() const noexcept {
        return ptr_;
    }

    T* get() noexcept {
        return ptr_;
    }
    const T* get() const noexcept {
        return ptr_;
    }

    bool operator==(const unique_ptr& other) const {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const unique_ptr& other) const {
        return ptr_ != other.ptr_;
    }

    bool operator==(std::nullptr_t) const {
        return ptr_ == nullptr;
    }
    bool operator!=(std::nullptr_t) const {
        return ptr_ != nullptr;
    }
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}