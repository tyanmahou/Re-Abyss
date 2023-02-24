#include <abyss/components/Adv/BossCommon/Builder.hpp>

#include <abyss/components/Adv/BossCommon/Command/ShowHpBar.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>

namespace abyss::Adv::BossCommon
{
    void Builder::ShowHpBar(AdvObj* pObj)
    {
        pObj->engine()->addCommand<BossCommon::ShowHpBar>();
    }
}
