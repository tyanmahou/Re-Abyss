#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/models/Actor/Gimmick/Door/DoorModel.hpp>
#include <abyss/types/CShape.hpp>

namespace abyss::Actor::Gimmick::Door
{
    class DoorProxy :
        public IComponent
    {
    public:
        DoorProxy(ActorObj* pActor, const DoorModel& door, const RoomModel& nextRoom);

        void setup(Executer executer) override;

        void onStart() override;

        CShape getCollider() const;

        s3d::int32 getStartId()const;
        const RoomModel& getNextRoom() const;
        const s3d::Vec2& getPos() const;
        const s3d::Vec2& getTargetPos() const;
        Forward getTargetForward() const;
        DoorKind getKind() const;
        bool isSave()const;
        s3d::Vec2 fixedVisiterPos(const s3d::Vec2& visitSize = { 22,80 }) const;

        ActorObj* getActor()const { return m_pActor; }
        const DoorModel& getDoor() const;
    private:
        ActorObj* m_pActor;
        DoorModel m_door;
        RoomModel m_nextRoom;
    };
}