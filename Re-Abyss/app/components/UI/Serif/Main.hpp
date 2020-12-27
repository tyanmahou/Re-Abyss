#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Event::Talk
{
    class SerifCtrl;
    class FaceTable;
}

namespace abyss::ui::Serif
{
    class MessageVM;
    class MessageBoxVM;
    class CursorVM;

    class Main : 
        public IComponent,
        public IUpdate,
        public IDraw
    {
        
    public:
        Main(
            IUserInterface* pUi, 
            const Ref<Event::Talk::SerifCtrl>& serif,
            const Ref<Event::Talk::FaceTable>& faceTable
        );

        void onStart() override;

        void onUpdate() override;

        void onDraw() const override;
    private:
        IUserInterface* m_pUi;

        Ref<Event::Talk::SerifCtrl> m_serif;
        Ref<Event::Talk::FaceTable> m_faceTable;

        std::unique_ptr<MessageVM> m_messageView;
        std::unique_ptr<MessageBoxVM> m_boxView;
        std::unique_ptr<CursorVM> m_cursorView;

    };
}

namespace abyss
{
    template<>
    struct ComponentTree<ui::Serif::Main>
    {
        using Base = MultiComponents<ui::IUpdate, ui::IDraw>;
    };
}