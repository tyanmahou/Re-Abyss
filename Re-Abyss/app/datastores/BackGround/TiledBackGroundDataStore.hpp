#pragma once
#include <S3DTiled.hpp>
#include <abyss/datastores/BackGround/base/IBackGroundDataStore.hpp>

namespace abyss
{
    class TiledBackGroundDataStore : public IBackGroundDataStore
    {
        s3dTiled::TiledMap m_tiledMap;
    public:
        TiledBackGroundDataStore(const s3d::String& mapName);

        s3d::Array<BackGroundEntity> select()const override;
    };
}