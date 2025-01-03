﻿#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Player/PlayerDesc.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Player
{
    class PlayerManager
    {
    public:
        PlayerManager() = default;

        void regist(const Ref<ActorObj>& player);

        PlayerManager& setPos(const s3d::Vec2& pos);
        PlayerManager& setCenterPos(const s3d::Vec2& pos);
        const s3d::Vec2& getPos() const;
        s3d::Vec2 getCenterPos() const;
        const s3d::Vec2& getVelocity() const;

        const Ref<ActorObj>& getActor() const;

        PlayerDesc getDesc(bool asDirect = false) const;
        PlayerDesc getDescAsDirect() const;
    private:
        Ref<ActorObj> m_player;
        Ref<Body> m_body;
        Ref<HP> m_hp;
    };
}
