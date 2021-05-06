#include "Decors.hpp"
#include "DecorGraphics.hpp"

namespace abyss
{
    Decors::Decors()
    {}
    void Decors::flush()
    {
        m_decors.flush();
    }
    void Decors::update()
    {
        m_decors.update();
    }
    void Decors::draw() const
    {
        m_decors.draw();
    }

    void Decors::onCheckOut()
    {
        m_bufferLayer = Decor::FlipBuffer(m_bufferLayer);
    }

    void Decors::onCheckIn()
    {
        m_decors.clear(Decor::FlipBuffer(m_bufferLayer));
    }

    Ref<Decor::DecorObj> Decors::create()
    {
        return  this->regist(std::make_shared<Decor::DecorObj>());
    }

    Ref<Decor::DecorObj> Decors::regist(const std::shared_ptr<Decor::DecorObj>& decor)
    {
        decor->setManager(m_pManager);
        decor->setBufferLayer(m_bufferLayer);
        m_decors.push(decor);
        return decor;
    }

    s3d::uint32 Decors::getAnimGId(s3d::uint32 gId, double time) const
    {
        return m_graphics->getAnimGId(gId, time);
    }
    s3d::TextureRegion Decors::getTexture(s3d::uint32 gId, double time) const
    {
        return m_graphics->getTexture(gId, time);
    }

    size_t Decors::size() const
    {
        return m_decors.size();
    }

    Decor::DecorIdTable Decors::getIdTable() const
    {
        return m_decors.getIdTable();
    }
}
