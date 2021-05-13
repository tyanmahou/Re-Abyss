#pragma once
#include <memory>
#include <abyss/services/Stage/base/IStageService.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class StageService : public IStageService
    {
	public:
    };

	struct StageServiceInstaller : emaject::IInstaller
	{
		void onBinding(emaject::Container* container) const override;
	};
}