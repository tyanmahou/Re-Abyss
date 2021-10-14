#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Novel
{
    class TalkHandler;

    class TalkObj : public GameObject
    {
    public:
        TalkObj();

        bool update();
    private:
        Ref<TalkHandler> m_talk;
    };
}