#include <abyss/services/Adv/ProjectService.hpp>
#include <abyss/datastores/Adv/base/IProjectDataStore.hpp>
#include <abyss/commons/MsgUtil.hpp>

namespace abyss::Adv
{
    ProjectService::ProjectService(std::shared_ptr<IProjectDataStore>datastore)
    {
        auto&& entities = datastore->selectCharas();
        m_charas.reserve(entities.size());
        for (auto&& entity : entities) {
            Chara chara;
            chara.setKind(entity.kind);
            chara.setFacePath(entity.facePath);

            const auto& name = MsgUtil::CharaName(entity.kind).get();
            if (!name.isEmpty()) {
                chara.setName(name);
            }
            m_charas << chara;
        }
    }
    void ProjectServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IProjectService>()
            .to<ProjectService>()
            .asCached();
    }
}
