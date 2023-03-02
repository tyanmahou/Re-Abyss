#pragma once
#include <abyss/commons/Resource/Msg/Manager.hpp>
#include <abyss/values/UserPlayMode.hpp>
#include <abyss/values/Adv/CharaKind.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>

namespace abyss::MsgUtil
{
    struct Text
    {
    public:
        constexpr Text(s3d::StringView category, s3d::StringView key) :
            m_label{ category, key }
        {}
        constexpr Text(const Resource::Msg::Label& label) :
            m_label(label)
        {}
        const s3d::String& get() const
        {
            return Resource::Msg::Manager::Get(m_label);
        }
        const s3d::String& operator()() const
        {
            return get();
        }

        friend void Formatter(s3d::FormatData& formatData, const Text& value)
        {
            formatData.string.append(value.get());
        }
    private:
        Resource::Msg::Label m_label;
    };

    /// =============================
    /// Common
    /// =============================
    inline constexpr Text Common(s3d::StringView key)
    {
        return { U"Common", key };
    }
    inline constexpr Text Decide = Common(U"Decide");
    inline constexpr Text Cancel = Common(U"Cancel");
    inline constexpr Text Yes = Common(U"Yes");
    inline constexpr Text No = Common(U"No");

    /// =============================
    /// Title
    /// =============================
    inline constexpr Text Title(s3d::StringView key)
    {
        return { U"Title", key };
    }
    inline constexpr Text Title_GameStart = Title(U"GameStart");
    inline constexpr Text Title_Exit = Title(U"Exit");

    /// =============================
    /// SaveSelect
    /// =============================
    inline constexpr Text SaveSlect(s3d::StringView key)
    {
        return { U"SaveSelect", key };
    }
    inline constexpr Text SaveSlect_Mode_GameStart = SaveSlect(U"Mode_GameStart");
    inline constexpr Text SaveSlect_Mode_Delete = SaveSlect(U"Mode_Delete");
    inline constexpr Text SaveSlect_CreateUser_Title = SaveSlect(U"CreateUser_Title");
    inline constexpr Text SaveSlect_EraseUser_Title = SaveSlect(U"EraseUser_Title");

    inline constexpr Text Name(UserPlayMode value)
    {
        if (value == UserPlayMode::Normal) {
            return Common(U"UserPlayMode_Normal");
        }
        if (value == UserPlayMode::Hard) {
            return Common(U"UserPlayMode_Hard");
        }
        return Common(U"UserPlayMode_Normal");
    }

    /// =============================
    /// Chara
    /// =============================
    inline constexpr Text CharaName(Adv::CharaKind value)
    {
        return { U"Chara", Enum::ToStr(value) };
    }
}
template<>
struct SIV3D_HIDDEN fmt::formatter<abyss::MsgUtil::Text, s3d::char32>
{
    std::u32string tag;

    auto parse(basic_format_parse_context<s3d::char32>& ctx)
    {
        return s3d::detail::GetFormatTag(tag, ctx);
    }

    template <class FormatContext>
    auto format(const abyss::MsgUtil::Text& value, FormatContext& ctx)
    {
        if (tag.empty())
        {
            return format_to(ctx.out(), U"{}", value.get());
        } else
        {
            const std::u32string format = U"{:" + tag + U"}";
            return format_to(ctx.out(), format, value.get());
        }
    }
};
