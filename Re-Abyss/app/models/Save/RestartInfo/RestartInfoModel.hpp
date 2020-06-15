#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>
namespace abyss
{
    class RestartInfoModel
    {
        s3d::int32 m_startId = 0;
        s3d::Optional<s3d::String> m_bgm;
    public:
        s3d::int32 getStartId() const
        {
            return m_startId;
        }
        void setStartId(s3d::int32 startId)
        {
            m_startId = startId;
        }
        const s3d::Optional<s3d::String>& getBgm() const
        {
            return m_bgm;
        }
        void setBgm(const s3d::String& bgm)
        {
            m_bgm = bgm;
        }
        void setBgm(const s3d::Optional<s3d::String>& bgm)
        {
            m_bgm = bgm;
        }
    };
}