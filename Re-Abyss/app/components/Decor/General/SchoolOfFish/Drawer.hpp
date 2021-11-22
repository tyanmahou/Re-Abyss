#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Decor/base/IDraw.hpp>
#include <abyss/views/Shader/SchoolOfFish/SchoolOfFishShader.hpp>
#include <abyss/entities/Decor/General/SchoolOfFishEntity.hpp>

namespace abyss::Decor::General::SchoolOfFish
{
    /// <summary>
    /// 描画
    /// </summary>
    class Drawer :
        public IComponent,
        public IDraw
    {
    public:
        Drawer(DecorObj* pObj, const SchoolOfFishEntity& entity);

        void onStart() override;

        void onDraw() const override;
    private:
        DecorObj* m_pObj;
        SchoolOfFishShader m_shader;
        SchoolOfFishEntity m_entity;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Decor::General::SchoolOfFish::Drawer>
    {
        using Base = Decor::IDraw;
    };
}
