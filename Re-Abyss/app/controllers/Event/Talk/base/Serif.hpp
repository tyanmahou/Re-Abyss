#pragma once
#include <abyss/models/Event/Talk/SerifModel.hpp>

namespace abyss::Event::Talk
{
    class MessageVM;
    class MessageBoxVM;
    class CursorVM;
    class FaceManager;

    class Serif
    {
        SerifModel m_serif;
        std::shared_ptr<MessageVM> m_messageView;
        std::shared_ptr<MessageBoxVM> m_boxView;
        std::shared_ptr<CursorVM> m_cursorView;

        std::shared_ptr<FaceManager> m_faceManager;
    public:
        Serif();
        ~Serif();
        void setModel(SerifModel&& model);
        void setFaceManager(const std::shared_ptr<FaceManager>& faceManager);
        bool update();
        void draw()const;
    };
}