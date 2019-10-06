#pragma once
#include <application/util/Observable.hpp>

namespace abyss
{
	class IStageDataStore;

	class StageObservable
	{
		Observable<void(IStageDataStore*)> m_onLoadStageFile;
	public:
		inline Observable<void(IStageDataStore*)>& onLoadStageFile()
		{
			return m_onLoadStageFile;
		}
	};
}