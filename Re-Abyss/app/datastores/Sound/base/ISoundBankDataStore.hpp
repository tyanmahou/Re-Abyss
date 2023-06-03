#pragma once
#include <abyss/utils/AudioSetting/AudioSetting.hpp>
#include <Siv3D/HashTable.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Sound
{
    class ISoundBankDataStore
    {
    public:
        virtual ~ISoundBankDataStore() = default;

        virtual s3d::HashTable<s3d::String, AudioSetting> select() const = 0;
    };
}
