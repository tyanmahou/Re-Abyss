#include <abyss/values/StageDef.hpp>
#include <abyss/commons/Path.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>

namespace
{
    using namespace abyss;

    String MapName(const s3d::String& fullPath)
    {
#if ABYSS_DEBUG
        if (fullPath.includes(U"tests/data/maps")) {
            auto relativeTestPath = s3d::FileSystem::RelativePath(FileUtil::FixRelativePath(fullPath), Path::TestMapPath);
            return U"TestMap/{}"_fmt(relativeTestPath.substrView(0, relativeTestPath.lastIndexOf('.')));
        }
#endif
        auto relativePath = s3d::FileSystem::RelativePath(FileUtil::FixRelativePath(fullPath), Path::MapPath);
        return U"Map/{}"_fmt(relativePath.substrView(0, relativePath.lastIndexOf('.')));
    }
}
namespace abyss
{
    StageDef StageDef::Stage0()
    {
        return { Path::MapPath + U"Stage0/Stage0_0.tmx" };
    }
    StageDef StageDef::FromDircet(const s3d::FilePath& mapPath)
    {
        return {mapPath};
    }
    s3d::String StageDef::mapName() const
    {
        return ::MapName(m_mapPath);
    }
    s3d::String StageDef::preloadPath() const
    {
#if ABYSS_DEBUG
        if (this->isTestMap()) {
            return U"Map/Test";
        }
#endif
        return this->mapName();
    }
    bool StageDef::isTestMap() const
    {
        return m_mapPath.includes(U"tests/data/maps");
    }
    StageDef StageDef::link(const s3d::String& link) const
    {
#if ABYSS_DEBUG
        if (this->isTestMap()) {
            return { Path::TestMapPath + link + U".tmx" };
        }
#endif
        return { Path::MapPath + link + U".tmx" };
    }
    StageDef::StageDef(const s3d::FilePath& mapPath):
        m_mapPath(mapPath)
    {
    }
}
