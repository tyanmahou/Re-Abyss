#pragma once
#include <abyss/components/base/Components.hpp>

namespace abyss::Actor::Enemy
{
    // ドロップテーブル種類
    enum class ItemDropTableKind
    {
        Normal,
    };

    /// <summary>
    /// アイテムドロップ制御
    /// </summary>
    class ItemDropCtrl : 
        public IComponent
    {
    public:
        ItemDropCtrl(ActorObj* pActor, ItemDropTableKind tableKind = ItemDropTableKind::Normal);

        Ref<ActorObj> drop() const;
    private:
        ActorObj* m_pActor;
        ItemDropTableKind m_tableKind = ItemDropTableKind::Normal;
    };
}