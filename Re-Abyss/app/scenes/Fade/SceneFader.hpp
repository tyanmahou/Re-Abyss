#pragma once
#include <memory>

namespace abyss::Fade
{
    class SceneFader
    {
    public:
        SceneFader();
        ~SceneFader();

        void update();
        void draw() const;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}
