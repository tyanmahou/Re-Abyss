#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Slime
{
    class Senser;

    class SenserCtrlModel : public IComponent
    {
        Ref<Senser> m_senser;
    public:
        void set(std::shared_ptr<Senser> senser);

        void destroy();
    };
}