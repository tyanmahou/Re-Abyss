#include <abyss/modules/Devs/GitHub/GitHub.hpp>
#if ABYSS_DEVELOP
#include <abyss/utils/Env/Env.hpp>
#include <Siv3D.hpp>

namespace abyss::Devs::GitHub
{
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
        m_token(token),
        m_task(Env::Get(U"GITHUB_PROJECT_ID"), token)
    {
    }
    const s3d::Array<TaskIssue>& GitHub::getIssues(const s3d::String& status) const
    {
        return m_task.getIssues(status);
    }
    bool GitHub::open(const s3d::String& url) const
    {
        return System::LaunchBrowser(url);
    }
}
#endif
