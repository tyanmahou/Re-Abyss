#include "AudioSetting.hpp"
#include <Siv3D.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
namespace abyss
{
    s3d::Audio AudioSetting::load(const s3d::FilePath& basePath, const s3d::TOMLValue& toml) const
    {
        s3d::Audio ret;
        if (auto audioPath = toml[U"path"].getOpt<String>()) {
            ret = Audio(FileUtil::ParentPath(basePath) + *audioPath);
        }
        if (auto loop = toml[U"loop"].getOpt<bool>()) {
            ret.setLoop(*loop);
        } else if (auto loopVec2 = toml[U"loop"].getOpt<Vec2>()) {
            ret.setLoop(Duration(loopVec2->x), Duration(loopVec2->y));
        }
        return ret;
    }
    s3d::Audio AudioSetting::load(const s3d::FilePath& path) const
    {
        TOMLReader toml(path);
        if (!toml) {
            return s3d::Audio();
        }
        return this->load(path, toml[U"Audio"]);
    }
}
