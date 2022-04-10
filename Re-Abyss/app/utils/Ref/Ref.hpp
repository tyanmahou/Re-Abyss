#pragma once
#include <memory>

namespace abyss
{
    /// <summary>
    /// weak_ptrのラッパー
    /// 楽にアクセスできるがマルチスレッドの際には注意
    /// </summary>
    template<class T>
    class Ref
    {
        std::weak_ptr<T> m_ptr;
    public:
        Ref() = default;
        Ref(const std::shared_ptr<T>& sharedPtr):
            m_ptr(sharedPtr)
        {}
        Ref(std::nullptr_t) :
            m_ptr(std::weak_ptr<T>())
        {}
        [[nodiscard]] T& operator *()const noexcept
        {
            return *get();
        }

        [[nodiscard]] T* operator->()const noexcept
        {
            return get();
        }
        [[nodiscard]] T* get() const noexcept
        {
            auto  lock = m_ptr.lock();
            auto p = lock.get();
            return p;
        }

        [[nodiscard]] bool isValid() const
        {
            return !m_ptr.expired();
        }
        [[nodiscard]] explicit operator bool()const noexcept
        {
            return isValid();
        }
        [[nodiscard]] std::shared_ptr<T> lock() const
        {
            return m_ptr.lock();
        }
    };

    template<>
    class Ref<void>
    {
        std::weak_ptr<void> m_ptr;
    public:
        Ref() = default;
        Ref(const std::shared_ptr<void>& sharedPtr) :
            m_ptr(sharedPtr)
        {}
        Ref(std::nullptr_t) :
            m_ptr(std::weak_ptr<void>())
        {}

        [[nodiscard]] void* get() const noexcept
        {
            auto  lock = m_ptr.lock();
            auto p = lock.get();
            return p;
        }

        [[nodiscard]] explicit operator bool()const noexcept
        {
            return !m_ptr.expired();
        }
        [[nodiscard]] std::shared_ptr<void> lock() const
        {
            return m_ptr.lock();
        }
    };
    template<class T, class U>
    Ref<T> RefCast(const Ref<U>& ref)
    {
        return Ref<T>(std::dynamic_pointer_cast<T>(ref.lock()));
    }

    template<class T, class U>
    Ref<T> StaticRefCast(const Ref<U>& ref)
    {
        return Ref<T>(std::static_pointer_cast<T>(std::static_pointer_cast<void>(ref.lock())));
    }
}