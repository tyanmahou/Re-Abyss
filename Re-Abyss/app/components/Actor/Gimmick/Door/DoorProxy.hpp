#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Room/RoomData.hpp>
#include <abyss/entities/Actor/Gimmick/DoorEntity.hpp>
#include <abyss/utils/Collision/CShape.hpp>

namespace abyss::Actor::Gimmick::Door
{
    class DoorProxy :
        public IComponent
    {
    public:
        DoorProxy(ActorObj* pActor, const DoorEntity& entity);

        void setup(Executer executer) override;

        void onStart() override;

        CShape getCollider() const;

        s3d::int32 getStartId()const;
        const s3d::Optional<s3d::String>& getLink() const;

        const s3d::Vec2& getPos() const;
        const s3d::Vec2& getSize() const;
        DoorKind getKind() const;
    private:
        ActorObj* m_pActor;

        s3d::int32 m_startId;
        s3d::Optional<s3d::String> m_link;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_size;
        DoorKind m_kind;
    };
}
