#include "GimmickTranslator.hpp"
#include <abyss/entities/Actors/Gimmick/DoorEntity.hpp>
#include <abyss/entities/Actors/Gimmick/EventTriggerEntity.h>

#include <abyss/controllers/Actors/Gimmick/Door/DoorActor.hpp>
#include <abyss/controllers/Actors/Gimmick/EventTrigger/EventTriggerActor.hpp>
#include <abyss/controllers/Stage/Stage.hpp>

namespace abyss
{
    GimmickTranslator::GimmickTranslator(const Stage* pStage):
        m_pStage(pStage)
    {}
    std::shared_ptr<IActor> GimmickTranslator::toActorPtr(const GimmickEntity& entity)
    {
        switch (entity.type) {
        case GimmickType::StartPos: return nullptr;
        case GimmickType::Door:
        {
            const auto& doorEntity = static_cast<const DoorEntity&>(entity);
            if (auto startPos = m_pStage->findStartPos(doorEntity.startId)) {
                if (auto room = m_pStage->findRoom(startPos->getPos())) {
                    DoorModel door{
                        startPos->getStartId(),
                        doorEntity.pos, 
                        startPos->getPos(),
                        startPos->getForward(),
                        doorEntity.size,
                        startPos->isSave()
                    };
                    return std::make_shared<Door::DoorActor>(door, *room);
                }
            }
        }
        case GimmickType::EventTrigger:
        {
            const auto& eventTriggerEntity = static_cast<const EventTriggerEntity&>(entity);
            return  std::make_shared<Actor::Gimmick::EventTrigger::EventTriggerActor>(eventTriggerEntity.event);
        }
        case GimmickType::BgmChanger: return nullptr;
        default:
            break;
        }
        return nullptr;
    }
}
