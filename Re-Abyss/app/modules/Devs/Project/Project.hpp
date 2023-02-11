#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/Devs/Project/base/Issue.hpp>

namespace abyss::Devs::Project
{
    class IProjectService;

    /// <summary>
    /// 開発プロジェクトモジュール
    /// </summary>
    class Project
    {
    public:
        Project();
        Project(std::shared_ptr<IProjectService> service);

        const s3d::Array<Issue>& issues(TaskStatus status) const;
        bool open(const s3d::URL& url) const;
    private:
        std::shared_ptr<IProjectService> m_service;
    };
}
#endif
