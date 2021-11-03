#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/modules/UI/base/Filter.hpp>

namespace abyss::UI
{
    class UIObj final : public GameObject
    {
    public:

        void update();
        void postUpdate();

        void draw() const;

        double deltaTime() const;

        bool isActive(const Filter& filter) const;

        void setFilter(const Filter& filter)
        {
            m_filter = filter;
        }
    private:
        Filter m_filter{ Filter::Game };
    };
}