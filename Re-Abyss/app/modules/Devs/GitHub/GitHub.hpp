#pragma once
#if ABYSS_DEVELOP
#include <abyss/utils/Network/GitHub/Issue/Issue.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Devs
{
    /// <summary>
    /// GitHub機能
    /// </summary>
    class GitHub
    {
        using IssueList = Network::GitHub::Issue::IssueList;
    public:
        GitHub();
        GitHub(const s3d::String& owner, const s3d::String& repository, const s3d::String& token);

        IssueList issueList() const;

        bool openIssue(s3d::int32 number) const;
    private:
        s3d::String m_owner;
        s3d::String m_repository;
        s3d::String m_token;
    };
}
#endif
