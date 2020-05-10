#pragma once
#include <Siv3D/Array.hpp>
namespace abyss
{
    template<class T>
    class LoopQueue
    {
    private:
        s3d::Array<T> m_queue;
        size_t m_current = 0;
    public:
        void add(const T& elm)
        {
            m_queue.push_back(elm);
        }
        void add(T&& elm)
        {
            m_queue.push_back(std::move(elm));
        }

        size_t size()const
        {
            return m_queue.size();
        }
        bool isEmpty() const
        {
            return size() == 0;
        }
        void clear()
        {
            m_current = 0;
            return m_queue.clear();
        }

        void reset()
        {
            m_current = 0;
        }

        void set(size_t index)
        {
            m_current = index % size();
        }
        void skip(size_t step)
        {
            m_current += step;
            m_current %= size();
        }
        const T& pop()
        {
            size_t current = m_current++;
            m_current %= size();
            return m_queue[current];
        }

    };
}