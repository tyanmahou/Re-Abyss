#pragma once
#include <functional>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Collision/CShape.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>

namespace abyss::Actor
{
    class OutRoomChecker :
        public IComponent,
        public ILastUpdate
    {
    private:
        ActorObj* m_pActor = nullptr;
        Ref<DeadChecker> m_deadChecker;
        std::function<CShape()> m_colliderFunc;

        bool m_isOutRoom = false;
        bool m_isAutoDestroy = true;
    public:
        OutRoomChecker(ActorObj* pActor);

        void setup(Executer executer)override;
        void onStart() override;
        void onLastUpdate() override;

        /// <summary>
        /// コライダー関数を登録
        /// </summary>
        /// <param name="func"></param>
        OutRoomChecker& setColFunc(const std::function<CShape()>& func)
        {
            m_colliderFunc = func;
            return *this;
        }
        bool isOutRoom() const
        {
            return m_isOutRoom;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::OutRoomChecker>
    {
        using Base = Actor::ILastUpdate;
    };
}
