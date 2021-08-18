#pragma once
#include <abyss/utils/Chunk/Chunk.hpp>
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
        const s3d::Size& startIndex() const
        {
            return m_startIndex;
        }
        const s3d::Size& endIndex() const
        {
            return m_endIndex;
        }
        s3d::Size size() const
        {
            return m_endIndex - m_startIndex;
        }
        void calcSize()
        {
            m_startIndex = m_endIndex = s3d::Size{ 0, 0 };
            for (auto&& [y, row] : m_gIds) {
                for (auto&& [x, id] : row) {
                    if (x < m_startIndex.x) {
                        m_startIndex.x = x;
                    } else if (x > m_endIndex.x) {
                        m_endIndex.x = x;
                    }
                    if (y < m_startIndex.y) {
                        m_startIndex.y = y;
                    } else if (y> m_endIndex.y) {
                        m_endIndex.y = y;
                    }
                }
            }
        }
        bool isEmpty() const
        {
            return m_gIds.isEmpty();
        }

        decltype(auto) operator[](s3d::int32 y)
        {
            return m_gIds[y];
        }

        decltype(auto) operator[](s3d::int32 y) const
        {
            return m_gIds[y];
        }

        const ChunkGrid<s3d::uint32>& gIds()const
        {
            return m_gIds;
        }
    private:
        s3d::Vec2 m_pos;
        s3d::String m_filePath;
        s3d::Vec2 m_tileSize;
        s3d::uint32 m_firstGId;
        ChunkGrid<s3d::uint32> m_gIds;
        s3d::Size m_startIndex;
        s3d::Size m_endIndex;
    };
}