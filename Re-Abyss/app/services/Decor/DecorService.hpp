#pragma once
#include <memory>
#include <abyss/services/Decor/base/IDecorService.hpp>

#include <Emaject.hpp>

namespace abyss::decor
{
    class IDecorDataStore;
    class IAnimationDataStore;
    class IGraphicsDataStore;

    class DecorService : public IDecorService
    {
        s3d::Array<std::shared_ptr<DecorEntity>> m_front;
        s3d::Array<std::shared_ptr<DecorEntity>> m_back;
        s3d::Array<std::shared_ptr<DecorEntity>> m_custom;

        DecorGraphics m_graphics;
        DecorAnimations m_animation;
    public:
        INJECT_CTOR(DecorService(
            std::shared_ptr<IDecorDataStore> decor,
            std::shared_ptr<IGimmickDataStore> gimmick,
            std::shared_ptr<IMapDataStore> map,
            std::shared_ptr<IGraphicsDataStore> graphics,
            std::shared_ptr<IAnimationDataStore> animation
        ));
        const s3d::Array<std::shared_ptr<DecorEntity>>& getFront() const override
        {
            return m_front;
        }
        const s3d::Array<std::shared_ptr<DecorEntity>>& getBack() const override
        {
            return m_back;
        }
        const s3d::Array<std::shared_ptr<DecorEntity>>& getCustom() const override
        {
            return m_custom;
        }
        const DecorGraphics& getGraphics() const override
        {
            return m_graphics;
        }
        const DecorAnimations& getAnimations() const override
        {
            return m_animation;
        }
    };

    struct DecorServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}