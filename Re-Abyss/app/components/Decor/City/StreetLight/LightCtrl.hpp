#pragma once

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Decor/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Decor
{
    class DecorInfo;
}
namespace abyss::Decor::City::StreetLight
{
    class LightVM;

    class LightCtrl :
        public IComponent,
        public IDraw
    {
    public:
        LightCtrl(DecorObj* pObj);

        void setup(Executer executer) override;

        void onStart()override;
        void onDraw() const override;

    private:
        DecorObj* m_pObj;
        Ref<DecorInfo> m_info;

        std::unique_ptr<LightVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Decor::City::StreetLight::LightCtrl>
    {
        using Base = Decor::IDraw;
    };
}