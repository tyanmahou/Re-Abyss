#include <abyss/components/Adv/CommonUtil.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Event/Events.hpp>

namespace abyss::Adv
{
    bool CommonUtil::IsEventEnd(AdvObj* pTalk)
    {
        return pTalk->getModule<Events>()->isEmpty();
    }
}
