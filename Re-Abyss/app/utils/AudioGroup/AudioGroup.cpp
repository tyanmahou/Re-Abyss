#include "AudioGroup.hpp"
#include <Siv3D.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
#include <abyss/utils/AudioSetting/AudioSetting.hpp>

namespace abyss
{
    class AudioGroup::Impl
    {
        HashTable<String, Audio> m_audios;
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
            for (auto&& setting : toml[U"@Extends"].tableArrayView()) {
                auto extendPath = setting[U"path"].getOpt<String>();
                if (!extendPath) {
                    continue;
                }
                auto path = FileUtil::ParentPath(aase) + *extendPath;
                Impl base(path);
                this->merge(base);
            }
            for (auto&&[key, setting] : toml.tableView()) {
                if (key[0] == U'@') {
                    continue;
                }
                m_audios[key] = AudioSetting{}.load(aase, setting);
            }
        }

        Audio operator()(const s3d::String& key)
        {
            if (m_audios.find(key) != m_audios.end()) {
                return m_audios[key];
            }
            return Audio();
        }

        void merge(const Impl& other)
        {
            for (auto&& [key, audio] : other.m_audios) {
                m_audios[key] = audio;
            }
        }
    };
    AudioGroup::AudioGroup(const s3d::FilePath& path):
        m_pImpl(std::make_shared<Impl>(path))
    {}

    Audio AudioGroup::operator()(const s3d::String& key) const
    {
        return (*m_pImpl)(key);
    }
    AudioGroup::operator bool() const
    {
        return m_pImpl != nullptr;
    }
}
