#include "Cursor.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/Cycle/Title/Cursor/CursorVM.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::Title::Cursor
{
    Cursor::Mode& operator ++(Cursor::Mode& mode)
    {
        mode = (mode == Cursor::Mode::Max) ? 
            Cursor::Mode::Min : 
            static_cast<Cursor::Mode>(static_cast<int>(mode) + 1);
        return mode;
    }
    Cursor::Mode& operator --(Cursor::Mode& mode)
    {
        mode = (mode == Cursor::Mode::Min) ?
            Cursor::Mode::Max :
            static_cast<Cursor::Mode>(static_cast<int>(mode) - 1);
        return mode;
    }
    Cursor::Cursor():
        m_view(std::make_unique<CursorVM>())
    {}
    Cursor::~Cursor()
    {}
    void Cursor::update()
    {
        // カーソルを動かす
        if (InputManager::Up.down()) {
            --m_mode;
        } else if (InputManager::Down.down()) {
            ++m_mode;
        }
    }

    void Cursor::draw() const
    {
        struct CursorViewParam
        {
            String name;
            double posY;
        };
        const static std::array<CursorViewParam, static_cast<size_t>(Mode::Term)> viewParams
        {
            CursorViewParam{U"GAME START", 360.0},
            CursorViewParam{U"Exit", 410.0},
        };
        size_t modeIndex = static_cast<size_t>(m_mode);
        m_view->setPos({ 350, viewParams[modeIndex].posY }).draw();

        for (const auto& param : viewParams) {
            FontAsset(U"titleSelect")(param.name).drawAt(480, param.posY);
        }
    }
}
