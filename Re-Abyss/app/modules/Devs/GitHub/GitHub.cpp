#include <abyss/modules/Devs/GitHub/GitHub.hpp>
#if ABYSS_DEVELOP
#include <abyss/debugs/Debug.hpp>
#include <abyss/utils/Env/Env.hpp>
#include <abyss/utils/Network/GitHub/GitHubService.hpp>
namespace abyss::Devs
{
    using namespace Network::GitHub;

    GitHub::GitHub():
        GitHub(
            Env::Get(U"GITHUB_OWNER"),
            Env::Get(U"GITHUB_REPOS"),
            Env::Get(U"GITHUB_TOKEN")
        )
    {}
    GitHub::GitHub(const s3d::String& owner, const s3d::String& repository, const s3d::String& token):
        m_owner(owner),
        m_repository(repository),
        m_token(token)
    {
    }

    GitHub::IssueList GitHub::issueList() const
    {
        auto response = GitHubService::ListRepositoryIssues(m_owner, m_repository, m_token);
        if (response) {
            return response.value();
        }
        Debug::Log::Error(U"[GitHub]Issueの取得に失敗しました");
        return {};
    }

    bool GitHub::openIssue(s3d::int32 number) const
    {
        return GitHubService::OpenIssueByBrowser(m_owner, m_repository, number);
    }
}
#endif
