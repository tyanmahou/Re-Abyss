#include <abyss/views/UI/Home/Top/TopView.hpp>
#include <abyss/views/UI/Home/Top/ModeIconVM.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/SeekThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/GuildThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/MaintThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/MemoryThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/CollectThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/OptionThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeSelectLineVM.hpp>

#include <abyss/params/UI/Home/Top/ViewParam.hpp>

namespace abyss::UI::Home::Top
{
    TopView::TopView():
        m_icons(std::make_unique<ModeIconVM[]>(IconSize)),
        m_selectLine(std::make_unique<ModeSelectLineVM>())
    {
        for (size_t index = 0; index < IconSize; ++index) {
            const auto& param = ViewParam::Icons[index];
            m_icons[index]
                .setPos(param.pos)
                .setScale(param.scale)
                .setReverseColor(param.isReverseColor)
                .setLocked(true)
                ;
        }
        m_icons[IconSeek].setThumbnail<SeekThumb>();
        m_icons[IconGuild].setThumbnail<GuildThumb>();
        m_icons[IconMaint].setThumbnail<MaintThumb>();
        m_icons[IconMemory].setThumbnail<MemoryThumb>();
        m_icons[IconCollect].setThumbnail<CollectThumb>();
        m_icons[IconOption].setThumbnail<OptionThumb>();
    }
    TopView::~TopView()
    {}
    void TopView::draw() const
    {
        s3d::Scene::Rect().draw(Color(31, 27, 48));
        const size_t modeIndex = static_cast<size_t>(m_mode);
        // 選択線
        {
            const auto& param = ViewParam::Icons[modeIndex];
            m_selectLine
                ->setTime(m_time)
                .setPos(param.pos)
                .setScale(param.scale)
                .setText(param.text)
                .setTextOffset(param.textOffset)
                .setLine(param.line0, param.line1)
                .setLocked(m_isLocked[modeIndex])
                .draw();
                ;
        }
        struct InAnimInfo
        {
            double animStartRate;
            double animRateLength;
            double offsetX;
        };
        constexpr double inAnimeStartOffs = 0.8 / 6.0;
        constexpr auto animeEasing = [](double x) constexpr {
            return x * inAnimeStartOffs;
        };
        constexpr double animRateLength = 1.0 - animeEasing(5.0);
        constexpr double animRateLengthDelayRate = 0.6;
        constexpr auto animeLengthEasing = [](double x) constexpr {
            return animRateLength + inAnimeStartOffs * animRateLengthDelayRate * x;
        };
        std::array<InAnimInfo, IconSize> inAnimInfo{
            InAnimInfo{animeEasing(5.0), animeLengthEasing(0.0), -50},
            InAnimInfo{animeEasing(2.0), animeLengthEasing(3.0), -70},
            InAnimInfo{animeEasing(1.0), animeLengthEasing(4.0), -40},
            InAnimInfo{animeEasing(3.0), animeLengthEasing(2.0), -60},
            InAnimInfo{animeEasing(4.0), animeLengthEasing(1.0), -90},
            InAnimInfo{animeEasing(0.0), animeLengthEasing(5.0), -80},
        };
        for (size_t index = 0; index < IconSize; ++index) {
            double rate = s3d::Saturate((m_inAnimeRate - inAnimInfo[index].animStartRate) / inAnimInfo[index].animRateLength);
            s3d::Transformer2D t2d(Mat3x2::Translate({s3d::Math::Lerp(inAnimInfo[index].offsetX, 0, rate), 0}));
            s3d::ScopedColorMul2D colorMul(ColorF(1, rate));
            m_icons[index]
                .setTime(m_time)
                .setLocked(m_isLocked[index])
                .setSelected(m_inAnimeRate >= 1.0 && index == modeIndex)
                .draw();
        }
    }
}
