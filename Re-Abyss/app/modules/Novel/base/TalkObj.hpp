#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Novel
{
    class Engine;

    class TalkObj : public GameObject
    {
    public:
        TalkObj();

        bool update();

        const Ref<Engine>& engine() const
        {
            return m_engine;
        }

        void stash()
        {
            m_isStashed = true;
        }
        void stashPop()
        {
            m_isStashed = false;
        }
        bool isStahed() const
        {
            return m_isStashed;
        }
    private:
        Ref<Engine> m_engine;
        bool m_isStashed = false;
    };
}
