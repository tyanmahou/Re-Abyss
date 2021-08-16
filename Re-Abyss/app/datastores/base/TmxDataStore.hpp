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
        TmxDataStore(const s3d::String& mapPath);
    };

    struct TiledMapInstaller final : emaject::IInstaller
    {
        TiledMapInstaller(const s3d::String& mapPath);
        void onBinding(emaject::Container* conatienr) const override;

    private:
        std::shared_ptr<s3dTiled::TiledMap> m_tmx;
    };

    template<class From, class To>
    struct TmxDataStoreInataller final : emaject::IInstaller
    {
        void onBinding(emaject::Container* conatienr) const override
        {
            conatienr->bind<From>()
                .to<To>()
                .asCache();
        }
    };
}