#pragma once
#include <abyss/utils/TOML/TOMLUtil.hpp>
#include <abyss/components/UI/Home/Top/Mode.hpp>

namespace abyss::UI::Home::Top
{
    struct ViewParam
    {
        struct IconParam
        {
            [[TOML_BIND(pos)]]
            s3d::Vec2 pos{};

            [[TOML_BIND(iconOffset)]]
            s3d::Vec2 iconOffset{};

            [[TOML_BIND(iconScale)]]
            double iconScale{1.0};

            [[TOML_BIND(text)]]
            s3d::String text{};

            [[TOML_BIND(textOffset)]]
            s3d::Vec2 textOffset{};

            [[TOML_BIND(scale)]]
            double scale{ 1.0 };

            [[TOML_BIND(isReverseColor)]]
            bool isReverseColor{ false };

            [[TOML_BIND(line0)]]
            s3d::Line line0{};

            [[TOML_BIND(line1)]]
            s3d::Line line1{};
        };

        [[TOML_BIND(ViewParam::Icons, "Icons")]]
        inline static s3d::Array<IconParam> Icons;

        static const IconParam& SeekIcon()
        {
            return GetIcon(Mode::Seek);
        }
        static const IconParam& GuildIcon()
        {
            return GetIcon(Mode::Guild);
        }
        static const IconParam& MaintIcon()
        {
            return GetIcon(Mode::Maint);
        }
        static const IconParam& MemoryIcon()
        {
            return GetIcon(Mode::Memory);
        }
        static const IconParam& CollectIcon()
        {
            return GetIcon(Mode::Collect);
        }
        static const IconParam& OptionIcon()
        {
            return GetIcon(Mode::Option);
        }
        static const IconParam& GetIcon(Mode mode)
        {
            return Icons[static_cast<size_t>(mode)];
        }

    };
}
