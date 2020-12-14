#pragma once
#include <S3DTiled.hpp>
#include <Emaject.hpp>
namespace abyss
{
    class TmxDataStore
    {
    protected:
        s3dTiled::TiledMap m_tmx;
    public:
        INJECT_CTOR(TmxDataStore(const std::shared_ptr<s3dTiled::TiledMap>& mapData));

        TmxDataStore(const s3d::String& mapName);
    };

    struct TiledMapInstaller final : emaject::IInstaller
    {
        TiledMapInstaller(const s3d::String& mapName):
            m_tmx(std::make_shared<s3dTiled::TiledMap>(mapName + U".tmx"))
        {}
        void onBinding(emaject::Container* conatienr) const override
        {
            conatienr->bind<s3dTiled::TiledMap>()
                .fromInstance([tmx = m_tmx]() {
                    return tmx;
                })
               .asCache();
        }

    private:
        std::shared_ptr<s3dTiled::TiledMap> m_tmx;
    };

    template<class From, class To>
    struct TmxDataStoreInataller final : emaject::IInstaller
    {
        void onBinding(emaject::Container* conatienr) const override
        {
            conatienr->bind<From>
                .to<To>
                .asCache();
        }
    };
}