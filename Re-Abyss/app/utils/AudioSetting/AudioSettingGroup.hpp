#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/HashTable.hpp>

#include <abyss/utils/AudioSetting/AudioSetting.hpp>

namespace abyss
{
    class AudioSettingGroup
    {
        using BaseType = s3d::HashTable<s3d::String, AudioSetting>;
    public:
        using iterator = BaseType::iterator;
        using const_iterator = BaseType::const_iterator;
    public:
        AudioSettingGroup() = default;
        AudioSettingGroup(const s3d::FilePath& path);
        AudioSetting operator()(const s3d::String& key) const;

        explicit operator bool()const;

        bool isContain(const s3d::String& key) const;

        iterator begin() const;
        iterator end() const;

        const_iterator cbegin() const;
        const_iterator cend() const;

        std::size_t size() const;

    private:
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    };
}