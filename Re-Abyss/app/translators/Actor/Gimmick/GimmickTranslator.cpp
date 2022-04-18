#include <abyss/translators/Actor/Gimmick/GimmickTranslator.hpp>

#include <abyss/entities/Actor/Gimmick/DoorEntity.hpp>
#include <abyss/entities/Actor/Gimmick/BulletinEntity.hpp>
#include <abyss/entities/Actor/Gimmick/BushEntity.hpp>
#include <abyss/entities/Actor/Gimmick/EventTriggerEntity.hpp>
#include <abyss/entities/Actor/Gimmick/CodeZeroBackEntity.hpp>

#include <abyss/components/Actor/Gimmick/Door/Builder.hpp>
#include <abyss/components/Actor/Gimmick/Bulletin/Builder.hpp>
#include <abyss/components/Actor/Gimmick/Bush/Builder.hpp>
#include <abyss/components/Actor/Gimmick/EventTrigger/Builder.hpp>
#include <abyss/components/Actor/Gimmick/CodeZeroBack/Builder.hpp>

#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/World/World.hpp>

namespace abyss::Actor::Gimmick
{
    GimmickTranslator::GimmickTranslator(const Stage* pStage):
        m_pStage(pStage)
    {}

    Ref<Actor::ActorObj> GimmickTranslator::buildActor(World& world, const GimmickEntity& entity)
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
        case GimmickType::Bulletin:
        {
            return world.create<Bulletin::Builder>(static_cast<const BulletinEntity&>(entity));
        }
        case GimmickType::Bush:
        {
            return world.create<Bush::Builder>(static_cast<const BushEntity&>(entity));
        }
        case GimmickType::EventTrigger:
        {
            const auto& eventTriggerEntity = static_cast<const EventTriggerEntity&>(entity);
            return world.create<EventTrigger::Builder>(eventTriggerEntity.event);
        }
        case GimmickType::BgmChanger: return nullptr;
        case GimmickType::CodeZeroBack:
        {
            return world.create<CodeZeroBack::Builder>(static_cast<const CodeZeroBackEntity&>(entity));
        }
        default:
            break;
        }
        return nullptr;
    }
}
