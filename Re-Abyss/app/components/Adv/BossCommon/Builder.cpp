#include <abyss/components/Adv/BossCommon/Builder.hpp>

#include <abyss/components/Adv/BossCommon/Command/ShowHpBar.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Process.hpp>

namespace abyss::Adv::BossCommon
{
    void Builder::ShowHpBar(AdvObj* pObj)
    {
        pObj->process()->addCommand<BossCommon::ShowHpBar>();
    }
}
