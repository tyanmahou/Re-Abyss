#pragma once
#include <functional>
#include <abyss/utils/Coro/Task/Task.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Coro
{
	/// <summary>
	/// 複数タスク
	/// </summary>
    class MultiTasks
    {
	public:
		MultiTasks() = default;

		/// <summary>
		/// 追加
		/// </summary>
		/// <param name="task"></param>
		/// <returns></returns>
		MultiTasks& add(const std::function<Task<>()>& task);

		/// <summary>
		/// 実行
		/// </summary>
		/// <returns></returns>
		Task<> operator()() const;
	private:
		s3d::Array<std::function<Task<>()>> m_tasks;
    };
}