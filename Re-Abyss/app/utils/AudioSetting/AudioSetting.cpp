#include "AudioSetting.hpp"
#include <Siv3D.hpp>
#include <abyss/utils/Overloaded.hpp>

namespace abyss
{
    s3d::Audio AudioSetting::load() const
    {
        if (streaming) {
            return this->loadStreamimg();
        } else {
            return this->loadWave();
        }
    }

    s3d::Audio AudioSetting::loadWave() const
    {
        return this->apply(s3d::Wave(path));
    }

    s3d::Audio AudioSetting::loadStreamimg() const
    {
        return this->loadStreamimg(path);
    }
    s3d::Audio AudioSetting::loadStreamimg(s3d::FilePathView otherPath) const
    {
        return std::visit(overloaded{
            [&](Loop l) {
                return s3d::Audio(Audio::Stream, otherPath, l);
            },
            [&](const s3d::Duration& begin) {
                return s3d::Audio(Audio::Stream, otherPath, Arg::loopBegin = static_cast<uint64>(samplingRate * begin.count()));
            },
            [&](const s3d::Vector2D<s3d::Duration>& beginEnd) {
                return s3d::Audio(Audio::Stream, otherPath, static_cast<uint64>(samplingRate * beginEnd.x.count()));
            }
        }, loop);
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
