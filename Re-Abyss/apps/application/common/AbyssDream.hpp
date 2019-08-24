#pragma once
#include"Application.hpp"

namespace abyss
{
	class AbyssDream : public Application
	{
	private:
		bool update() const override;
	public:
		AbyssDream();
		~AbyssDream();
	};
}
