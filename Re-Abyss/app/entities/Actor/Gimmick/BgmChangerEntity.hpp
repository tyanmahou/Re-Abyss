#pragma once
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>
#include <abyss/modules/Sound/SoundBank/SoundLabel.hpp>

namespace abyss::Actor::Gimmick
{
    struct BgmChangerEntity : GimmickEntity
    {
        Sound::SoundLabel bgm;
    };
}
