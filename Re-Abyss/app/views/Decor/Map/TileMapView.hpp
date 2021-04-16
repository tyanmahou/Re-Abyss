#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Decor/Map/TileMapModel.hpp>
#include <abyss/views/Decor/Map/TileMapShader.hpp>

#include <Siv3D/Texture.hpp>

namespace abyss::decor::Map
{
    class TileMapView
    {
    public:
        TileMapView(const TileMapModel& tileMap);

        void draw(const Decor& decor, double time)const;
    private:
        TileMapModel m_tileMap; 
        s3d::Texture m_texture;
        TileMapShader m_shader;
    };
}