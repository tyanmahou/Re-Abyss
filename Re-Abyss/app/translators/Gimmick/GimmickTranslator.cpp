#include "GimmickTranslator.hpp"
#include <abyss/entities/Actors/Gimmick/DoorEntity.hpp>
#include <abyss/entities/Actors/Gimmick/EventTriggerEntity.h>

#include <abyss/components/Actors/Gimmick/Door/Builder.hpp>
#include <abyss/components/Actors/Gimmick/EventTrigger/Builder.hpp>

#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/World/World.hpp>

namespace abyss
{
    GimmickTranslator::GimmickTranslator(const Stage* pStage):
        m_pStage(pStage)
    {}

    Ref<Actor::IActor> GimmickTranslator::buildActor(World& world, const GimmickEntity& entity)
    {
        using namespace Actor::Gimmick;
        switch (entity.type) {
        case GimmickType::StartPos: return nullptr;
        case GimmickType::Door:
        {
            const auto& doorEntity = static_cast<const DoorEntity&>(entity);
            if (auto startPos = m_pStage->findStartPos(doorEntity.startId)) {
                if (auto room = m_pStage->findRoom(startPos->getPos())) {
                    Door::DoorModel door{
                        startPos->getStartId(),
                        doorEntity.pos,
                        startPos->getPos(),
                        startPos->getForward(),
                        doorEntity.size,
                        doorEntity.kind,
                        startPos->isSave()
                    };
                    return world.create<Door::Builder>(door, *room);
                }
            }
            break;
        }
        case GimmickType::EventTrigger:
        {
            const auto& eventTriggerEntity = static_cast<const EventTriggerEntity&>(entity);
            return world.create<EventTrigger::Builder>(eventTriggerEntity.event);
        }
        case GimmickType::BgmChanger: return nullptr;
        default:
            break;
        }
        return nullptr;
    }
}
