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
    private:
        CycleObj m_master;
    };
}