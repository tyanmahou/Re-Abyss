#pragma once
#include <functional>

#include <abyss/commons/Fwd.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ILastUpdate.hpp>

namespace abyss::Actor
{
    class OutRoomChecker :
        public IComponent,
        public ILastUpdate
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<DeadChecker> m_deadChecker;
        std::function<CShape()> m_colliderFunc;

        bool m_isOutRoom = false;
        bool m_isAutoDestroy = true;
    public:
        OutRoomChecker(IActor* pActor);

        void setup() override;
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