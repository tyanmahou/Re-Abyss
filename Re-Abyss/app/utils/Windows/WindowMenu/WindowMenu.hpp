#pragma once
#include <memory>
#include <functional>
#include <Siv3D/Array.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Windows
{
    class MenuItem;

    /// <summary>
    /// ウィンドウメニュー
    /// </summary>
    class WindowMenu
    {
        class Impl;
    public:
        static WindowMenu& Main();
    public:
        WindowMenu();

        /// <summary>
        /// 現在表示されているか
        /// </summary>
        /// <returns></returns>
        bool isShow() const;

        /// <summary>
        /// 表示する
        /// </summary>
        /// <param name="show"></param>
        void show(bool show);

        /// <summary>
        /// アイテムを追加
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        MenuItem createItem(const s3d::String& name);

        /// <summary>
        /// ポップメニューを追加
        /// </summary>
        /// <param name="name"></param>
        /// <param name="setup"></param>
        /// <returns></returns>
        MenuItem createPopup(const s3d::String& name, std::function<void(MenuItem)> setup);

    private:
        std::shared_ptr<Impl> m_pImpl;
    };

    /// <summary>
    /// メニューアイテム
    /// </summary>
    class MenuItem
    {
    public:
        class Impl;

        using SubMenu = MenuItem;
    public:
        MenuItem() = default;

        MenuItem(std::shared_ptr<Impl> pImpl);

        /// <summary>
        /// アイテムを追加
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        SubMenu createItem(const s3d::String& name);

        /// <summary>
        /// ボタンを設定
        /// </summary>
        /// <param name="callback"></param>
        /// <returns></returns>
        MenuItem& setButton(std::function<void()> callback);

        /// <summary>
        /// ボタンを追加
        /// </summary>
        /// <param name="name"></param>
        /// <param name="callback"></param>
        /// <returns></returns>
        SubMenu createButton(const s3d::String& name, std::function<void()> callback);

        /// <summary>
        /// ボタンを設定
        /// </summary>
        /// <param name="callback"></param>
        /// <returns></returns>
        MenuItem& setCheckButton(std::function<void(bool)> callback, bool isChecked = false);

        /// <summary>
        /// チェックボタンを追加
        /// </summary>
        /// <param name="name"></param>
        /// <param name="callback"></param>
        /// <param name="isChecked"></param>
        /// <returns></returns>
        SubMenu createCheckButton(const s3d::String& name, std::function<void(bool)> callback, bool isChecked = false);

        /// <summary>
        /// ラジオボタンを追加
        /// </summary>
        /// <param name="name"></param>
        /// <param name="callback"></param>
        /// <param name="checkIndex"></param>
        /// <returns></returns>
        s3d::Array<SubMenu> createRadioButton(const s3d::Array<s3d::String>& name, std::function<void(size_t)> callback, size_t checkIndex = 0);

        /// <summary>
        /// ポップアップメニューを追加
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        SubMenu createPopup(const s3d::String& name, std::function<void(SubMenu)> setup);

        /// <summary>
        /// セパレーターを追加
        /// </summary>
        /// <returns></returns>
        void createSeperator();

        /// <summary>
        /// 有効無効
        /// </summary>
        /// <param name="enabled"></param>
        /// <returns></returns>
        bool enabled() const;

        /// <summary>
        /// 有効無効を設定
        /// </summary>
        /// <param name="enabled"></param>
        /// <returns></returns>
        void setEnabled(bool enabled);

        /// <summary>
        /// 名前を取得
        /// </summary>
        /// <returns></returns>
        s3d::String name() const;

        /// <summary>
        /// 使用可能か
        /// </summary>
        /// <returns></returns>
        explicit operator bool() const;

        /// <summary>
        /// リリース
        /// </summary>
        void release() const;
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}
