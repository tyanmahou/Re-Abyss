#pragma once
#include<abyss/values/Sound/SoundLabel.hpp>

namespace abyss::Actor::Player
{
    class SeDef
    {
    public:
        inline static const Sound::SoundLabel DoorMove{U"Se/Actor/Player/DoorMove"};
        inline static const Sound::SoundLabel Damage{U"Se/Actor/Player/Damage"};
        inline static const Sound::SoundLabel Dead{U"Se/Actor/Player/Dead"};
        inline static const Sound::SoundLabel Swim{U"Se/Actor/Player/Swim"};

        inline static const Sound::SoundLabel ShotSmall{U"Se/Actor/Player/Shot/ShotSmall"};
        inline static const Sound::SoundLabel ShotMedium{U"Se/Actor/Player/Shot/ShotMedium"};
        inline static const Sound::SoundLabel ShotBig{U"Se/Actor/Player/Shot/ShotBig"};
    };
}
