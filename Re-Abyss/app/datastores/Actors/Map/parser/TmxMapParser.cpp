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
    MapType TmxMapParser::getFieldType(s3d::int32 x, s3d::int32 y)

    {
        if (x < 0 || x >= m_grid.width()) {
            return MapType::None;
        }
        if (y < 0 || y >= m_grid.height()) {
            return MapType::None;
        }
        return getFieldType(m_grid[y][x]);
    };
    ColDirection TmxMapParser::calcColDirectrion(s3d::int32 x, s3d::int32 y)
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
    ColDirection TmxMapParser::calcAroundFloor(s3d::int32 x, s3d::int32 y)
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
    s3d::Optional<MapEntity> TmxMapParser::tryToMapInfoModel(s3d::int32 x, s3d::int32 y)
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
        ret.id = x + size.y * y;
        ret.gId = gId;
        switch (ret.type) {
        case MapType::Floor:
            ret.col = calcColDirectrion(x, y);
            return ret;
            //if (!m_useAroundFilter || ret.col) {
            //    return ret;
            //}
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
        m_useAroundFilter(useAroundFilter),
        m_entityGrid(grid.size())
    {}
    void TmxMapParser::forEach(std::function<void(const MapEntity&)> callback)
    {
        for (uint32 y = 0; y < m_grid.height(); ++y) {
            for (uint32 x = 0; x < m_grid.width(); ++x) {
                m_entityGrid[y][x] = this->tryToMapInfoModel(static_cast<s3d::int32>(x), static_cast<s3d::int32>(y));
            }
        }
        if (!m_useAroundFilter) {
            for (auto&& entity : m_entityGrid) {
                if (!entity) {
                    continue;
                }
                callback(*entity);
            }
            return;
        }

        // マージされたマップ
        s3d::Array<MergeParam> mergedMaps;
        Grid<s3d::int32> mergeIndex(m_entityGrid.size());
        for (auto&& index : mergeIndex) {
            index = -1;
        }

        auto equal = [](const MapEntity& a, const MapEntity& b) {
            if (a.type != b.type) {
                return false;
            }
            if (a.type == MapType::Ladder && a.col != b.col) {
                return false;
            }
            if (a.type == MapType::Penetrate && a.canDown != b.canDown) {
                return false;
            }
            return true;
        };
        // 横にマージ
        for (int32 y = 0; y < m_entityGrid.height(); ++y) {
            for (int32 x = 0; x < m_entityGrid.width(); ++x) {
                const auto& entity = m_entityGrid[y][x];
                if (x == 0 && entity) {
                    // 最初
                    mergedMaps.push_back({ *entity, x, x });
                    auto size = static_cast<int32>(mergedMaps.size());
                    mergeIndex[y][x] =  size - 1;
                    continue;
                }
                const auto& prevEntity = m_entityGrid[y][x - 1];
                if (entity && prevEntity && equal(*entity, *prevEntity)) {
                    // マージできる
                    auto paramIndex = mergeIndex[y][x - 1];
                    auto& param = mergedMaps[paramIndex];
                    param.endX = x;
                    auto left = Min(param.entity.pos.x - param.entity.size.x / 2.0, entity->pos.x - entity->size.x / 2.0);
                    auto right = Max(param.entity.pos.x + param.entity.size.x / 2.0, entity->pos.x + entity->size.x / 2.0);
                    param.entity.pos.x = (left + right) / 2.0;
                    param.entity.size.x = right - left;
                    param.entity.col |= entity->col;
                    mergeIndex[y][x] = paramIndex;
                } else {
                    mergedMaps.push_back({ *entity, x, x });
                    auto size = static_cast<int32>(mergedMaps.size());
                    mergeIndex[y][x] = size - 1;
                }

            }
        }
        // 縦にマージ
        //s3d::Array<MergeParam> mergedMaps2;
        //Grid<s3d::int32> mergeIndex2(m_entityGrid.size());
        //for (auto&& index : mergeIndex2) {
        //    index = -1;
        //}
        //std::unordered_map<s3d::int32, s3d::int32> registedIndex;

        //for (int32 y = 0; y < m_entityGrid.height(); ++y) {
        //    for (int32 x = 0; x < m_entityGrid.width(); ++x) {
        //        const auto& paramIndex = mergeIndex[y][x];
        //        if (y == 0 && paramIndex != -1) {
        //            // 最初
        //            if (!registedIndex.contains(paramIndex)) {
        //                mergedMaps2.push_back(mergedMaps[paramIndex]);
        //                mergeIndex2[y][x] = mergedMaps2.size() - 1;
        //                registedIndex[paramIndex] = mergedMaps2.size() - 1;
        //            } else {
        //                mergeIndex2[y][x] = registedIndex[paramIndex];
        //            }
        //            continue;
        //        }

        //        const auto& prevIndex = mergeIndex2[y - 1][x];
        //        if (paramIndex != -1 && prevIndex != -1 
        //            && equal(mergedMaps[paramIndex].entity, mergedMaps2[prevIndex].entity)
        //            && mergedMaps[paramIndex].beginX == mergedMaps2[prevIndex].beginX
        //            && mergedMaps[paramIndex].endX == mergedMaps2[prevIndex].endX
        //            ) {
        //            // マージできる
        //            if (!registedIndex.contains(paramIndex)) {
        //                auto& param = mergedMaps2[prevIndex];
        //                param.entity.pos.y = (param.entity.pos.y + mergedMaps[paramIndex].entity.pos.y) / 2.0;
        //                param.entity.size.y += mergedMaps[paramIndex].entity.size.y;
        //                param.entity.col |= mergedMaps[paramIndex].entity.col;
        //                mergeIndex2[y][x] = prevIndex;
        //                registedIndex[paramIndex] = prevIndex;
        //            } else {
        //                mergeIndex2[y][x] = registedIndex[paramIndex];
        //            }
        //        } else {
        //            if (!registedIndex.contains(paramIndex)) {
        //                mergedMaps2.push_back(mergedMaps[paramIndex]);
        //                mergeIndex2[y][x] = mergedMaps2.size() - 1;
        //                registedIndex[paramIndex] = mergedMaps2.size() - 1;
        //            } else {
        //                mergeIndex2[y][x] = registedIndex[paramIndex];
        //            }
        //            continue;
        //        }

        //    }
        //}

        for (auto&& [entity,b,e] : mergedMaps) {
            callback(entity);
        }
    };
}