#pragma once
#include <functional>

#include <abyss/commons/Fwd.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>

namespace abyss
{
    class OutRoomCheckerModel :
        public IComponent,
        public ILastUpdateModel
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<DeadCheckerModel> m_deadChecker;
        std::function<CShape()> m_colliderFunc;

        bool m_isOutRoom = false;
        bool m_isAutoDestroy = true;
    public:
        OutRoomCheckerModel(IActor* pActor);

        void setup() override;
        void onLastUpdate() override;

        /// <summary>
        /// コライダー関数を登録
        /// </summary>
        /// <param name="func"></param>
        OutRoomCheckerModel& setColFunc(const std::function<CShape()>& func)
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
    struct ComponentTree<OutRoomCheckerModel>
    {
        using Base = ILastUpdateModel;
    };
}