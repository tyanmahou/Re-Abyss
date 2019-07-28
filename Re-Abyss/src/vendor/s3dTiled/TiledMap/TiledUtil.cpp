#include "TiledUtil.hpp"
#include<Siv3D/Color.hpp>
#include<Siv3D/Parse.hpp>

using namespace s3d;

namespace s3dTiled
{
	s3d::Color ParseTiledColor(const s3d::String& str)
	{
		bool noneAlpha = str.length <= 7;
		if (noneAlpha) {
			return Color(str);
		}
		String code = L"#" + str.substr(3, 6);
		Color ret(code);
		ret.setAlpha(Parse<uint32>(L"0x" + str.substr(1, 2)));
		return ret;
	}
}