#include "TmxMapParser.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    MapType TmxMapParser::getFieldType(s3dTiled::GId gId)
    {
        if (gId <= 0) {
            return MapType::None;
        }
        if (m_fieldTypeMap.find(gId) != m_fieldTypeMap.end()) {
            return m_fieldTypeMap[gId];
        }
        bool isLadder = m_tiledMap.getTileProperty(gId, U"ladder").has_value();
        if (isLadder) {
            return m_fieldTypeMap[gId] = MapType::Ladder;
        }
        bool isPenetrate = m_tiledMap.getTileProperty(gId, U"penetrate").has_value();
        if (isPenetrate) {
            return m_fieldTypeMap[gId] = MapType::Penetrate;
        }
        return m_fieldTypeMap[gId] = MapType::Floor;
    }
    MapType TmxMapParser::getFieldType(s3d::uint32 x, s3d::uint32 y)

    {
        if (x < 0 || x >= m_grid.width()) {
            return MapType::None;
        }
        if (y < 0 || y >= m_grid.height()) {
            return MapType::None;
        }
        return getFieldType(m_grid[y][x]);
    };
    ColDirection TmxMapParser::calcColDirectrion(s3d::uint32 x, s3d::uint32 y)
    {
        ColDirection col = ColDirection::None;
        if (getFieldType(x, y - 1) != MapType::Floor) {
            col = col | ColDirection::Up;
        }

        if (getFieldType(x, y + 1) != MapType::Floor) {
            col = col | ColDirection::Down;
        }
        if (getFieldType(x - 1, y) != MapType::Floor) {
            col = col | ColDirection::Left;
        }
        if (getFieldType(x + 1, y) != MapType::Floor) {
            col = col | ColDirection::Right;
        }
        return col;
    }
    ColDirection TmxMapParser::calcAroundFloor(s3d::uint32 x, s3d::uint32 y)
    {
        ColDirection col = ColDirection::None;
        if (getFieldType(x, y - 1) == MapType::Floor) {
            col = col | ColDirection::Up;
        }

        if (getFieldType(x, y + 1) == MapType::Floor) {
            col = col | ColDirection::Down;
        }
        if (getFieldType(x - 1, y) == MapType::Floor) {
            col = col | ColDirection::Left;
        }
        if (getFieldType(x + 1, y) == MapType::Floor) {
            col = col | ColDirection::Right;
        }
        return col;
    }
    s3d::Optional<MapEntity> TmxMapParser::tryToMapInfoModel(s3d::uint32 x, s3d::uint32 y)
    {
        GId gId = m_grid[y][x];
        if (gId <= 0) {
            return s3d::none;
        }
        MapEntity ret;
        ret.type = this->getFieldType(gId);
        auto size = m_tiledMap.getTileSize();
        ret.pos = Vec2{ size.x * x, size.y * y } +static_cast<Vec2>(size) / 2;
        ret.size = m_tiledMap.getTile(gId).size;
        ret.aroundFloor = calcAroundFloor(x, y);
        switch (ret.type) {
        case MapType::Floor:
            ret.col = calcColDirectrion(x, y);
            if (!m_useAroundFilter || ret.col) {
                return ret;
            }
            break;
        case MapType::Ladder:
            ret.col = ColDirection::None;
            if (getFieldType(x, y - 1) == MapType::None) {
                ret.col = ColDirection::Up;
            }
            return ret;
        case MapType::Penetrate:
            ret.col = ColDirection::Up;
            ret.canDown = m_tiledMap.getTileProperty(gId, U"can_down").has_value();
            return ret;
        }
        return s3d::none;
    }
    TmxMapParser::TmxMapParser(const s3dTiled::TiledMap& tiledMap, const s3d::Grid<GId>& grid, bool useAroundFilter) :
        m_tiledMap(tiledMap),
        m_grid(grid),
        m_useAroundFilter(useAroundFilter)
    {}
    void TmxMapParser::forEach(std::function<void(const MapEntity&)> callback)
    {
        for (uint32 y = 0; y < m_grid.height(); ++y) {
            for (uint32 x = 0; x < m_grid.width(); ++x) {
                if (auto info = this->tryToMapInfoModel(x, y)) {
                    callback(*info);
                }
            }
        }
    };
}