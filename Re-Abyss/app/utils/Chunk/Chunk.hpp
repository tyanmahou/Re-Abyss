#pragma once
#include <Siv3D/HashTable.hpp>

namespace abyss
{
    template<class Type>
    class Chunk
    {
    public:
        Type& operator[](s3d::int32 index)
        {
            if (m_indexRange.first > index) {
                m_indexRange.first = index;
            }
            if(m_indexRange.second < index + 1) {
                m_indexRange.second = index + 1;
            }
            return m_data[index];
        }
        const Type& operator[](s3d::int32 index) const
        {
            return value(index);
        }
        const Type& value(s3d::int32 index) const
        {
            return valueOr(index, notfound);
        }
        const Type& valueOr(s3d::int32 index, const Type& value) const
        {
            if (!m_data.contains(index)) {
                return value;
            }
            return m_data.at(index);
        }
        s3d::int32 indexBegin() const
        {
            return m_indexRange.first;
        }
        s3d::int32 indexEnd() const
        {
            return m_indexRange.second;
        }
        s3d::int32 indexSize() const
        {
            return m_indexRange.second - m_indexRange.first;
        }
        const std::pair<s3d::int32, s3d::int32>& indexRange() const
        {
            return m_indexRange;
        }

        auto begin() const
        {
            return m_data.begin();
        }
        auto end() const
        {
            return m_data.end();
        }
        bool isEmpty() const
        {
            return m_data.empty();
        }
    private:
        std::pair<s3d::int32, s3d::int32> m_indexRange{0, 0};
        s3d::HashTable<s3d::int32, Type> m_data;
        inline static const Type notfound{};
    };

    template<class Type>
    using ChunkGrid = Chunk<Chunk<Type>>;
}