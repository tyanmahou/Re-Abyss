#pragma once
#include <queue>
#include <memory>
#include <abyss/concepts/Novel.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Novel
{
    /// <summary>
    /// ノベル
    /// </summary>
    class Novels
    {
    public:

        Novels& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }

        /// <summary>
        /// 更新
        /// </summary>
        /// <returns></returns>
        bool update();

        /// <summary>
        /// 空か
        /// </summary>
        /// <returns></returns>
        bool isEmpty() const;

        /// <summary>
        /// 会話の生成
        /// </summary>
        /// <returns></returns>
        Ref<TalkObj> create();

        /// <summary>
        /// ビルダーから会話の生成
        /// </summary>
        template<class BuilerType, class... Args>
        Ref<TalkObj> create(Args&& ... args)
            requires TalkBuildy<BuilerType, Args...>
        {
            auto talk = this->create();
            BuilerType::Build(talk.get(), std::forward<Args>(args)...);
            return talk;
        }

        /// <summary>
        /// 会話の登録
        /// </summary>
        /// <param name="event"></param>
        /// <returns></returns>
        Ref<TalkObj> regist(const std::shared_ptr<TalkObj>& talk);
    private:
        std::queue<std::shared_ptr<TalkObj>> m_talks;
        bool m_doneCurrentInit = false;
        Manager* m_pManager;

        std::shared_ptr<CharaTable> m_charaTable;
    };
}