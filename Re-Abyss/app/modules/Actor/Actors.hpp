#pragma once
#include <abyss/modules/Actor/base/ActorsHolder.hpp>

namespace abyss::Actor
{
    class Actors
    {
    public:
        Actors();
        ~Actors();

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
        /// 物理衝突前
        /// </summary>
        void prePhysics();

        /// <summary>
        /// 物理衝突後
        /// </summary>
        void postPhysics();

        /// <summary>
        /// 衝突前処理
        /// </summary>
        void preCollision();

        /// <summary>
        /// 衝突後処理
        /// </summary>
        void postCollision();

        void lastUpdate();

        void cleanUp();

        /// <summary>
        /// チェックイン
        /// </summary>
        void onCheckIn();

        /// <summary>
        /// チェックアウト
        /// </summary>
        void onCheckOut();

        void draw() const;


        template<class Type, class... Args>
        std::shared_ptr<ActorObj> create(Args&& ... args)
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
        std::shared_ptr<ActorObj> create();

        /// <summary>
        /// アクターの登録
        /// </summary>
        /// <param name="pAactor"></param>
        void regist(const std::shared_ptr<ActorObj>& pAactor);

        template<class Type>
        [[nodiscard]] Ref<Type> find() const
        {
            return m_actorsHolder.find<Type>();
        }

        template<class Type>
        [[nodiscard]] Ref<ActorObj> findActor() const
        {
            return m_actorsHolder.findActor<Type>();
        }

        template<class Type>
        [[nodiscard]] s3d::Array<Ref<Type>> finds() const
        {
            return m_actorsHolder.finds<Type>();
        }

    private:
        ActorsHolder m_actorsHolder;

        Manager* m_pManager = nullptr;
        BufferLayer m_bufferLayer = BufferLayer::Front;
    };
}
