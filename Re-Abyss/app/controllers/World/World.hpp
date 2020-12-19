#pragma once

#include <abyss/controllers/Actors/base/ActorsHolder.hpp>

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

        void reset();
        void draw() const;

        template<class Type, class... Args>
        std::shared_ptr<Actor::IActor> create(Args&& ... args)
            requires ActBuildy<Type, Args...>
        {
            auto obj = std::make_shared<Actor::IActor>();
            Type::Build(obj.get(), std::forward<Args>(args)...);
            this->regist(obj);
            return obj;
        }
        template<class Type, class... Args>
        std::shared_ptr<Type> create(Args&& ... args) 
            requires IsActor<Type>
        {
            auto obj = std::make_shared<Type>(std::forward<Args>(args)...);
            this->regist(obj);
            return obj;
        }

        template<class Type>
        void regist(const std::shared_ptr<Type>& actor) 
            requires IsActor<Type>
        {
            actor->setManager(m_pManager);
            m_actorsHolder.pushActor(actor);
        }

        template<class Type>
        [[nodiscard]] Ref<Type> find() const
            requires IsActor<Type>
        {
            return m_actorsHolder.find<Type>();
        }

        template<class Type>
        [[nodiscard]] s3d::Array<Ref<Type>> finds() const
        {
            return m_actorsHolder.finds<Type>();
        }
    };
}
