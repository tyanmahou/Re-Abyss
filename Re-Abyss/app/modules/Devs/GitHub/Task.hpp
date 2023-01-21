#pragma once
#if ABYSS_DEVELOP
#include <abyss/utils/JSON/JSONUtil.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/HashTable.hpp>
namespace abyss::Devs::GitHub
{
    struct TaskIssue
    {
        [[JSON_BIND(title)]]
        s3d::String title;

        [[JSON_BIND(url)]]
        s3d::String url;
    };

    class Task
    {
    public:
        Task(const s3d::String& projectId, const s3d::String& token);

        bool load(const s3d::String& projectId, const s3d::String& token);

        const s3d::Array<TaskIssue>& getIssues(const s3d::String& status) const;
    private:
        s3d::HashTable<s3d::String, s3d::Array<TaskIssue>> m_issues;
    };
}
#endif
