#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/modules/Decor/base/BufferLayer.hpp>

namespace abyss::decor
{
    class DecorObj final : public GameObject
    {
    public:
        DecorObj();

        void update();
        void draw() const;

        DecorObj& setBufferLayer(BufferLayer layer)
        {
            m_bufferLayer = layer;
            return *this;
        }

        BufferLayer getBufferLayer()const
        {
            return m_bufferLayer;
        }
    private:
        BufferLayer m_bufferLayer;
    };
}