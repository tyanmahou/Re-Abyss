#pragma once
#include <memory>
#include <unordered_map>
#include <utility>
#include <Siv3D/String.hpp>

namespace abyss
{
    namespace reflection::detail
    {
        inline constexpr size_t AUTO_BIND_MAX_LINES = 700;

        template<size_t Line>
        struct AutoBindLine
        {
        };

        template<class Type, size_t LineNum>
        concept AutoBindCallable = requires(Type * t, AutoBindLine<LineNum> l)
        {
            t | l;
        };

        template <auto... As, auto... Bs>
        constexpr std::index_sequence<As..., Bs...> operator+(std::index_sequence<As...>, std::index_sequence<Bs...>)
        {
            return {};
        }
        template <size_t LineNum, class Type>
        constexpr auto LineNumToSeq()
        {
            if constexpr (AutoBindCallable<Type, LineNum>) {
                return std::index_sequence<LineNum>{};
            } else {
                return std::index_sequence<>{};
            }
        }
        template <class Type, size_t ...Seq>
        constexpr auto LineSeq(std::index_sequence<Seq...>)
        {
            return (LineNumToSeq<Seq, Type>() + ...);
        }

        template <class Type>
        struct AutoBinder
        {
            template<size_t LineNum>
            void bind(Type* p)
            {
                p | AutoBindLine<LineNum>{};
            }
            template<size_t ...Seq>
            void operator()(Type* p, std::index_sequence<Seq...>)
            {
                (this->bind<Seq>(p), ...);
            }
        };
    }

    template<class Type>
    struct Reflection
    {
        template<class FuncPointerType>
        Reflection(const s3d::String& funcName, FuncPointerType func)
        {
            FuncInternal<FuncPointerType>(funcName) = func;
        }

        template<class FuncPointerType>
        static FuncPointerType Find(const s3d::String& funcName)
        {
            Initilize();
            return FuncInternal<FuncPointerType>(funcName);
        }
    private:
        static bool Initilize()
        {
            static const bool initilize = [] {
                using namespace reflection::detail;
                Type* p = nullptr;
                AutoBinder<Type>{}(p, LineSeq<Type>(std::make_index_sequence<AUTO_BIND_MAX_LINES>()));
                return true;
            }();
            return initilize;
        }
        template<class FuncPointerType>
        static FuncPointerType& FuncInternal(const s3d::String& funcName)
        {
            constinit static std::unique_ptr<std::unordered_map<s3d::String, FuncPointerType>> funcs = nullptr;
            if (!funcs) {
                funcs = std::make_unique<std::unordered_map<s3d::String, FuncPointerType>>();
            }
            return (*funcs)[funcName];
        }
    };

}

#define REFLECTION2(funcName, line)\
]] friend void operator | (auto* a, ::abyss::reflection::detail::AutoBindLine<line>)\
{\
    static_assert(line < ::abyss::reflection::detail::AUTO_BIND_MAX_LINES);\
    using this_type = std::decay_t<decltype(*a)>;\
    static const ::abyss::Reflection<this_type> regist{ U#funcName, &this_type::funcName };\
}[[

#define REFLECTION(funcName) REFLECTION2(funcName, __LINE__)