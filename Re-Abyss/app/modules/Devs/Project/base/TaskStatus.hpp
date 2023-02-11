#pragma once
#if ABYSS_DEVELOP
namespace abyss::Devs::Project
{
    /// <summary>
    /// タスクのステータス
    /// </summary>
    enum class TaskStatus
    {
        /// <summaryなし</summary>
        None,

        /// <summary>Todo</summary>
        Todo,

        /// <summary>作業中</summary>
        InProgress,

        /// <summary> 完了</summary>
        Done,
    };
}
#endif
