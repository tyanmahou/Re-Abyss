#pragma once

namespace abyss::Fade
{
    class Fader;

    class FadeProxy
    {
    public:
        FadeProxy(Fader* fader);
    private:
        Fader* m_fader;
    };
}
