#pragma once
#include <Siv3D/IAddon.hpp>
#include <abyss/values/Fps.hpp>

namespace abyss
{
    class FrameRateController : public IAddon
    {
    protected:
        void postPresent() override;
    private:
        s3d::Optional<Fps> m_value;
    };
}
