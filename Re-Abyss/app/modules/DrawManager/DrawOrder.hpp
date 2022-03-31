#pragma once

namespace abyss
{
    // 描画順
    struct DrawOrder
    {
        // DecorBack
        struct DecorBack
        {
            static constexpr double Default = 1.0;
            static constexpr double MostFront = 99998.0;
            static constexpr double UI = 99999.0;
        };
        // WorldBack
        struct WorldBack
        {
            static constexpr double Default = 1.0;
            static constexpr double UI = 99999.0;
        };
        // World
        struct World
        {
            static constexpr double MostBack = -99.0;
            static constexpr double Default = 1.0;
            static constexpr double Player = 10.0;
        };

        // UI
        struct UI
        {
            static constexpr double MostBack = -9999.0;
            static constexpr double Flush = -1.0;
            static constexpr double Default = 1.0;
            static constexpr double Dialog = 1000.0;
            static constexpr double Footer = 99998.0;
            static constexpr double Fade = 99999.0;
        };
    };
}