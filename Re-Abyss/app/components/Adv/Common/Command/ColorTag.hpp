#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Adv
{
    class ColorTag :
        public ICommand
    {
    public:
        ColorTag(AdvObj* pTalk, const s3d::Optional<s3d::ColorF>& color);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pTalk = nullptr;
        s3d::Optional<s3d::ColorF> m_color;
    };
}
