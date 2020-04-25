#pragma once
#include <abyss/models/Event/Talk/SerifModel.hpp>

namespace abyss::Event::Talk
{
    class MessageVM;
    class MessageBoxVM;
    class CursorVM;

    class Serif
    {
        SerifModel m_serif;
        std::shared_ptr<MessageVM> m_messageView;
        std::shared_ptr<MessageBoxVM> m_boxView;
        std::shared_ptr<CursorVM> m_cursorView;
    public:
        Serif();
        ~Serif();
        void setModel(SerifModel&& model);
        bool update();
        void draw()const;
    };
}