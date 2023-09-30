#include <abyss/components/UI/Experiment/Builder.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Experiment/Main.hpp>
#include <abyss/components/UI/Experiment/TopicBoard.hpp>
#include <abyss/components/UI/Experiment/DualComplexLab/Topic.hpp>
#include <abyss/components/UI/Experiment/WorkLab/Topic.hpp>

namespace abyss::UI::Experiment
{
    void Builder::Build(UIObj* pUi)
    {
        pUi->attach<Main>(pUi);
        pUi->attach<TopicBoard>(pUi)
            ->add<WorkLab::Topic>(U"作業用")
            .add<DualComplexLab::Topic>(U"二重複素数")
            ;
    }
}
#endif
