#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/base/Tasks.hpp>

namespace abyss::Devs::Project
{
    Tasks::Tasks()
    {
        m_issues[TaskStatus::None] = {};
        m_issues[TaskStatus::Todo] = {};
        m_issues[TaskStatus::InProgress] = {};
        m_issues[TaskStatus::Done] = {};
    }
    void Tasks::add(Issue&& issue)
    {
        m_issues[issue.status] << std::move(issue);
    }
    const s3d::Array<Issue>& Tasks::issues(TaskStatus status) const
    {
        return m_issues.at(status);
    }
}
#endif
