#pragma once
#include <Siv3D/String.hpp>

namespace abyss
{
    /// <summary>
    /// ステージ種類
    /// </summary>
    class StageDef
    {
    public:
        static StageDef Stage0();
        static StageDef FromDircet(const s3d::FilePath& mapPath);
    public:
        StageDef() = default;

        const s3d::FilePath& mapPath() const
        {
            return m_mapPath;
        }
        s3d::String mapName() const;

        s3d::String preloadPath() const;

        bool isTestMap() const;

        StageDef link(const s3d::String& link) const;

        bool isValid() const;
    private:
        StageDef(const s3d::FilePath& mapPath);
    private:
        s3d::String m_mapPath;
    };
}
