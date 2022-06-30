#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Room/RoomData.hpp>
#include <abyss/components/Actor/Gimmick/Door/DoorData.hpp>
#include <abyss/utils/Collision/CShape.hpp>

namespace abyss::Actor::Gimmick::Door
{
    class DoorProxy :
        public IComponent
    {
    public:
        DoorProxy(ActorObj* pActor, const DoorData& door, const Room::RoomData& nextRoom);

        void setup(Executer executer) override;

        void onStart() override;

        CShape getCollider() const;

        s3d::int32 getStartId()const;
        const Room::RoomData& getNextRoom() const;
        const s3d::Vec2& getPos() const;
        const s3d::Vec2& getTargetPos() const;
        Forward getTargetForward() const;
        DoorKind getKind() const;
        bool isSave()const;
        s3d::Vec2 fixedVisiterPos(const s3d::Vec2& visitSize = { 22,80 }) const;

        ActorObj* getActor()const { return m_pActor; }
        const DoorData& getDoor() const;
    private:
        ActorObj* m_pActor;
        DoorData m_door;
        Room::RoomData m_nextRoom;
    };
}
