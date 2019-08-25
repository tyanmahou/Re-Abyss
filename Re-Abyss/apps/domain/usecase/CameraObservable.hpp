#pragma once
#include <functional>
#include <memory>
#include <Siv3D/Fwd.hpp>
namespace abyss
{
	class CameraUseCase;

	template<class T>
	class Observable;

	template<class Ret, class... Args>
	class Observable<Ret(Args...)>
	{
		std::function<Ret(Args...)> m_event;

	public:
		void subscribe(std::function<Ret(Args...)> callback)
		{
			m_event = callback;
		}
		template<class... T>
		s3d::Optional<Ret> notify(T&& ... args) const
		{
			if (m_event) {
				return m_event(std::forward<T>(args)...);
			}
			return s3d::none;
		}
		template<class... T>
		s3d::Optional<Ret> operator()(T&& ... args) const
		{
			return this->notify(std::forward<T>(args)...);
		}
	};
	template<class... Args>
	class Observable<void(Args...)>
	{
		std::function<void(Args...)> m_event;

	public:
		void subscribe(std::function<void(Args...)> callback)
		{
			m_event = callback;
		}

		template<class... T>
		void notify(T&& ... args)const
		{
			if (m_event) {
				m_event(std::forward<T>(args)...);
			}
		}
		template<class... T>
		void operator()(T&& ... args) const
		{
			return this->notify(std::forward<T>(args)...);
		}
	};
	class CamraObservable
	{
		Observable<void(CameraUseCase*)> m_onNextRoom;
	public:
		inline Observable<void(CameraUseCase*)>& onNextRoom()
		{
			return m_onNextRoom;
		}
	};
}
