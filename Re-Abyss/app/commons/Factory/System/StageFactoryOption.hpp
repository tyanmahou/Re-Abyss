#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/values/StageDef.hpp>
#include <memory>

namespace abyss::Factory::System
{
    struct StageFactoryOption
    {
        StageDef stageDef;
        std::shared_ptr<StageData> stageData;
        std::shared_ptr<abyss::Adv::Project> advProject;
    };
}
