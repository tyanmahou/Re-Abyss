#include "Builder.hpp"
#include <abyss/modules/Cron/base/Batch.hpp>

#include <abyss/components/Cron/BubbleGenerator/Generator.hpp>
#include <abyss/components/Cron/Common/OnceScheduler.hpp>
#include <abyss/components/Cron/Common/RoomMoveCallbackCtrl.hpp>

namespace abyss::Cron::BubbleGenerator
{
    void Builder::Build(Batch* batch)
    {
        batch->attach<Generator>(batch->getManager());

        if (auto roomManager = batch->getModule<RoomManager>()) {
            batch->attach<RoomMoveCallbackCtrl>(batch);
        }
    }

    void BuildOnce::Build(Batch* batch)
    {
        Builder::Build(batch);

        batch->attach<OnceScheduler>();
    }
}
