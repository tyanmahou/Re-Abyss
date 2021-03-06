#include "Builder.hpp"
#include <abyss/modules/Cron/base/Batch.hpp>

#include <abyss/components/Crons/BubbleGenerator/Generator.hpp>
#include <abyss/components/Crons/Commons/IntervalTimeScheduler.hpp>

namespace abyss::cron::BubbleGenerator
{
    void Builder::Build(Batch* batch)
    {
        batch->attach<Generator>(batch->getManager());
    }

    void BuildIntervalTime::Build(Batch* batch, const s3d::Duration& duration)
    {
        Builder::Build(batch);

        batch->attach<IntervalTimeScheduler>(batch->getManager(), duration);
    }
}
