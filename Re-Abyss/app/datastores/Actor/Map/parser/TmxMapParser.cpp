#include "TmxMapParser.hpp"
#include <Siv3D.hpp>

namespace abyss::Actor::Map
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
        return getFieldType(m_chunk(y, x));
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
        GId gId = m_chunk(y, x);
        if (gId <= 0) {
            return s3d::none;
        }
        MapEntity ret;
        ret.type = this->getFieldType(gId);
        auto size = m_tiledMap.getTileSize();
        ret.pos = Vec2{ size.x * x, size.y * y } + static_cast<Vec2>(size) / 2;
        ret.size = size;
        ret.aroundFloor = calcAroundFloor(x, y);
        ret.id = x + static_cast<s3d::int32>(m_chunk.width()) * y;
        ret.gId = gId;
        switch (ret.type) {
        case MapType::Floor:
            ret.col = calcColDirectrion(x, y);
            return ret;
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
    TmxMapParser::TmxMapParser(const s3dTiled::TiledMap& tiledMap, const s3dTiled::Chunk<GId>& chunk, bool isMerge) :
        m_tiledMap(tiledMap),
        m_chunk(chunk),
        m_isMerge(isMerge)
    {}
    const ChunkGrid<s3d::Optional<MapEntity>>& TmxMapParser::selectGrid()
    {
        auto&& [xBegin, yBegin] = m_chunk.startIndex();
        auto&& [xEnd, yEnd] = m_chunk.endIndex();
        for (int32 y = yBegin; y < yEnd; ++y) {
            for (int32 x = xBegin; x < xEnd; ++x) {
                if (auto&& entity = this->tryToMapInfoModel(static_cast<s3d::int32>(x), static_cast<s3d::int32>(y)); entity && entity->type != MapType::None) {
                    m_entityGrid[y][x] = std::move(entity);
                }
            }
        }
        return m_entityGrid;
    }
    void TmxMapParser::forEach(std::function<void(const MapEntity&)> callback)
    {
        this->selectGrid();

        if (!m_isMerge) {
            for (auto&& [y, row] : m_entityGrid) {
                for (auto&& [x, entity] : row) {
                    if (!entity) {
                        continue;
                    }
                    callback(*entity);
                }
            }
            return;
        }
        // マージされたマップ
        s3d::Array<MergeParam> mergedMapsX;
        // マージしていいか
        auto equal = [](const MapEntity& a, const MapEntity& b, bool horizontal = false) {
            if (a.type != b.type) {
                return false;
            }
            if (a.col != b.col) {
                return false;
            }
            if (horizontal) {
                if (a.type == MapType::Ladder) {
                    // 梯子は横にマージできない
                    return false;
                } else if (a.type == MapType::Penetrate && a.canDown != b.canDown) {
                    // すり抜け床は降りれるかどうかが違うならマージできない
                    return false;
                }
            } else {
                if (a.type == MapType::Ladder && a.col != b.col) {
                    // 梯子はコリジョンが違うならマージできない
                    return false;
                } else if (a.type == MapType::Penetrate) {
                    // すり抜け床は縦マージできない
                    return false;
                }
            }
            return true;
        };
        {
            ChunkGrid<s3d::int32> mergeIndexX;

            // 横にマージ
            auto mergeX = [](const MapEntity& a, const MapEntity& b) {
                auto ret = a;
                auto left = Min(a.pos.x - a.size.x / 2.0, b.pos.x - b.size.x / 2.0);
                auto right = Max(a.pos.x + a.size.x / 2.0, b.pos.x + b.size.x / 2.0);
                ret.pos.x = (left + right) / 2.0;
                ret.size.x = right - left;
                ret.col |= b.col;
                return ret;
            };

            for (int32 y = m_entityGrid.indexBegin(); y < m_entityGrid.indexEnd(); ++y) {
                const auto& row = m_entityGrid[y];
                for (int32 x = row.indexBegin(); x < row.indexEnd(); ++x) {
                    const auto& entity = row[x];
                    if (!entity) {
                        continue;
                    }
                    {
                        const auto& prevEntity = row[x - 1];
                        if (prevEntity && equal(*entity, *prevEntity, true)) {
                            // マージできる
                            auto paramIndex = mergeIndexX[y][x - 1];
                            auto& param = mergedMapsX[paramIndex];
                            param.endX = x;
                            param.entity = mergeX(param.entity, *entity);
                            mergeIndexX[y][x] = paramIndex;
                            continue;
                        }
                    }
                    mergedMapsX.push_back({ *entity, x, x, y, y});
                    auto size = static_cast<int32>(mergedMapsX.size());
                    mergeIndexX[y][x] = size - 1;
                }
            }
        }
        // 縦にマージ
        s3d::Array<MergeParam> mergedMapsY;
        {
            s3d::Array<s3d::int32> mergeIndexY(mergedMapsX.size(), -1);

            auto mergeY = [](const MapEntity& a, const MapEntity& b) {
                auto ret = a;
                auto up = Min(a.pos.y - a.size.y / 2.0, b.pos.y - b.size.y / 2.0);
                auto down = Max(a.pos.y + a.size.y / 2.0, b.pos.y + b.size.y / 2.0);
                ret.pos.y = (up + down) / 2.0;
                ret.size.y = down - up;
                ret.col |= b.col;
                return ret;
            };

            for (int32 index = 0; index < mergedMapsX.size(); ++index) {
                const auto& prev = mergedMapsX[index];
                if (mergeIndexY[index] == -1) {
                    mergedMapsY.push_back(prev);
                    auto size = static_cast<int32>(mergedMapsY.size());
                    mergeIndexY[index] = size - 1;
                }

                for (int32 index2 = index + 1; index2 < mergedMapsX.size(); ++index2) {
                    const auto& current = mergedMapsX[index2];
                    if (current.beginX == prev.beginX &&
                        current.endX == prev.endX &&
                        (Abs(current.beginY - prev.endY) <= 1 || Abs(current.endY - prev.beginY) <= 1) &&
                        equal(current.entity, prev.entity)
                        ) {
                        // マージ可能
                        auto mergeIndex = mergeIndexY[index];
                        auto& param = mergedMapsY[mergeIndex];
                        param.entity = mergeY(param.entity, current.entity);
                        mergeIndexY[index2] = mergeIndex;
                    }
                }
            }
        }
        for (auto&& map : mergedMapsY) {
            callback(map.entity);
        }
    };
}