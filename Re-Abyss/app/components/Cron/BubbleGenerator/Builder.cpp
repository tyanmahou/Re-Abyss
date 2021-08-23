#include "Builder.hpp"
#include <abyss/modules/Cron/base/Batch.hpp>

#include <abyss/components/Cron/BubbleGenerator/Generator.hpp>
#include <abyss/components/Cron/Commons/IntervalTimeScheduler.hpp>
#include <abyss/components/Cron/Commons/RoomMoveCallbackCtrl.hpp>

namespace abyss::Cron::BubbleGenerator
{
    void Builder::Build(Batch* batch)
    {
        batch->attach<Generator>(batch->getManager());

        if (auto roomManager = batch->getModule<RoomManager>()) {
            batch->attach<RoomMoveCallbackCtrl>(batch);
        }
    }

    void BuildIntervalTime::Build(Batch* batch, const s3d::Duration& duration)
    {
        Builder::Build(batch);

        batch->attach<IntervalTimeScheduler>(batch->getManager(), duration);
    }
}
