#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Adv
{
    class Engine;

    class AdvObj : public GameObject
    {
    public:
        AdvObj();

        bool update();

        const Ref<Engine>& engine() const
        {
            return m_engine;
        }
    private:
        Ref<Engine> m_engine;
    };
}
