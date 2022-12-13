#pragma once
#include <functional>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Coro
{
	/// <summary>
	/// 複数Fiber
	/// </summary>
    class MultiFibers
    {
	public:
		MultiFibers() = default;

		/// <summary>
		/// 追加
		/// </summary>
		/// <param name="fiber"></param>
		/// <returns></returns>
		MultiFibers& add(const std::function<Fiber<>()>& fiber);

		/// <summary>
		/// 実行
		/// </summary>
		/// <returns></returns>
        Fiber<> operator()() const;
	private:
		s3d::Array<std::function<Fiber<>()>> m_fibers;
    };
}
