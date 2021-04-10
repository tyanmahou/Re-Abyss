#include "DecorService.hpp"

#include <abyss/datastores/Decor/base/IDecorDataStore.hpp>
#include <abyss/datastores/Actors/Map/base/IMapDataStore.hpp>

namespace abyss::decor
{
    DecorService::DecorService(
        std::shared_ptr<IDecorDataStore>decor, 
        std::shared_ptr<IGimmickDataStore>gimmick,
        std::shared_ptr<IMapDataStore>map
    )
    {
        m_front = decor->select(DecorGroup::Front);
        m_back = decor->select(DecorGroup::Back);
    }
}
