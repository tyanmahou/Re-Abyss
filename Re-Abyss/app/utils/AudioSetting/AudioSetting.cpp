#include "AudioSetting.hpp"
#include <Siv3D.hpp>
#include <abyss/utils/Overloaded.hpp>

namespace abyss
{
    s3d::Audio AudioSetting::load() const
    {
        return this->apply(s3d::Wave(path));
    }
    s3d::Audio AudioSetting::apply(const s3d::Wave& wave) const
    {
        return std::visit(overloaded{
            [&](Loop l) {
                return s3d::Audio(wave, l);
            },
            [&](const s3d::Duration& begin) {
                return s3d::Audio(wave, begin);
            },
            [&](const s3d::Vector2D<s3d::Duration>& beginEnd) {
                return s3d::Audio(wave, beginEnd.x, beginEnd.y);
            }
        }, loop);
    }
}
