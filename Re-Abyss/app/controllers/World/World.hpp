#pragma once

#include <abyss/controllers/ActorsHolder/ActorsHolder.hpp>
#include <abyss/views/World/WorldView.hpp>
#include <abyss/commons/Concept.hpp>
namespace abyss
{
    class World
    {
    private:
        ActorsHolder m_actorsHolder;
        std::unique_ptr<ICollisionModel> m_collision;

        std::shared_ptr<PlayerActor> m_pPlayer;

        WorldView m_view;
    public:
        World();
        ~World();

        void update();
        void reset();
        void draw() const;

        template<class Type, class... Args>
        void create(Args&& ... args) //requires IsActor<Type>
        {
            auto obj = std::make_shared<Type>(std::forward<Args>(args)...);
            this->regist(obj);
        }

        template<class Type>
        void regist(const std::shared_ptr<Type>& actor) //requires IsActor<Type>
        {
            actor->setWorld(this);
            m_actorsHolder.pushActor(actor);
        }

        inline WorldView& getView() {return m_view;}
        inline const WorldView& getView()const { return m_view; }

        inline void setPlayer(const std::shared_ptr<PlayerActor>& player) { m_pPlayer = player; }
        inline std::shared_ptr<PlayerActor> getPlayer()const { return m_pPlayer; }
    };
}
