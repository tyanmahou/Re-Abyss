#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/Devs/GitHub/Task.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Devs::GitHub
{
    /// <summary>
    /// GitHub機能
    /// </summary>
    class GitHub
    {
    public:
        GitHub();
        GitHub(const s3d::String& owner, const s3d::String& repository, const s3d::String& token);

        const s3d::Array<TaskIssue>& getIssues(const s3d::String& status) const;
        bool open(const s3d::String& url) const;
    private:
        s3d::String m_owner;
        s3d::String m_repository;
        s3d::String m_token;

        Task m_task;
    };
}
#endif
