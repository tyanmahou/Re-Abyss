#pragma once

namespace abyss
{
	/// <summary>
	/// Singleton template
	/// </summary>
	template<class _Tp>
	class Singleton
	{
	public:

		static _Tp* Instance()
		{
			static _Tp instance;
			return &instance;
		}
	protected:
		Singleton() {}
		virtual ~Singleton() {}
	private:
		Singleton(const Singleton& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
	};
}