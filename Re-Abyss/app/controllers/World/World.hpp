#pragma once

#include <abyss/controllers/Actors/base/ActorsHolder.hpp>
#include <abyss/views/World/WorldView.hpp>

namespace abyss
{
    class World
    {
    private:
        ActorsHolder m_actorsHolder;
        std::unique_ptr<ICollisionModel> m_collision;

        WorldView m_view;

        ActManager* m_pManager = nullptr;
    public:
        World();
        ~World();

        void setManager(ActManager* pManager);
        void init();

        /// <summary>
        /// 予約済みアクターを登録
        /// </summary>
        void flush();
        void update();
        void reset();
        void draw() const;

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

        template<class Type, class... Args>
        void addEffect(Args&& ... args)
        {
            m_view.addEffect<Type>(std::forward<Args>(args)...);
        }
        [[nodiscard]] inline WorldView& getView() {return m_view;}
        [[nodiscard]] inline const WorldView& getView()const { return m_view; }

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
