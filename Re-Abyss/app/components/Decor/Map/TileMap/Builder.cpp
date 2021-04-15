#include "Builder.hpp"
#include <abyss/components/Decor/Commons/CustomDraw.hpp>

#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/models/Decor/Map/TileMapModel.hpp>

#include <abyss/modules/Decor/Decor.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace
{
    class Drawer;
}
namespace abyss::decor::Map::TileMap
{
    void Builder::Build(DecorObj* pObj, const TileMapModel& tileMap)
    {
        pObj->attach<CustomDraw>()->setDrawer<Drawer>(pObj, tileMap);
    }
}

namespace
{
    using namespace abyss;
    using namespace abyss::decor;
    using namespace abyss::decor::Map;

    struct TileMapShaderParam
    {
        Float2 textureSize;
        Float2 mapChipSize;
        Float2 mapChipGIdSize;
        Float2 tileSize;
    };
    class Drawer : public CustomDraw::IImpl
    {
    public:
        Drawer(DecorObj* pObj, const TileMapModel& tileMap) :
            m_pObj(pObj),
            m_tileMap(tileMap),
            m_texture(Image(tileMap.size()* tileMap.getTileSize().asPoint())),
            m_mapChip(Resource::Assets::Main()->loadTexture(tileMap.getFilePath(), Path::Root)),
            m_gId(tileMap.size(), Palette::White),
            m_shader(Resource::Assets::Main()->loadPs(U"tilemap.hlsl"))
        {}
        void onStart()
        {
            m_cb->textureSize = m_texture.size();
            m_cb->mapChipSize = m_mapChip.size();
            m_cb->mapChipGIdSize = m_mapChip.size() / m_tileMap.getTileSize();
            m_cb->tileSize = m_tileMap.getTileSize();
        }
        void onDraw() const
        {
            auto decor = m_pObj->getModule<Decor>();
            auto time = m_pObj->getModule<GlobalTime>()->time();

            Image image(m_tileMap.size());
            image.fill(ColorF(0, 0));
            const auto& grid = m_tileMap.gIds();
            auto firstGId = m_tileMap.getFirstGId();
            for (uint32 y = 0; y < grid.height(); ++y) {
                for (uint32 x = 0; x < grid.width(); ++x) {
                    auto gId = grid[y][x];
                    if (gId == 0) {
                        continue;
                    }
                    if (firstGId <= gId) {
                        image[y][x] = Color(decor->getAnimGId(gId, time) - firstGId, 0, 0);
                    }
                }
            }
            m_gId.fill(std::move(image));

            {
                auto scopedShader = s3d::ScopedCustomShader2D(m_shader);
                s3d::Graphics2D::SetTexture(1, m_mapChip);
                s3d::Graphics2D::SetTexture(2, m_gId);
                s3d::Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, m_cb);
                m_texture.draw(m_tileMap.getPos());
            }
        }
    private:
        DecorObj* m_pObj;
        TileMapModel m_tileMap;
        Texture m_texture;
        Texture m_mapChip;
        mutable DynamicTexture m_gId;
        PixelShader m_shader;
        ConstantBuffer<TileMapShaderParam> m_cb;
    };
}