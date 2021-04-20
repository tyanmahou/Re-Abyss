#pragma once
#include <memory>
#include <abyss/services/Decor/base/IDecorService.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class ITileMapDataStore;
}
namespace abyss::decor
{
    class IDecorDataStore;
    class IAnimationDataStore;
    class IGraphicsDataStore;

    class DecorService : public IDecorService
    {
        s3d::Array<std::shared_ptr<DecorEntity>> m_front;
        s3d::Array<std::shared_ptr<DecorEntity>> m_back;
        s3d::Array<std::shared_ptr<DecorEntity>> m_middle;

        DecorGraphics m_graphics;
        DecorAnimations m_animation;

        s3d::HashTable<s3d::String, Map::TileMapModel> m_tileMap;
    public:
        INJECT_CTOR(DecorService(
            std::shared_ptr<IDecorDataStore> decor,
            std::shared_ptr<ITileMapDataStore> map,
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
        const s3d::Array<std::shared_ptr<DecorEntity>>& getMiddle() const override
        {
            return m_middle;
        }
        s3d::Array<Map::TileMapModel> getTileMap(const s3d::RectF& screen) const override;

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