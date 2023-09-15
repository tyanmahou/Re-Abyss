#include <abyss/components/UI/Experiment/Builder.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Experiment/Main.hpp>
#include <abyss/components/UI/Experiment/DualComplexLab/Topic.hpp>

namespace abyss::UI::Experiment
{
    void Builder::Build(UIObj* pUi)
    {
        pUi->attach<Main>(pUi)
            ->add<DualComplexLab::Topic>()
            ;
    }
}
#endif
