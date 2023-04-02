#pragma once
#include <abyss/commons/Fwd.hpp>
#include <memory>

namespace abyss::Factory::System
{
    struct StageFactoryOption
    {
        s3d::String mapPath;
        std::shared_ptr<StageData> stageData;
        std::shared_ptr<Adv::Project> advProject;
    };
}
