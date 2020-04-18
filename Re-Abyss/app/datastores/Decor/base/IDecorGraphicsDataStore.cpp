#include "IDecorGraphicsDataStore.hpp"

namespace abyss
{
    s3d::HashTable<s3d::uint32, DecorGraphicsEntity> abyss::IDecorGraphicsDataStore::selectWithKey() const
    {
        s3d::HashTable<s3d::uint32, DecorGraphicsEntity> ret;
        for (auto&& entity : this->select()) {
            ret[entity.gId] = std::move(entity);
        }

        return ret;
    }

}
