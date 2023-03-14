#pragma once

namespace abyss::UI::Home::Top
{
    /// <summary>
    /// モード
    /// </summary>
    enum class Mode
    {
        Seek,
        Guild,
        Maint,
        Memory,
        Collect,
        Option,

        Max,
    };

    inline Mode& operator++(Mode& mode)
    {
        mode = static_cast<Mode>(static_cast<size_t>(mode) + 1);
        return mode;
    }
}
