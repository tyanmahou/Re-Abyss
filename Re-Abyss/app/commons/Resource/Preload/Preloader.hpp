#pragma once
#include <abyss/commons/Resource/Preload/PreloadInfo.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/utils/Coro/Generator/Generator.hpp>

namespace abyss::Resource::Preload
{
    class Preloader
    {
    public:
        Preloader() = default;
        Preloader(const s3d::String& preloadName);

        Preloader(PreloadInfo&& info);

        /// <summary>
        /// プリロード
        /// </summary>
        /// <param name="assets"></param>
        void preload(const Assets* assets = Assets::Main());

        /// <summary>
        /// 進捗率を取得するジェネレータとしてロード
        /// </summary>
        /// <param name="assets"></param>
        /// <returns></returns>
        Coro::Generator<double> preloadProgress(const Assets* assets = Assets::Main()) const;

        size_t size() const
        {
            return m_info.size();
        }
    private:
        PreloadInfo m_info;
    };
}