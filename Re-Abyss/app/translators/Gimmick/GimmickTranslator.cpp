#include "GimmickTranslator.hpp"
#include <abyss/entities/Actors/Gimmick/DoorEntity.hpp>
#include <abyss/controllers/Actors/Door/DoorActor.hpp>
#include <abyss/controllers/Stage/Stage.hpp>

namespace abyss
{
    GimmickTranslator::GimmickTranslator(Stage* pStage):
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
                    DoorModel door(doorEntity.pos, startPos->getPos(), doorEntity.size);
                    return std::make_shared<DoorActor>(door, *room);
                }
            }
        }
        default:
            break;
        }
        return nullptr;
    }
}
