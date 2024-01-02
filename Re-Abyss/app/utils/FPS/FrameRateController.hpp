#pragma once
#include <Siv3D/IAddon.hpp>
#include <abyss/values/Fps.hpp>

namespace abyss
{
    class FrameRateController : IAddon
    {
    private:
        s3d::Optional<Fps> m_value;
    };
}
