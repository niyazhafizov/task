#include <cstddef>
#include <iostream>
#include <tuple>

template<typename T>
struct Deleter {
    /// Default constructor
    Deleter() noexcept = default;

    void operator()(T *__ptr) const {
        delete __ptr;
    }
};

template<typename T, typename MyDeleter = Deleter<T>>
class UniquePtr {
private:
    std::tuple<T *, MyDeleter> ptr;

public:
    // 1 +
    explicit UniquePtr() : ptr() {
    }

    // 2 +
    explicit UniquePtr(T *_ptr) : ptr(_ptr, MyDeleter()) {
    }

    // 3 + || Почему можно писать без <T>
    UniquePtr(UniquePtr &&other) noexcept {
        std::get<0>(ptr) = other.release();
        get_deleter() = std::forward<MyDeleter>(other.get_deleter());
    }


    explicit UniquePtr(T *_ptr, MyDeleter _deleter) : ptr(_ptr, _deleter) {
    }

    // 4 +
    UniquePtr &operator=(std::nullptr_t) noexcept {
        get_deleter()(ptr);
        return *this;
    }

    // 5 +
    UniquePtr &operator=(UniquePtr &&other) noexcept {
        reset(other.release());
        get_deleter() = std::forward<MyDeleter>(other.get_deleter());
        return *this;
    }

    // 6 +
    ~UniquePtr() noexcept {
        auto &__ptr = std::get<0>(ptr);
        if (__ptr != nullptr)
            get_deleter()(__ptr);
        __ptr = nullptr;
    }

    // 7 +
    T &operator*() {
        return *std::get<0>(ptr);
    }

    T &operator*() const {
        return *std::get<0>(ptr);
    }

    // 8 +
    T *operator->() const noexcept {
        return std::get<0>(ptr);
    }

    // 9 +
    T *release() noexcept {
        T *tmp = std::get<0>(ptr);
        std::get<0>(ptr) = nullptr;
        return tmp;
    }

    // 10 +
    void reset(T *_ptr) noexcept {
        std::swap(std::get<0>(ptr), _ptr);
        get_deleter()(_ptr);
    }

// 11 +
    void swap(UniquePtr &other) noexcept {
        std::swap(ptr, other.ptr);
    }

// 12 +
    T *get() const noexcept {
        return std::get<0>(ptr);
    }

// 13 +
    explicit operator bool() const noexcept {
        return std::get<0>(ptr) != nullptr;
    }

    MyDeleter &get_deleter() {
        return std::get<1>(ptr);
    }

    MyDeleter &get_deleter() const {
        return std::get<1>(ptr);
    }
};
