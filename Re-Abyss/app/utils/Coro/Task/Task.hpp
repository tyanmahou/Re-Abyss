#pragma once
#include <coroutine>
#include <memory>

namespace abyss::Coro
{
	template<class T>
	struct Task;

	namespace detail
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
			using Task = Task<T>;

			static Task get_return_object_on_allocation_failure()
			{
				return Task{ nullptr };
			}
			auto get_return_object() { return Task{ Task::Handle::from_promise(*this) }; }
			auto initial_suspend() { return std::suspend_always{}; }
			auto final_suspend() noexcept { return std::suspend_always{}; }
			void unhandled_exception() { std::terminate(); }

			auto yield_value(const detail::Yield& _yield)
			{
				struct Awaiter
				{
					bool await_ready() const noexcept
					{
						return ready;
					}

					void await_suspend(std::coroutine_handle<>) {}
					void await_resume() {}

					bool ready = false;
				};
				if (_yield.count == 0) {
					return Awaiter{ true };
				}
				--(this->yield = _yield).count;
				return Awaiter{ false };
			}
			detail::Yield yield{ 0 };
			NextTaskHandler next;
		};

		template<class T>
		struct IsTaskPromise :std::false_type {};
		template<class U>
		struct IsTaskPromise<detail::PromiseType<U>> : std::true_type {};

		template<class T>
		concept TaskPromiseType = IsTaskPromise<T>::value;

		template<class T>
		concept TaskHandleType = requires(T handle)
		{
			requires TaskPromiseType<std::decay_t<decltype(handle.promise())>>;
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
			template<TaskHandleType U>
			void await_suspend(U handle) const
			{
				handle.promise().next = task;
			}
		};
	}

	/// <summary>
	/// タスク
	/// </summary>
	template <class T = void>
	struct Task
	{
		using promise_type = detail::PromiseType<T>;
		using Handle = std::coroutine_handle<promise_type>;

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
}