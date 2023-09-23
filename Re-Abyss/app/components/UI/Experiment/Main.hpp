#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>

namespace abyss::UI::Experiment
{
    class ITopic;

    class Main final :
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        Main(UIObj* pUi);

        void setTopic(std::shared_ptr<ITopic> topic)
        {
            m_topic = topic;
        }
    public:
        void onUpdate() override;
    public:
        void onDraw()const override;
    private:
        UIObj* m_pUi;
        std::shared_ptr<ITopic> m_topic;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<UI::Experiment::Main>
    {
        using Base = MultiComponents<
            UI::IUpdate,
            UI::IDraw
        >;
    };
}
#endif
