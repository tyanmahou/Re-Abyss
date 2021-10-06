#pragma once
namespace abyss
{
    // 描画順
    struct DrawOrder
    {
        // World
        struct World
        {
            static constexpr double MostBack = -99.0;
            static constexpr double Default = 1.0;
            static constexpr double Player = 10.0;
        };
    };
}