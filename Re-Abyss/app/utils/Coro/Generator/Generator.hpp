#pragma once
#include <coroutine>

namespace abyss::Coro
{
	template<class Type>
	struct Generator
	{
		struct promise_type;
		using handle = std::coroutine_handle<promise_type>;

		struct promise_type
		{
			Type value;
			auto get_return_object() { return Generator{ handle::from_promise(*this) }; }
			auto  initial_suspend() { return std::suspend_never{}; }
			auto final_suspend() noexcept { return std::suspend_always{}; }
			auto yield_value(const Type& _value)
			{
				this->value = _value;
				return std::suspend_always{};
			}
			void unhandled_exception() { std::terminate(); }
			void return_void() {}
		};

		struct iterator_end {};
		struct iterator
		{
			using promise_type = Generator::promise_type;

			iterator(const Generator& other) :
				m_coro(other.coro)
			{}
			iterator(Generator&& other) :
				m_coro(std::move(other.coro))
			{
				other.coro = nullptr;
				m_needDestroy = true;
			}
			~iterator()
			{
				if (m_needDestroy && m_coro) {
					m_coro.destroy();
				}
			}
			iterator& operator++()
			{
				if (!m_coro.done()) {
					m_coro.resume();
				}
				return *this;
			}
			decltype(auto) operator*()
			{
				return m_coro.promise().value;
			}
			bool operator!=(const iterator_end&) const
			{
				return !m_coro.done();
			}
		private:
			handle m_coro;
			bool m_needDestroy = false;
		};
	public:
		iterator begin()const { return { *this }; }
		iterator_end end()const { return {}; }

		template<class Func>
		void each(Func func) const requires std::is_invocable_v<Func, Type>
		{
			for (auto&& elm : *this) {
				func(elm);
			}
		}
	public:
		explicit Generator(handle h)
			: coro(h)
		{}

		Generator(Generator const&) = delete;

		Generator(Generator&& rhs) noexcept
			: coro(std::move(rhs.coro))
		{
			rhs.coro = nullptr;
		}

		~Generator()
		{
			if (coro) {
				coro.destroy();
			}
		}
	private:
		handle coro;
	};
}