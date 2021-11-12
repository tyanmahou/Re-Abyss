#include "Drawer.hpp"
#include <Siv3D.hpp>
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Decor::General::SchoolOfFish
{
    Drawer::Drawer(DecorObj* pObj):
        m_pObj(pObj)
    {}

    void Drawer::onStart()
    {

    }
    void Drawer::onDraw() const
    {
        struct CBuffer
        {
            float t;
        };
        static s3d::ConstantBuffer<CBuffer> cb;
        cb->t = static_cast<float>(m_pObj->getModule<GlobalTime>()->time());

        ScopedRenderStates2D blend(s3d::BlendState::Subtractive);
        VertexShader vs = Resource::Assets::Norelease()->load(U"school_of_fish.hlsl");
        PixelShader ps = Resource::Assets::Norelease()->load(U"school_of_fish.hlsl");
        auto tex = Resource::Assets::Main()->loadTexturePacker(U"effects/Misc/Fish/fish.json")(U"fish_1");
        ScopedCustomShader2D shader(vs, ps);
        s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Vertex, 1, cb);
        s3d::Graphics2D::SetPSTexture(0, tex);
        s3d::Graphics2D::DrawTriangles(64 * 8 * 2);
    }
}