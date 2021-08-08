#include "SelectFrameVM.hpp"
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/UI/SaveSelect/Param.hpp>
#include <abyss/views/util/Pivot/PivotUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SaveSelect::SelectFrame
{
    SelectFrameVM::SelectFrameVM():
        m_trashIcon(Resource::Assets::Main()->loadTexture(U"ui/SaveSelect/erase_user.png"))
    {}

    void SelectFrameVM::draw() const
    {
        const Vec2& size = Param::SelectFrame::Size;
        const Vec2 framePos = PivotUtil::FromCc(Param::SelectFrame::BasePos);
        const Vec2& tl = framePos - size / 2.0;
        const Vec2& selectSize = Param::SelectFrame::SelectSize;
        const Vec2& trashSize = Param::SelectFrame::TrashSize;

        // ユーザー番号
        for (int32 userId = 0; userId < Constants::UserNum; ++userId) {
            bool isSelect = m_selectUserId == userId;
            Vec2 pos = tl + Vec2{ selectSize.x * userId, 0 };
            Vec2 fSize = selectSize;

            if (!isSelect) {
                pos.y += Param::SelectFrame::SelectPosOffset;
                fSize.y -= Param::SelectFrame::SelectPosOffset;
            }
            {
                LineString ls({
                    pos + Vec2{0, fSize.y},
                    pos,
                    pos + Vec2{selectSize.x * Param::SelectFrame::SelectCornerRate.x, 0},
                    pos + Vec2{fSize.x, selectSize.y * Param::SelectFrame::SelectCornerRate.y},
                    pos + fSize
                    });
                if (m_selectUserId == userId) {
                    ls.draw(1.0);
                } else {
                    ls.drawClosed(1.0);
                }
                ls.draw();
            }
            FontAsset(FontName::SceneName)(U"{}"_fmt(userId + 1)).drawAt(pos + fSize / 2.0);
        }

        // ゴミ箱
        {
            bool isSelect = m_selectUserId == -1;

            Vec2 pos = tl + Vec2{ size.x - trashSize.x,  0 };
            Vec2 fSize = trashSize;

            if (!isSelect) {
                pos.y += Param::SelectFrame::SelectPosOffset;
                fSize.y -= Param::SelectFrame::SelectPosOffset;
            }
            LineString ls({
                    pos + Vec2{0, fSize.y},
                    pos,
                    pos + Vec2{fSize.x, 0},
                    pos + fSize,
                });
            if (m_selectUserId == -1) {
                ls.draw(1.0);
            } else {
                ls.drawClosed(1.0);
            }

            m_trashIcon.drawAt(pos + fSize / 2.0);
        }

        // 間のライン
        Line(
            tl + Vec2{ selectSize.x * Constants::UserNum, selectSize.y }, 
            tl + Vec2{ size.x - trashSize.x, selectSize.y }
        ).draw(1.0);
        // フレーム大枠
        LineString({ 
            tl + Vec2{ 0, selectSize.y }, 
            tl + Vec2{0, size.y},
            tl + size, 
            tl + Vec2{size.x, 0} + Vec2{ 0, selectSize.y }
        }).draw(1.0);
    }

}
