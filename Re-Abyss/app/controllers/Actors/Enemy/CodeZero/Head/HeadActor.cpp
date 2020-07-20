#include <abyss/models/Actors/Enemy/CodeZero/Head/State/BaseState.hpp>

#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/CustomDrawModel.hpp>

#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Head/HeadVM.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::CodeZero;
    using namespace abyss::CodeZero::Head;

    class MotionImpl : public abyss::CustomDrawModel::IImpl
    {
        IActor* m_pActor = nullptr;
        Ref<HeadModel> m_head;
        Ref<HPModel> m_hp;
        std::unique_ptr<HeadVM> m_view;
    private:
        HeadVM* getBindedView() const
        {
            return &m_view->setTime(m_pActor->getDrawTimeSec())
                .setPos(m_head->getPos())
                .setForward(m_head->getForward())
                .setIsDamaging(m_hp->isInInvincibleTime());
        }
        void setup() override
        {
            m_head = m_pActor->find<HeadModel>();
            m_hp = m_pActor->find<ParentCtrlModel>()->getHp();
        }

        void onDraw([[maybe_unused]]const s3d::String& motion) const override
        {
            auto view = this->getBindedView();
            if (!view) {
                return;
            }
            
            view->draw();
        }
    public:
        MotionImpl(IActor* pActor) :
            m_pActor(pActor),
            m_view(std::make_unique<HeadVM>())
        {}
    };
}
namespace abyss::CodeZero::Head
{
    HeadActor::HeadActor(CodeZeroActor* parent)
    {
        {
            m_parent = this->attach<ParentCtrlModel>(parent);
        }
        {
            m_head = this->attach<HeadModel>(this);
        }
        {
            this->attach<OldStateModel<HeadActor>>(this)
                ->add<BaseState>(State::Base)
                ;
        }
        {
            auto col = this->attach<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }

        // 描画
        {
            this->attach<CustomDrawModel>()
                ->setDrawer<MotionImpl>(this);
        }
    }
    s3d::Vec2 HeadActor::getPos() const
    {
        return m_head->getPos();
    }

    CShape HeadActor::getCollider() const
    {
        return s3d::Circle(this->getPos() + s3d::Vec2{0, 10}, Param::Head::ColRadius);
    }
    bool HeadActor::accept(const ActVisitor & visitor)
    {
        return visitor.visit(static_cast<Receiver&>(*this))
            || visitor.visit(static_cast<IActor&>(*this));
    }
}
