#pragma once
#include <Siv3D/Grid.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Decor::Map
{
    class TileMapModel
    {
    public:
        TileMapModel& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        const s3d::Vec2& getPos() const
        {
            return m_pos;
        }
        TileMapModel& setFilePath(const s3d::String& path)
        {
            m_filePath = path;
            return *this;
        }
        const s3d::String& getFilePath() const
        {
            return m_filePath;
        }
        TileMapModel& setTileSize(const s3d::Vec2& size)
        {
            m_tileSize = size;
            return *this;
        }
        const s3d::Vec2& getTileSize() const
        {
            return m_tileSize;
        }
        TileMapModel& setFirstGId(s3d::uint32 firstGId)
        {
            m_firstGId = firstGId;
            return *this;
        }
        s3d::uint32 getFirstGId() const
        {
            return m_firstGId;
        }
        void resize(size_t x, size_t y)
        {
            m_gIds.resize(x, y);
        }
        s3d::Size size() const
        {
            return m_gIds.size();
        }
        bool isEmpty() const
        {
            return m_gIds.isEmpty();
        }

        decltype(auto) operator[](size_t y)
        {
            return m_gIds[y];
        }

        decltype(auto) operator[](size_t y) const
        {
            return m_gIds[y];
        }

        const s3d::Grid<s3d::uint32>& gIds()const
        {
            return m_gIds;
        }
    private:
        s3d::Vec2 m_pos;
        s3d::String m_filePath;
        s3d::Vec2 m_tileSize;
        s3d::uint32 m_firstGId;
        s3d::Grid<s3d::uint32> m_gIds;
    };
}