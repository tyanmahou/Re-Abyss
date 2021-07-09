#pragma once
#include <memory>
#include <functional>
#include <Siv3D/Rectangle.hpp>
#include <abyss/types/ColDirection.hpp>
#include "ITerrainExtData.hpp"
#include "Tag.hpp"

namespace abyss::Physics
{
    struct TerrainData
    {
        s3d::RectF region;
        ColDirection col;

        TagType tag;
        std::shared_ptr<ITerrainExtData> extData;

        template<TaggedOf<Tag::PhysicsTagKind> T, TerrainExtended D>
        bool isThen(std::function<bool(D&)> callback) const
        {
            if (tag.is<T>()) {
                if (auto d = std::dynamic_pointer_cast<TerrainExtended>(extData)) {
                    return callback(*d);
                }
            }
            return false;
        }
    };
}