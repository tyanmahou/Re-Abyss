#pragma once

#include <application/util/Observable.hpp>
namespace abyss
{
	class CameraUseCase;


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
