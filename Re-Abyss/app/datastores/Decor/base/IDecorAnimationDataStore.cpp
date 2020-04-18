#include "IDecorAnimationDataStore.hpp"

namespace abyss
{
    s3d::HashTable<s3d::uint32, s3d::Array<DecorAnimationEntity>> abyss::IDecorAnimationDataStore::selectWithKey() const
    {
        s3d::HashTable<s3d::uint32, s3d::Array<DecorAnimationEntity>> ret;
        for (auto&& entity : this->select()) {
            ret[entity.fromGId].push_back(entity);
        }
        return ret;
    }

}
