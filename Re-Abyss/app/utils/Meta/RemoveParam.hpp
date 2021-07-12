#pragma once

namespace abyss::Meta
{
    namespace detail
    {
        template<template<class...>class MetaFunc, class T, class U>
        struct remove_param_merge
        {
        };
        template<template<class...>class MetaFunc, class T, class... Us>
        struct remove_param_merge<MetaFunc, T, MetaFunc<Us...>>
        {
            using type = MetaFunc<T, Us...>;
        };

        template<template<class...>class MetaFunc, class T, class U>
        using remove_param_merge_t = remove_param_merge<MetaFunc, T, U>::type;

        template<template<class...>class MetaFunc, class Ignore, class Head, class... Tail >
        struct remove_param
        {
            using type = remove_param_merge_t<
                MetaFunc,
                Head,
                typename remove_param<MetaFunc, Ignore, Tail...>::type
            >;
        };
        template<template<class...>class MetaFunc, class Ignore, class Head>
        struct remove_param<MetaFunc, Ignore, Head>
        {
            using type = MetaFunc<Head>;
        };
        template<template<class...>class MetaFunc, class Ignore>
        struct remove_param<MetaFunc, Ignore, Ignore>
        {
            using type = MetaFunc<>;
        };
        template<template<class...>class MetaFunc, class Ignore, class... Tail>
        struct remove_param<MetaFunc, Ignore, Ignore, Tail...>
        {
            using type = typename remove_param<
                MetaFunc,
                Ignore,
                Tail...
            >::type;
        };
    }

    template<template<class...>class MetaFunc, class Ignore, class... Args>
    using remove_param_t = detail::remove_param<MetaFunc, Ignore, Args...>::type;

    template<template<class...>class MetaFunc, class... Args>
    using remove_param_void_t = remove_param_t<MetaFunc, void, Args...>;
}