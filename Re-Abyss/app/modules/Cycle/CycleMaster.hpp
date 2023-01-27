#pragma once
#include <abyss/modules/Cycle/base/CycleObj.hpp>

namespace abyss::Cycle
{
    template<class Type, class... Args>
    concept CycleBuildable = requires(CycleObj * pCycle, Args&&... args)
    {
        Type::Build(pCycle, std::forward<Args>(args)...);
    };

    /// <summary>
    /// Cycle Master
    /// </summary>
    class CycleMaster
    {
    public:
        /// <summary>
        /// Manager設定
        /// </summary>
        /// <param name="pManager"></param>
        void setManager(Manager* pManager);

        /// <summary>
        /// 初期化
        /// </summary>
        void init();

        /// <summary>
        /// 監視
        /// </summary>
        void listen();

        /// <summary>
        /// ファイナライザ
        /// </summary>
        void finalize();

        /// <summary>
        /// ビルド
        /// </summary>
        template<class Type, class... Args>
        void build(Args&&... args)
            requires CycleBuildable<Type, Args...>
        {
            Type::Build(&m_master, std::forward<Args>(args)...);
        }

        template<class Component>
        Ref<Component> find() const
        {
            return m_master.find<Component>();
        }
    private:
        CycleObj m_master;
    };
}
