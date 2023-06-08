#pragma once
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>
#include <abyss/values/Sound/SoundLabel.hpp>

namespace abyss::Actor::Gimmick
{
    struct BgmChangerEntity : GimmickEntity
    {
        Sound::SoundLabel bgm;
    };
}
