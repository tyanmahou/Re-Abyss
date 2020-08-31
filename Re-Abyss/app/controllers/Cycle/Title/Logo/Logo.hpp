#pragma once
#include <memory>

namespace abyss::Cycle::Title::Logo
{
    class LogoModel;
    class LogoVM;

    class Logo
    {
        std::unique_ptr<LogoModel> m_model;
        std::unique_ptr<LogoVM> m_view;
    public:
        Logo();
        ~Logo();

        bool isEnd() const;

        void update();
        void draw()const;
    };
}