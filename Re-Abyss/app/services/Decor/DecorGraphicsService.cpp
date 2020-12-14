#include "DecorGraphicsService.hpp"

#include <abyss/datastores/Decor/base/IDecorGraphicsDataStore.hpp>
#include <abyss/datastores/Decor/base/IDecorAnimationDataStore.hpp>

namespace abyss
{
    DecorGraphicsService::DecorGraphicsService(
        std::shared_ptr<IDecorGraphicsDataStore> decorGraphics, 
        std::shared_ptr<IDecorAnimationDataStore> decorAnimation
    ):
        m_graphics(decorGraphics->selectWithKey()),
        m_animations(decorAnimation->selectWithKey())
    {}
    void DecorGraphicsServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IDecorGraphicsService>()
            .to<DecorGraphicsService>()
            .asCache();
    }
}
