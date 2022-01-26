#include <abyss/views/util/MaskUtil/MaskUtil.hpp>
#include <abyss/commons/Constants.hpp>
#include <Siv3D.hpp>

namespace abyss
{
	MaskShader& MaskUtil::Instance()
	{
		static MaskShader shader{ Constants::AppResolution };
		return shader;
	}
}
