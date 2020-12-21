#include "Decor.hpp"
#include <abyss/modules/Decor/DecorGraphicsManager.hpp>

namespace abyss
{
    void Decor::clear()
    {
        m_view.clear();
    }
    DecorGraphicsManager* Decor::getGraphicsManager() const
    {
        return m_graphicsManager.get();
    }
    void Decor::regist(s3d::int32 order, const std::shared_ptr<IDecorVM>& decor)
    {
        m_view.add(order, decor);
    }
    Decor::Decor():
        m_graphicsManager(std::make_shared<DecorGraphicsManager>())
    {}
    void Decor::update(double time)
    {
        m_view.update(time);
    }
    void Decor::draw(s3d::int32 order, const s3d::RectF& screen) const
    {
        m_view.draw(order, screen);
    }
    void Decor::drawBack(const s3d::RectF& screen) const
    {
        this->draw(DecorOrder::Back, screen);
    }
    void Decor::drawMiddle(const s3d::RectF& screen) const
    {
        this->draw(DecorOrder::Middle, screen);
    }
    void Decor::drawFront(const s3d::RectF & screen) const
    {
        this->draw(DecorOrder::Front, screen);
    }
}
