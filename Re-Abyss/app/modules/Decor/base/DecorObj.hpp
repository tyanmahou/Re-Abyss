#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/modules/Decor/base/BufferLayer.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Decor
{
    class DecorObj final : public GameObject
    {
    public:
        DecorObj();

        void update();
        void draw() const;

        DecorObj& setDeployId(s3d::uint32 deployId)
        {
            m_deployId = deployId;
            return *this;
        }

        const s3d::Optional<s3d::uint32>& getDeployId() const
        {
            return m_deployId;
        }
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
        s3d::Optional<s3d::uint32> m_deployId;
        BufferLayer m_bufferLayer{};
    };
}