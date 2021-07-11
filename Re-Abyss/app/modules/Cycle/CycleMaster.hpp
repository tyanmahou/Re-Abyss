#pragma once
#include <abyss/concepts/Cycle.hpp>
#include <abyss/modules/Cycle/base/CycleObj.hpp>

namespace abyss::Cycle
{
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
            requires CycleBuildy<Type, Args...>
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