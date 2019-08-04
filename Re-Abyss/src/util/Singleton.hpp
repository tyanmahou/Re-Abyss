#pragma once

namespace abyss
{
	///<summary>
	///シングルトンテンプレート
	///</summary>
	template<class _Tp>
	class Singleton
	{
	public:
		///<summary>
		///<para>概要：インスタンスを返す</para>
		///<para>返り値：シングルトンのclassのポインタ型</para>
		///</summary>
		static _Tp* Instance()
		{
			static _Tp instance;
			return &instance;
		}
	protected:
		Singleton() {}
		virtual ~Singleton() {}
	private:
		Singleton(const Singleton& other);
		Singleton& operator=(const Singleton& other);
	};

}