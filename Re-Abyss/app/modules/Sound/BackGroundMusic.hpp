#pragma once
#include <stack>
#include <Siv3D/String.hpp>
#include <Siv3D/Audio.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss
{
    /// <summary>
    /// BGM制御
    /// </summary>
    class BackGroundMusic
    {
    public:
        BackGroundMusic(Resource::Assets* pAssets = Resource::Assets::Norelease());

        /// <summary>
        /// 再生
        /// </summary>
        /// <param name="path"></param>
        /// <param name="sec"></param>
        void play(const s3d::String& path, const s3d::Duration& sec = 0.2s);

        /// <summary>
        /// 停止
        /// </summary>
        /// <param name="sec"></param>
        void stop(const s3d::Duration& sec = 0.2s);

        /// <summary>
        /// リリース
        /// </summary>
        void release();

        const s3d::Optional<s3d::String>& getCurrentPath()const
        {
            return m_currentPath;
        }

        /// <summary>
        /// 一時退避
        /// </summary>
        void stash(const s3d::Duration& sec = 2s);
        void stashPop(const s3d::Duration& sec = 2s);

        void setVolume(double volume);
        void setVolume(double volume, const s3d::Duration& time);
    private:
        Resource::Assets* m_pAssets;

        s3d::Audio m_prev;
        s3d::Audio m_current;
        s3d::Optional<s3d::String> m_currentPath;
        std::stack<s3d::String> m_stash;
    };
}
