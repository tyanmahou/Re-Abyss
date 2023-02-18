#include <abyss/components/Novel/BossCommon/Builder.hpp>

#include <abyss/components/Novel/BossCommon/Command/ShowHpBar.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Novel/base/Engine.hpp>

namespace abyss::Novel::BossCommon
{
    void Builder::ShowHpBar(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<BossCommon::ShowHpBar>();
    }
}
