#pragma once
#include <memory>
#include <functional>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Windows/Windows.hpp>

namespace abyss::Windows
{
	/// <summary>
	/// カスタムウィンドウプロシージャ
	/// </summary>
	class CustomWindowProc
	{
	public:
		using Callback_t = std::function<s3d::Optional<LRESULT> CALLBACK(HWND, UINT, WPARAM, LPARAM)>;

		class Impl;
	public:

		/// <summary>
		/// コンストラクタ
		/// </summary>
		CustomWindowProc();

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="callback">登録するコールバック</param>
		CustomWindowProc(const Callback_t& callback);

		/// <summary>
		/// プロシージャのコールバックを登録
		/// </summary>
		/// <param name="callback"></param>
		void setCallback(const Callback_t& callback);
	private:
		std::shared_ptr<Impl> m_pImpl;
	};
}
