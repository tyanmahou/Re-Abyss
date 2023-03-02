#include <abyss/modules/Adv/Project/Project.hpp>
#include <abyss/services/Adv/base/IProjectService.hpp>

namespace abyss::Adv
{
    Project::Project(std::shared_ptr<IProjectService> service)
    {
        for (const auto& chara : service->getCharas()) {
            m_charaTable.add(chara);
        }
    }
    s3d::Optional<Chara> Project::findChara(CharaKind kind) const
    {
        return m_charaTable.find(kind);
    }
}
