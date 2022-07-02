#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Decor/Map/TileMapData.hpp>
#include <abyss/views/Shader/TileMap/TileMapShader.hpp>

#include <Siv3D/Texture.hpp>

namespace abyss::Decor::Map
{
    class TileMapView
    {
    public:
        TileMapView(const TileMapData& tileMap);

        void draw(const Decors& decor, double time)const;
    private:
        TileMapData m_tileMap;
        s3d::Texture m_texture;
        TileMapShader m_shader;

        // 最適化用インデックス配列
        s3d::Array<s3d::Size> m_indexPoints;
    };
}
