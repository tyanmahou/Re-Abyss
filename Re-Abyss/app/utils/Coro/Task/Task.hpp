#pragma once
#include <coroutine>
#include <memory>

namespace abyss::Coro
{
	/// <summary>
	/// Yield
	/// </summary>
	/// <returns></returns>
	struct Yield
	{
		constexpr Yield() :
			count(1)
		{}

		constexpr Yield(std::uint32_t _count) :
			count(_count)
		{}

		std::uint32_t count;
	};

	namespace detail
	{
		template<class Handle>
		concept YieldAwaitableHandle = requires(Handle handle)
		{
			requires std::same_as<Yield, decltype(handle.promise().yield)>;
			requires std::convertible_to<Handle, std::coroutine_handle<>>;
		};

		struct YieldAwaiter
		{
			bool await_ready() const noexcept
			{
				return yield.count == 0;
			}

			template<YieldAwaitableHandle Handle>
			void await_suspend(Handle handle)
			{
				--(handle.promise().yield = yield).count;
			}
			void await_resume() {}

			Yield yield;
		};
	}

	inline auto operator co_await(const Yield& yield)
	{
		return detail::YieldAwaiter{ yield };
	}

	namespace detail
	{
		template<class T>
		struct PromiseType;

		template<class T>
		struct TaskAwaiter;
	}

	/// <summary>
	/// タスク
	/// </summary>
	template <class T = void>
	struct Task
	{
		using promise_type = detail::PromiseType<T>;
		using Handle = std::coroutine_handle<promise_type>;
	public:
		Task(Handle h) :
			coro(h)
		{}

		Task(Task const&) = delete;

		Task(Task&& rhs) noexcept
			: coro(std::move(rhs.coro))
		{
			rhs.coro = nullptr;
		}

		~Task()
		{
			if (coro) {
				coro.destroy();
			}
		}
	public:
		/// <summary>
		/// 再開
		/// </summary>
		/// <returns></returns>
		bool moveNext() const
		{
			if (!coro) {
				return false;
			}
			if (coro.done()) {
				return false;
			}
			// Yield
			{
				auto& yield = coro.promise().yield;
				if (yield.count > 0 && yield.count-- > 0) {
					// カウンタが残ってるなら
					return true;
				}
			}
			// 割り込み別タスク
			{
				auto& next = coro.promise().next;
				if (next) {

					if (!next.moveNext()) {
						next.clear();
					} else {
						return true;
					}
				}
			}
			coro.resume();
			return !coro.done();
		}

		/// <summary>
		/// 完了したか
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] bool isDone()const
		{
			if (!coro) {
				return true;
			}
			return coro.done();
		}

		/// <summary>
		/// 取得
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] decltype(auto) get() const
		{
			return coro.promise().getValue();
		}

	private:
		Handle coro;
	};

	template<class T>
	auto operator co_await(Task<T> other)
	{
		return detail::TaskAwaiter{ std::move(other) };
	}

	template<class T, class U>
	[[nodiscard]] Task<void> operator & (Task<T> a, Task<U> b)
	{
		while (true) {
			a.moveNext();
			b.moveNext();

			if (a.isDone() && b.isDone()) {
				co_return;
			}

			co_yield{};
		}
	}

	template<class T, class U>
	[[nodiscard]] Task<void> operator | (Task<T> a, Task<U> b)
	{
		while (true) {
			a.moveNext();
			b.moveNext();

			if (a.isDone() || b.isDone()) {
				co_return;
			}

			co_yield{};
		}
	}

	template<class T, class U>
	[[nodiscard]] Task<U> operator + (Task<T> a, Task<U> b)
	{
		while (a.moveNext()) {
			co_yield{};
		}
		while (b.moveNext()) {
			co_yield{};
		}
		co_return b.get();
	}
	namespace detail
	{
		/// <summary>
		/// NextTaskHandler
		/// </summary>
		struct NextTaskHandler
		{
		public:
			NextTaskHandler() = default;
			template<class T>
			NextTaskHandler(const Task<T>& task) :
				m_holder(std::make_unique<Holder<T>>(task))
			{}

			bool moveNext() const
			{
				return m_holder->moveNext();
			}
			void clear()
			{
				m_holder = nullptr;
			}
			explicit operator bool() const
			{
				return static_cast<bool>(m_holder);
			}
		private:
			struct IHolder
			{
				virtual ~IHolder() = default;
				virtual bool moveNext() const = 0;
			};
			template<class T>
			struct Holder final : IHolder
			{
				Holder(const Task<T>& task) :
					m_task(task)
				{}
				bool moveNext() const override
				{
					return m_task.moveNext();
				}
			private:
				const Task<T>& m_task;
			};
			std::unique_ptr<IHolder> m_holder;
		};

		/// <summary>
		/// Promise
		/// </summary>
		template<class T>
		struct PromiseValue
		{
			void return_value(const T& _value)
			{
				this->value = _value;
			}

			const T& getValue() const
			{
				return value;
			}
			T value;
		};

		// void特殊化
		template<>
		struct PromiseValue<void>
		{
			void return_void() {}

			void getValue() const
			{}
		};

		template<class T>
		struct PromiseType : PromiseValue<T>
		{
			using TaskType = Task<T>;

			static TaskType get_return_object_on_allocation_failure()
			{
				return TaskType{ nullptr };
			}
			auto get_return_object() { return TaskType{ TaskType::Handle::from_promise(*this) }; }
			auto initial_suspend() { return std::suspend_always{}; }
			auto final_suspend() noexcept { return std::suspend_always{}; }
			void unhandled_exception() { std::terminate(); }

			auto yield_value(const Yield& _yield)
			{
				return operator co_await(_yield);
			}
			Yield yield{ 0 };
			NextTaskHandler next;
		};

		template<class Handle>
		concept TaskAwaitableHandle = requires(Handle handle)
		{
			requires std::same_as<NextTaskHandler, decltype(handle.promise().next)>;
			requires std::convertible_to<Handle, std::coroutine_handle<>>;
		};

		/// <summary>
		/// Awaiter
		/// </summary>
		template<class T>
		struct TaskAwaiter
		{
			Task<T> task;

			bool await_ready() const
			{
				return !task.moveNext();
			}
			decltype(auto) await_resume() const
			{
				return task.get();
			}
			template<TaskAwaitableHandle Handle>
			void await_suspend(Handle handle) const
			{
				handle.promise().next = task;
			}
		};
	}
}