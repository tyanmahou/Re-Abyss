#if ABYSS_DEVELOP
#include <abyss/datastores/Devs/Project/GitHubDataStore.hpp>
#include <abyss/utils/Env/Env.hpp>
#include <abyss/utils/Network/GitHub/GitHub.hpp>
#include <abyss/debugs/Debug.hpp>

namespace
{
    using namespace abyss::Devs::Project;

    TaskStatus ToTaskStatus(const s3d::String& status)
    {
        if (status == U"Todo") {
            return TaskStatus::Todo;
        }
        if (status == U"In Progress") {
            return TaskStatus::InProgress;
        }
        if (status == U"Done") {
            return TaskStatus::Done;
        }
        return TaskStatus::None;
    }
}
namespace abyss::Devs::Project
{
    using abyss::Network::GitHub::GitHub;

    GitHubDataStore::GitHubDataStore() :
        GitHubDataStore(
            Env::Get(U"GITHUB_OWNER"),
            Env::Get(U"GITHUB_REPOS"),
            Env::Get(U"GITHUB_TOKEN"),
            Env::Get(U"GITHUB_PROJECT_ID")
        )
    {
    }
    GitHubDataStore::GitHubDataStore(
        const s3d::String& owner,
        const s3d::String& repository,
        const s3d::String& token,
        const s3d::String& projectId
    ):
        m_owner(owner),
        m_repository(repository),
        m_token(token),
        m_projectId(projectId)
    {
    }
    s3d::Array<Issue> GitHubDataStore::issues() const
    {
        String query = UR"(
            query {
              node(id: "<PROJECT_ID>") {
                ... on ProjectV2 {
                  url
                  items(first: 50) {
                    nodes{
                      fieldValueByName(name: "Status"){
                          ... on ProjectV2ItemFieldSingleSelectValue {
                            name
                          }
                      }
                      content{
                        ...on Issue {
                          id
                          title
                          number
                          url
                        }
                      }
                    }
                  }
                }
              }
            }
        )";
        s3d::Array<Issue> result;

        auto response = GitHub::GraphQL(query.replace(U"<PROJECT_ID>", m_projectId), m_token);
        if (response) {
            for (auto&& node : response[U"data"][U"node"][U"items"][U"nodes"].arrayView()) {
                auto&& content = node[U"content"];
                auto&& status = node[U"fieldValueByName"][U"name"].getOpt<String>().value_or(U"No Status");
                result << Issue{
                    .title = content[U"title"].get<String>(),
                    .url = content[U"url"].get<URL>(),
                    .status = ::ToTaskStatus(status),
                };
            }
            return result;
        } else {
#if ABYSS_DEBUG
            Debug::Log::Error(U"[GitHub]Issueの取得に失敗しました");
#endif
        }
        return result;
    }
    void GitHubDataStoreInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IProjectDataStore>()
            .to<GitHubDataStore>()
            .asCache();
    }
}
#endif
