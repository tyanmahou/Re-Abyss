#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss::UI
{
    class UIObj final : public GameObject
    {
    private:
        s3d::int32 m_order = 0;
    public:

        void setOrder(s3d::int32 order)
        {
            m_order = order;
        }

        s3d::int32 getOrder() const
        {
            return m_order;
        }

        void update();
        void postUpdate();

        void draw() const;

        double deltaTime() const;
    };
}