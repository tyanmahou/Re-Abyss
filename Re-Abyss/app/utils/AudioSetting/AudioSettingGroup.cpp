#include "AudioSettingGroup.hpp"
#include <Siv3D.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
#include <abyss/utils/AudioSetting/AudioSettingReader.hpp>

#define ABYSS_CUSTOM

#ifdef ABYSS_CUSTOM
#include <abyss/commons/Resource/Assets/Assets.hpp>
#endif

namespace abyss
{
    class AudioSettingGroup::Impl
    {
        HashTable<String, AudioSetting> m_audios;
    public:
        Impl(const s3d::FilePath& path)
        {
            this->load(path);
        }

        bool load(const s3d::FilePath& aase)
        {
            TOMLReader toml(aase);
            if (!toml) {
                return false;
            }
            if (auto&& extends = toml[U"@Extends"]; extends.isTableArray()) {
                for (auto&& setting : extends.tableArrayView()) {
                    auto extendPath = setting[U"path"].getOpt<String>();
                    if (!extendPath) {
                        continue;
                    }
                    auto path = FileUtil::ParentPath(aase) + *extendPath;
                    this->merge(path);
                }
            }
            for (auto&&[key, setting] : toml.tableView()) {
                if (key[0] == U'@') {
                    continue;
                }
                m_audios[key] = AudioSettingReader{}.load(aase, setting);
            }
            return true;
        }

        AudioSetting operator()(const s3d::String& key)
        {
            if (m_audios.find(key) != m_audios.end()) {
                return m_audios[key];
            }
            return AudioSetting();
        }
        bool isContain(const s3d::String& key) const
        {
            return m_audios.find(key) != m_audios.end();
        }

        void merge(const s3d::FilePath& ssae);
        void merge(const Impl& other)
        {
            for (auto&& [key, audio] : other.m_audios) {
                m_audios[key] = audio;
            }
        }

        auto begin()
        {
            return m_audios.begin();
        }
        auto end()
        {
            return m_audios.end();
        }
        auto cbegin() const
        {
            return m_audios.cbegin();
        }
        auto cend() const
        {
            return m_audios.cend();
        }
        auto size() const
        {
            return m_audios.size();
        }
    };
    AudioSettingGroup::AudioSettingGroup(const s3d::FilePath& path):
        m_pImpl(std::make_shared<Impl>(path))
    {}

    AudioSetting AudioSettingGroup::operator()(const s3d::String& key) const
    {
        if (!m_pImpl) {
            return AudioSetting();
        }
        return (*m_pImpl)(key);
    }
    AudioSettingGroup::operator bool() const
    {
        return m_pImpl != nullptr;
    }
    bool AudioSettingGroup::isContain(const s3d::String& key) const
    {
        return m_pImpl->isContain(key);
    }
    AudioSettingGroup::iterator AudioSettingGroup::begin() const
    {
        return m_pImpl->begin();
    }
    AudioSettingGroup::iterator AudioSettingGroup::end() const
    {
        return m_pImpl->end();
    }
    AudioSettingGroup::const_iterator AudioSettingGroup::cbegin() const
    {
        return m_pImpl->cbegin();
    }
    AudioSettingGroup::const_iterator AudioSettingGroup::cend() const
    {
        return m_pImpl->cend();
    }
    std::size_t AudioSettingGroup::size() const
    {
        return m_pImpl->size();
    }
    void AudioSettingGroup::Impl::merge(const s3d::FilePath& aase)
    {
#ifdef ABYSS_CUSTOM
        AudioSettingGroup other = Resource::Assets::Main()->load(aase, Path::Root);
        this->merge(*other.m_pImpl);
#else
        Impl other(aase);
        this->merge(other);
#endif
    }
}
