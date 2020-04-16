#pragma once
#include <S3DTiled.hpp>
namespace abyss
{
    class TmxDataStore
    {
    protected:
        s3dTiled::TiledMap m_tmx;
    public:
        TmxDataStore(const s3d::String& mapName);
    };
}