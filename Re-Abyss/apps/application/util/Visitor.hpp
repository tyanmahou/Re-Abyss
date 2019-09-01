#pragma once
#include<utility>
#include<memory>

namespace abyss
{
	/// <summary>
	///　関数オブジェクトのオーバーロード
	/// </summary>
	template<class... Type>
	struct overloaded : Type...
	{
		using Type::operator()...;
	};
	template<class... Type>
	overloaded(Type ...)->overloaded<Type...>;


	/// <summary>
	/// ビジター
	/// </summary>
	template<class... Accepter>
	class Visitor
	{
		template<class U>
		struct _ivisiter
		{
			virtual void visit(U&) const = 0;
			virtual ~_ivisiter() = default;
		};

		template<class Head, class... Tail>
		struct _base2 : _ivisiter<Head>, _base2<Tail...>
		{
			using _ivisiter<Head>::visit;
			using _base2<Tail...>::visit;
		};
		template<class Last>
		struct _base2<Last> : _ivisiter<Last>
		{
			using _ivisiter<Last>::visit;
		};
		struct _base : _base2<Accepter...>
		{
			using _base2<Accepter...>::visit;
		};

		template<class F, class Void, class Head, class... Tail>
		struct _func2 : _func2<F, Void, Tail...>
		{
			void visit(Head&) const override
			{};
			using _func2<F, Void, Tail...>::_func2;
			using _func2<F, Void, Tail...>::visit;
		};

		template<class F, class Head, class... Tail>
		struct _func2<
			F,
			decltype(std::declval<F>()(std::declval<Head&>())),
			Head, 
			Tail...
        > : _func2<F, void,Tail...>
		{
			void visit(Head& a) const override
			{
				return this->m_func(a);
			};
			using _func2<F, void, Tail...>::_func2;
			using _func2<F, void, Tail...>::visit;
		};

		template<class F, class Void, class Last>
		struct _func2<F, Void, Last> : _base
		{
			F m_func;
			_func2(F f) :
				m_func(f)
			{}
			void visit(Last&) const override
			{};
			using _base::visit;
		};

		template<class F, class Last>
		struct _func2<
			F, 
			decltype(std::declval<F>()(std::declval<Last&>())),
			Last
		> : _base
		{
			F m_func;
			_func2(F f) :
				m_func(f)
			{}
			void visit(Last& a) const override
			{
				return m_func(a);
			};
			using _base::visit;
		};

		template<class F>
		struct _func : _func2<F, void, Accepter...>
		{
			using _func2<F, void, Accepter...>::_func2;
			using _func2<F, void, Accepter...>::visit;
		};

		std::unique_ptr<_base> m_storage;
	public:

		template<class F>
		Visitor(F&& f) :
			m_storage(std::make_unique<_func<F>>(std::forward<F>(f)))
		{}

		template<class Arg>
		void visit(Arg&& arg) const
		{
			return m_storage->visit(std::forward<Arg>(arg));
		}
	};
}