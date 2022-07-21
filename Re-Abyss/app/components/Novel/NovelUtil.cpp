#include <abyss/components/Novel/NovelUtil.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Event/Events.hpp>

namespace abyss::Novel
{
    bool NovelUtil::IsEventEnd(TalkObj* pTalk)
    {
        return pTalk->getModule<Events>()->isEmpty();
    }
}
