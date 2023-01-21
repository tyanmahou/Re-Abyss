#include <abyss/modules/Devs/GitHub/Task.hpp>
#if ABYSS_DEVELOP
#include <abyss/debugs/Debug.hpp>
#include <abyss/utils/Network/GitHub/GitHubService.hpp>

namespace abyss::Devs::GitHub
{
    using namespace abyss::Network::GitHub;

    Task::Task(const s3d::String& projectId, const s3d::String& token)
    {
        this->load(projectId, token);
    }

    bool Task::load(const s3d::String& projectId, const s3d::String& token)
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
        auto response = GitHubService::GraphQL(query.replace(U"<PROJECT_ID>", projectId), token);

        if (response) {
            for (auto&& node : response[U"data"][U"node"][U"items"][U"nodes"].arrayView()) {
                auto&& status = node[U"fieldValueByName"][U"name"].getOpt<String>().value_or(U"No Status");
                m_issues[status] << JSONUtil::FromJSON<TaskIssue>(node[U"content"]);
            }
            return true;
        } else {
            Debug::Log::Error(U"[GitHub]Issueの取得に失敗しました");
        }
        return false;
    }

    const s3d::Array<TaskIssue>& Task::getIssues(const s3d::String& status) const
    {
        return m_issues.at(status);
    }

}
#endif
