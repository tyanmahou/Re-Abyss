#pragma once
#include <memory>

namespace abyss::Fade
{
    class ISceneFader
    {
    public:
        virtual ~ISceneFader() = default;
        virtual void onFade(double t) const= 0;
    };
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
