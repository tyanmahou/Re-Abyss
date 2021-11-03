#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/modules/UI/base/Layer.hpp>

namespace abyss::UI
{
    class UIObj final : public GameObject
    {
    public:

        void update();
        void postUpdate();

        void draw() const;

        double deltaTime() const;

        bool isActive(const Layer& layer) const;

        void setLayer(const Layer& layer)
        {
            m_layer = layer;
        }
    private:
        Layer m_layer{};
    };
}