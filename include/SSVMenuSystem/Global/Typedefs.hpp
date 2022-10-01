// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_GLOBAL_TYPEDEFS
#define SSVMS_GLOBAL_TYPEDEFS

#include <functional>

namespace ssvms
{
    using Action = std::function<void()>;
    using Predicate = std::function<bool()>;

    template <typename T>
    class UniquePtr
    {
    private:
        T* _ptr;

    public:
        [[nodiscard, gnu::always_inline]] explicit UniquePtr() noexcept
            : _ptr{nullptr}
        {}

        [[nodiscard, gnu::always_inline]] explicit UniquePtr(T* ptr) noexcept
            : _ptr{ptr}
        {}

        [[gnu::always_inline]] ~UniquePtr() noexcept
        {
            delete _ptr;
        }

        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        [[nodiscard, gnu::always_inline]] UniquePtr(UniquePtr&& rhs) noexcept
            : _ptr{rhs._ptr}
        {
            rhs._ptr = nullptr;
        }

        [[nodiscard, gnu::always_inline]] T* get() noexcept
        {
            return _ptr;
        }

        [[nodiscard, gnu::always_inline]] const T* get() const noexcept
        {
            return _ptr;
        }

        [[nodiscard, gnu::always_inline]] T& operator*() noexcept
        {
            SSVOH_ASSERT(_ptr != nullptr);
            return *_ptr;
        }

        [[nodiscard, gnu::always_inline]] const T& operator*() const noexcept
        {
            SSVOH_ASSERT(_ptr != nullptr);
            return *_ptr;
        }

        [[nodiscard, gnu::always_inline]] T* operator->() noexcept
        {
            SSVOH_ASSERT(_ptr != nullptr);
            return _ptr;
        }

        [[nodiscard, gnu::always_inline]] const T* operator->() const noexcept
        {
            SSVOH_ASSERT(_ptr != nullptr);
            return _ptr;
        }

        [[nodiscard, gnu::always_inline]] bool operator==(
            const T* ptr) const noexcept
        {
            return _ptr == ptr;
        }

        [[nodiscard, gnu::always_inline]] bool operator!=(
            const T* ptr) const noexcept
        {
            return _ptr != ptr;
        }

        [[nodiscard, gnu::always_inline]] bool operator==(
            decltype(nullptr)) const noexcept
        {
            return _ptr == nullptr;
        }

        [[nodiscard, gnu::always_inline]] bool operator!=(
            decltype(nullptr)) const noexcept
        {
            return _ptr != nullptr;
        }
    };

    template <typename T, typename... Ts>
    [[nodiscard, gnu::always_inline]] inline UniquePtr<T> makeUnique(Ts&&... xs)
    {
        return UniquePtr<T>{new T{static_cast<Ts&&>(xs)...}};
    }
}

#endif
