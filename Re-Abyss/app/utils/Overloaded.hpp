#pragma once

namespace abyss
{
	/// <summary>
	/// 関数オブジェクトのオーバーロード
	/// </summary>
	template<class... Type>
	struct overloaded : Type...
	{
		using Type::operator()...;
	};
	template<class... Type>
	overloaded(Type ...)->overloaded<Type...>;
}