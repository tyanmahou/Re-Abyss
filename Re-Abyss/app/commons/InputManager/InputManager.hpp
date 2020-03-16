#pragma once
#include <memory>
#include <Siv3D/KeyGroup.hpp>
namespace abyss
{
    class InputManager
    {
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    public:
        InputManager();
        ~InputManager();

        const s3d::KeyGroup& jump() const;
        const s3d::KeyGroup& attack() const;

        const s3d::KeyGroup& up() const;
        const s3d::KeyGroup& down() const;
        const s3d::KeyGroup& right() const;
        const s3d::KeyGroup& left() const;

        const s3d::KeyGroup& start() const;

        const s3d::KeyGroup& A() const;
        const s3d::KeyGroup& B() const;

    };
}