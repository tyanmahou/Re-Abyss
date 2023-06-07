#include <abyss/datastores/Sound/CSVSoundBankDataStore.hpp>
#include <abyss/utils/AudioSetting/AudioSettingReader.hpp>
#include <abyss/commons/Path.hpp>

namespace abyss::Sound
{
    CSVSoundBankDataStore::CSVSoundBankDataStore(const s3d::FilePath& path, Resource::Assets* pAsset)
    {
        m_csv = pAsset->loadCSV(path, Path::Root);
    }
    s3d::HashTable<s3d::String, AudioSetting> CSVSoundBankDataStore::select() const
    {
        s3d::HashTable<s3d::String, AudioSetting> ret{};
        for (auto&& row : m_csv.getData()) {
            if (row[0].isEmpty()) {
                continue;
            }
            AudioSetting as{};
            if (auto&& audioPath = row[1]) {
                as.path = Path::SoundPath + audioPath;
            }
            if (auto loop = s3d::ParseOpt<bool>(row[2])) {
                as.loop = s3d::Loop{ *loop };
            } else if (auto loopBegin = s3d::ParseOpt<double>(row[2])) {
                as.loop = s3d::Duration(*loopBegin);
            } else if (auto loopBeginEnd = s3d::ParseOpt<Vec2>(row[2])) {
                as.loop = s3d::Vector2D<s3d::Duration>{ loopBeginEnd->x, loopBeginEnd->y };
            } else {
                as.loop = s3d::Loop::No;
            }
            if (auto samplingRate = s3d::ParseOpt<s3d::uint64>(row[3])) {
                as.samplingRate = *samplingRate;
            } else {
                as.samplingRate = 44100;
            }
            if (auto streaming = s3d::ParseOpt<bool>(row[4])) {
                as.streaming = *streaming;
            } else {
                as.streaming = false;
            }
            ret.emplace(row[0], std::move(as));
        }
        return ret;
    }
}
