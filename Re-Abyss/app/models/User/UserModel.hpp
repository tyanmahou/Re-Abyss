#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/DateTime.hpp>

#include <abyss/types/UserPlayMode.hpp>

namespace abyss::User
{
    /// <summary>
    /// ユーザーモデル
    /// </summary>
    class UserModel
    {
    public:
        UserModel() = default;

        UserModel& setUserId(s3d::int32 userId)
        {
            m_userId = userId;
            return *this;
        }

        s3d::int32 getUserId() const
        {
            return m_userId;
        }

        UserModel& setPlayMode(UserPlayMode playMode)
        {
            m_playMode = playMode;
            return *this;
        }

        UserPlayMode getPlayMode() const
        {
            return m_playMode;
        }

        UserModel& setPlayTime(const s3d::Duration& playTime)
        {
            m_playTime = playTime;
            return *this;
        }

        const s3d::Duration& getPlayTime() const
        {
            return m_playTime;
        }
        
        UserModel& setUpdatedAt(const  s3d::DateTime& updatedAt)
        {
            m_updatedAt = updatedAt;
            return *this;
        }

        const  s3d::DateTime& getUpdatedAt() const
        {
            return m_updatedAt;
        }

        UserModel& setCreatedAt(const  s3d::DateTime& createdAt)
        {
            m_createdAt = createdAt;
            return *this;
        }

        const  s3d::DateTime& getCreatedAt() const
        {
            return m_createdAt;
        }

        UserModel& setLoginOrSaveAt(const  s3d::DateTime& loginAt)
        {
            m_loginOrSaveAt = loginAt;
            return *this;
        }

        const  s3d::DateTime& getLoginOrSaveAt() const
        {
            return m_loginOrSaveAt;
        }

    private:
        s3d::int32 m_userId;
        UserPlayMode m_playMode;
        s3d::Duration m_playTime;
        s3d::DateTime m_updatedAt;
        s3d::DateTime m_createdAt;

        s3d::DateTime m_loginOrSaveAt;
    };
}