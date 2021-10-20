#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Novel
{
    class ColorTag :
        public ICommand
    {
    public:
        ColorTag(TalkObj* pTalk, const s3d::Optional<s3d::ColorF>& color);

        void onStart() override;
        Coro::Task<> onCommand() override;
    private:
        TalkObj* m_pTalk = nullptr;
        s3d::Optional<s3d::ColorF> m_color;
    };
}
