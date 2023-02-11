#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/base/Issue.hpp>

namespace abyss::Devs::Project
{
    /// <summary>
    /// タスク集
    /// </summary>
    class Tasks
    {
    public:
        Tasks();

        /// <summary>
        /// タスクの追加
        /// </summary>
        /// <param name="issue"></param>
        void add(Issue&& issue);

        /// <summary>
        /// タスクの取得
        /// </summary>
        /// <param name="status"></param>
        /// <returns></returns>
        const s3d::Array<Issue>& issues(TaskStatus status) const;
    private:
        s3d::HashTable<TaskStatus, s3d::Array<Issue>> m_issues;
    };
}

#endif
