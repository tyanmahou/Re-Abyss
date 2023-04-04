#pragma once
#include <queue>
#include <memory>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/Project/Project.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <Emaject.hpp>

namespace abyss::Adv
{
    template<class Type, class... Args>
    concept AdvBuildable = requires(AdvObj * pObj, Args&&... args)
    {
        Type::Build(pObj, std::forward<Args>(args)...);
    };

    /// <summary>
    /// アドベンチャー
    /// </summary>
    class Adventures
    {
    public:

        Adventures& setManager(Manager* pManager)
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
        Ref<AdvObj> create();

        /// <summary>
        /// ビルダーから会話の生成
        /// </summary>
        template<class BuilerType, class... Args>
        Ref<AdvObj> create(Args&& ... args)
            requires AdvBuildable<BuilerType, Args...>
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
        Ref<AdvObj> regist(const std::shared_ptr<AdvObj>& talk);

        /// <summary>
        /// キャラの検索
        /// </summary>
        /// <param name="kind"></param>
        /// <returns></returns>
        s3d::Optional<Chara> findChara(CharaKind kind) const;

        /// <summary>  
        /// コンポーネントの検索
        /// </summary>
        template<class Type>
        [[nodiscard]] Ref<Type> find() const
        {
            if (isEmpty()) {
                return nullptr;
            }
            return m_talks.front()->find<Type>();
        }
    private:
        [[INJECT(setProject)]]
        Adventures& setProject(std::shared_ptr<Project> project)
        {
            m_project = project;
            return *this;
        }
    private:
        std::queue<std::shared_ptr<AdvObj>> m_talks;
        bool m_doneCurrentInit = false;
        Manager* m_pManager;

        std::shared_ptr<Project> m_project;
    };
}
