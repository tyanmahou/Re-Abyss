#pragma once
#include <abyss/modules/Decor/Map/Tile.hpp>
#include <abyss/utils/Chunk/Chunk.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Decor::Map
{
    class TileMapData
    {
    public:
        TileMapData& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        const s3d::Vec2& getPos() const
        {
            return m_pos;
        }
        TileMapData& setFilePath(const s3d::String& path)
        {
            m_filePath = path;
            return *this;
        }
        const s3d::String& getFilePath() const
        {
            return m_filePath;
        }
        TileMapData& setTileSize(const s3d::Vec2& size)
        {
            m_tileSize = size;
            return *this;
        }
        const s3d::Vec2& getTileSize() const
        {
            return m_tileSize;
        }
        TileMapData& setFirstGId(s3d::uint32 firstGId)
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
            bool isFirst = true;

            for (auto&& [y, row] : m_tiles) {
                for (auto&& [x, _] : row) {
                    if (isFirst || x < m_startIndex.x) {
                        m_startIndex.x = x;
                    }
                    if (isFirst || x + 1 > m_endIndex.x) {
                        m_endIndex.x = x + 1;
                    }
                    if (isFirst || y < m_startIndex.y) {
                        m_startIndex.y = y;
                    }
                    if (isFirst || y + 1 > m_endIndex.y) {
                        m_endIndex.y = y + 1;
                    }
                    isFirst = false;
                }
            }
        }
        bool isEmpty() const
        {
            return m_tiles.isEmpty();
        }

        decltype(auto) operator[](s3d::int32 y)
        {
            return m_tiles[y];
        }

        decltype(auto) operator[](s3d::int32 y) const
        {
            return m_tiles[y];
        }

        const ChunkGrid<Tile>& tiles()const
        {
            return m_tiles;
        }
    private:
        s3d::Vec2 m_pos;
        s3d::String m_filePath;
        s3d::Vec2 m_tileSize;
        s3d::uint32 m_firstGId;
        ChunkGrid<Tile> m_tiles;
        s3d::Size m_startIndex;
        s3d::Size m_endIndex;
    };
}
