#include "IAnimationDataStore.hpp"

namespace abyss::Decor
{
    s3d::HashTable<s3d::uint32, s3d::Array<AnimationEntity>> IAnimationDataStore::selectWithKey() const
    {
        s3d::HashTable<s3d::uint32, s3d::Array<AnimationEntity>> ret;
        for (auto&& entity : this->select()) {
            ret[entity.fromGId].push_back(entity);
        }
        return ret;
    }
}
