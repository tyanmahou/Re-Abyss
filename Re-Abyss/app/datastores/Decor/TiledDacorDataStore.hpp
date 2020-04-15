#pragma once
#include <S3DTiled.hpp>
#include <abyss/datastores/Decor/base/IDecorDataStore.hpp>

namespace abyss
{
    class TiledDecorDataStore : public IDecorDataStore
    {
        s3dTiled::TiledMap m_tiledMap;
    public:
        TiledDecorDataStore(const s3d::String& mapName);

        s3d::Array<DecorEntity> select(DecorGroup group)const override;
    };
}