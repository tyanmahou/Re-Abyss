#pragma once
#include <Siv3D/Grid.hpp>
#include <Siv3D/String.hpp>

namespace abyss::decor::Map
{
    class TileMapModel
    {
    public:

        void setFilePath(const s3d::String& path)
        {
            m_filePath = path;
        }

        void resize(size_t x, size_t y)
        {
            m_gIds.resize(x, y);
        }
        bool isEmpty() const
        {
            return m_gIds.isEmpty();
        }

        decltype(auto) operator[](size_t y)
        {
            return m_gIds[y];
        }
    private:
        s3d::String m_filePath;
        s3d::Grid<s3d::uint32> m_gIds;
    };
}