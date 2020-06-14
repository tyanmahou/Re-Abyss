#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <abyss/utils/AudioSetting/AudioSetting.hpp>
namespace abyss
{
    class AudioSettingGroup
    {
    public:
        AudioSettingGroup() = default;
        AudioSettingGroup(const s3d::FilePath& path);
        AudioSetting operator()(const s3d::String& key) const;

        explicit operator bool()const;

        bool isContain(const s3d::String& key) const;
    private:
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    };
}