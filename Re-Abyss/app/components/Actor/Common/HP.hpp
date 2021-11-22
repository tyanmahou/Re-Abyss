#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor
{
    class HP : public IComponent
    {
    private:
        s3d::int32 m_hp;
        s3d::int32 m_maxHp;
        ActorObj* m_pActor;
    public:
        HP(ActorObj* m_pActor);

        /// <summary>
        /// HP/最大HPをセット
        /// </summary>
        /// <param name="hp"></param>
        /// <returns></returns>
        HP& initHp(s3d::int32 hp);

        HP& setHp(s3d::int32 hp);

        s3d::int32 value() const;

        bool heal(s3d::int32 value);
        bool damage(s3d::int32 power);

        /// <summary>
        /// HPを最大HPにリセット
        /// </summary>
        void reset();

        bool isFull() const;
        bool isDead() const;

        s3d::int32 getHp() const;
        s3d::int32 getMaxHp() const;

    };
}