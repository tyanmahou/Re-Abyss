#pragma once
#include <utility>
#include <memory>
#include <type_traits>
#include <abyss/utils/Overloaded.hpp>

namespace abyss
{
	/// <summary>
	/// ビジター
	/// </summary>
	template<class... Accepter>
	class Visitor
	{
		template<class U>
		struct _ivisitor
		{
			virtual bool visit(U&) const = 0;
			virtual ~_ivisitor() = default;
		};

		template<class... Is>
		struct _base2 : Is...
		{
			using Is::visit...;
		};
		struct _base : _base2<_ivisitor<Accepter>...>
		{
			using _base2<_ivisitor<Accepter>...>::visit;
		};

		template<class F, class Head, class... Tail>
		struct _func2 : _func2<F, Tail...>
		{
			bool visit([[maybe_unused]] Head& a) const override
			{
				static_assert(sizeof(Head) >= 1);

				if constexpr (std::is_invocable_v<F, Head&>) {
					this->m_func(a);
					return true;
				} else {
					return false;
				}
			};
			using _func2<F, Tail...>::_func2;
			using _func2<F, Tail...>::visit;
		};

		template<class F, class Last>
		struct _func2<F, Last> : _base
		{
			F m_func;
			_func2(F f) :
				m_func(f)
			{}
			bool visit([[maybe_unused]] Last& a) const override
			{
				static_assert(sizeof(Last) >= 1);

				if constexpr (std::is_invocable_v<F, Last&>) {
					m_func(a);
					return true;
				} else {
					return false;
				}
			};
			using _base::visit;
		};

		template<class F>
		struct _func : _func2<F, Accepter...>
		{
			using _func2<F, Accepter...>::_func2;
			using _func2<F, Accepter...>::visit;
		};

		std::unique_ptr<_base> m_storage;
	public:
		Visitor() = default;
		template<class F>
		Visitor(F&& f) :
			m_storage(std::make_unique<_func<F>>(std::forward<F>(f)))
		{}

		template<class Arg>
		bool visit(Arg&& arg) const
		{
			return m_storage->visit(std::forward<Arg>(arg));
		}

		Visitor& operator =(Visitor&& other) noexcept
		{
			m_storage = std::move(other.m_storage);
			return *this;
		}
	};

	template<class ...Accepter>
	using ConstVisitor = Visitor<const Accepter...>;
}