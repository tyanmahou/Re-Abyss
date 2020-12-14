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

    template<class From, class To>
    struct TmxDataStoreInataller final : emaject::IInstaller
    {
        TmxDataStoreInataller(const s3d::String& mapName):
            m_mapName(mapName)
        {}
        void onBinding(emaject::Container* conatienr) const override
        {
            conatienr->bind<From>()
                .fromInstance([name = m_mapName]() {
                return std::make_shared<To>(name);
            })
            .asCache();
        }
    private:
        s3d::String m_mapName;
    };
}