#pragma once
#include <memory>
#include <abyss/controllers/UI/base/IUserInterface.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Event::Talk
{
    class SerifModel;
    class FaceManager;
}
namespace abyss::ui
{
    class MessageVM;
    class MessageBoxVM;
    class CursorVM;

    /// <summary>
    /// セリフ
    /// </summary>
    class Serif : public IUserInterface
    {
        Ref<Event::Talk::SerifModel> m_serif;

        std::unique_ptr<MessageVM> m_messageView;
        std::unique_ptr<MessageBoxVM> m_boxView;
        std::unique_ptr<CursorVM> m_cursorView;

    public:
        Serif(const Ref<Event::Talk::SerifModel>& serif);

        void update(double dt) override;
        void draw() const override;
    };
}