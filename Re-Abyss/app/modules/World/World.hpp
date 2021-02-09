#pragma once

#include <abyss/modules/Actors/base/ActorsHolder.hpp>

namespace abyss
{
    class World
    {
    private:
        Actor::ActorsHolder m_actorsHolder;
        std::unique_ptr<ICollisionModel> m_collision;
        std::unique_ptr<IMapCollisionModel> m_mapCollision;

        Manager* m_pManager = nullptr;
    public:
        World();
        ~World();

        void setManager(Manager* pManager);
        void init();

        /// <summary>
        /// 予約済みアクターを登録
        /// </summary>
        void flush();

        /// <summary>
        /// アクターのデルタ時間を更新
        /// </summary>
        /// <param name="dt"></param>
        void updateDeltaTime(double dt);

        /// <summary>
        /// 更新
        /// </summary>
        void update();

        /// <summary>
        /// 移動処理
        /// </summary>
        void move();

        /// <summary>
        /// 物理衝突
        /// </summary>
        void physics();

        /// <summary>
        /// 衝突判定
        /// </summary>
        void collision();

        void lastUpdate();

        void cleanUp();


        /// <summary>
        /// チェックアウト
        /// </summary>
        void onCheckIn();

        /// <summary>
        /// チェックアウト
        /// </summary>
        void onCheckOut();

        void draw() const;


        template<class Type, class... Args>
        std::shared_ptr<Actor::IActor> create(Args&& ... args)
            requires ActBuildy<Type, Args...>
        {
            auto obj = this->create();
            Type::Build(obj.get(), std::forward<Args>(args)...);
            return obj;
        }

        /// <summary>
        /// アクターの生成
        /// </summary>
        /// <returns></returns>
        std::shared_ptr<Actor::IActor> create();

        /// <summary>
        /// アクターの登録
        /// </summary>
        /// <param name="pAactor"></param>
        void regist(const std::shared_ptr<Actor::IActor>& pAactor);

        template<class Type>
        [[nodiscard]] Ref<Type> find() const
        {
            return m_actorsHolder.find<Type>();
        }

        template<class Type>
        [[nodiscard]] Ref<Actor::IActor> findActor() const
        {
            return m_actorsHolder.findActor<Type>();
        }

        template<class Type>
        [[nodiscard]] s3d::Array<Ref<Type>> finds() const
        {
            return m_actorsHolder.finds<Type>();
        }
    };
}
