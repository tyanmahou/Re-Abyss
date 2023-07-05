#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>

namespace abyss::UI::BossArrival
{
    class Main :
        public IComponent,
        public IUpdate
    {
    public:
        Main(UIObj* pUi);

        void setup(Executer executer) override;

        void onStart() override;

        void onUpdate() override;
    private:
        UIObj* m_pUi;
    };
}
