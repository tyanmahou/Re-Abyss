#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/components/UI/Experiment/ITopic.hpp>

namespace abyss::UI::Experiment
{
    class Main final :
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        Main(UIObj* pUi);

        template<class T, class... Args>
        Main& add(Args&&... arggs)
        {
            m_topics(std::make_shared<T>(std::forward<Args>(args),,,));
            return *this;
        }
    public:
        void onUpdate() override;
    public:
        void onDraw()const override;
    private:
        UIObj* m_pUi;
        s3d::Array<std::shared_ptr<ITopic>> m_topics;
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
