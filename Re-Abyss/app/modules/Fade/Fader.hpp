#pragma once

namespace abyss::Fade
{
    class SceneFader;

    /// <summary>
    /// フェーダー
    /// SceneFaderのプロキシクラス
    /// </summary>
    class Fader
    {
    public:
        Fader(SceneFader* fader);
    private:
        SceneFader* m_fader;
    };
}
