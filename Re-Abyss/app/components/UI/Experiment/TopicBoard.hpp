#pragma once
#if ABYSS_DEVELOP
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/components/UI/Experiment/ITopic.hpp>
#include <abyss/views/util/List/SimpleVerticalList.hpp>
#include <abyss/utils/Layout/Window/Window.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::Experiment
{
    class Main;

    class TopicBoard final :
        public IComponent,
        public IDraw,
        public List::SimpleVerticalList::IEnumerable
    {
        struct TopicEntry
        {
            s3d::String title;
            std::function<std::shared_ptr<ITopic>()> factory;
        };
    public:
        TopicBoard(UIObj* pUi);
        ~TopicBoard();

        void setup(Executer executer) override;
        void onStart() override;

        template<class T, class... Args>
        TopicBoard& add(const s3d::String& title, Args&&... args)
        {
            m_topics.push_back({
                .title = title,
                .factory = [...args = std::forward<Args>(args)] {
                    return std::make_shared<T>(std::forward<Args>(args)...);
                }
            });
            return *this;
        }
    public:
        void onDraw()const override;
    public:
        Coro::Generator<List::SimpleVerticalList::Record> getList() const override;
    private:
        UIObj* m_pUi;
        std::unique_ptr<Layout::Window::Window> m_window;

        s3d::Array<TopicEntry> m_topics;
        std::unique_ptr<List::SimpleVerticalList> m_list;
        Ref<Main> m_main;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<UI::Experiment::TopicBoard>
    {
        using Base = MultiComponents<
            UI::IDraw
        >;
    };
}
#endif
