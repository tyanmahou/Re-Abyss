#pragma once
#include <memory>
#include <abyss/services/Decor/base/IDecorGraphicsService.hpp>
#include <abyss/commons/Fwd.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class DecorGraphicsService final: public IDecorGraphicsService
    {
    private:
        DecorGraphics m_graphics;
        DecorAnimations m_animations;
    public:
        INJECT_CTOR(DecorGraphicsService(
            std::shared_ptr<IDecorGraphicsDataStore> decorGraphics,
            std::shared_ptr<IDecorAnimationDataStore> decorAnimation
        ));
        const DecorGraphics& getGraphics() const override{ return m_graphics; }
        const DecorAnimations& getAnimations() const override{ return m_animations; }
    };

    struct DecorGraphicsServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}