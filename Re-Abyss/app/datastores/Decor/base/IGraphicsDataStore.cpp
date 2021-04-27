#include "IGraphicsDataStore.hpp"

namespace abyss::Decor
{
    s3d::HashTable<s3d::uint32, GraphicsEntity> IGraphicsDataStore::selectWithKey() const
    {
        s3d::HashTable<s3d::uint32, GraphicsEntity> ret;
        for (auto&& entity : this->select()) {
            ret[entity.gId] = std::move(entity);
        }

        return ret;
    }
}
