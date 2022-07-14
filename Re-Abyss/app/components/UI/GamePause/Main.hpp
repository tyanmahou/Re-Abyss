#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>

namespace abyss::UI::GamePause
{
    class Main :
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        Main(UIObj* pUi);
        ~Main();

    public:
        void onStart() override;
        void onUpdate() override;
        void onDraw() const override;
    private:
        UIObj* m_pUi;
    };
}
