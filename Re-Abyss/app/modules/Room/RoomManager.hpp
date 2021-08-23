#pragma once
#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/modules/Room/IRoomMoveCallback.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Room
{
    class RoomManager
    {
        class CameraFix;
    public:
        RoomManager();

        void init();

        void setManager(Manager* pManager)
        {
            m_pManager = pManager;
        }
        bool isOutOfRoomDeath(const s3d::Vec2& pos, double margin = 0.0) const;

        /// <summary>
        /// 現在の部屋設定
        /// </summary>
        /// <returns></returns>
        void setRoom(const RoomModel& room)
        {
            m_currentRoom = room;
        }

        /// <summary>
        /// 現在の部屋取得
        /// </summary>
        /// <returns></returns>
        const RoomModel& currentRoom() const
        {
            return m_currentRoom;
        }

        /// <summary>
        /// 次の部屋設定
        /// </summary>
        /// <returns></returns>
        void setNextRoom(const s3d::Optional<RoomModel>& room)
        {
            m_nextRoom = room;
        }

        /// <summary>
        /// 次の部屋取得
        /// </summary>
        /// <returns></returns>
        const s3d::Optional<RoomModel>& nextRoom() const
        {
            return m_nextRoom;
        }

        /// <summary>
        /// 次の部屋に移動できるか
        /// </summary>
        /// <param name="pos"></param>
        /// <returns></returns>
        bool canNextRoom(const s3d::Vec2& pos) const;

        /// <summary>
        /// 次の部屋を現在の部屋に適用する
        /// </summary>
        /// <returns></returns>
        bool applyNextRoom();

        /// <summary>
        /// ルーム壁補正
        /// </summary>
        /// <param name="pos"></param>
        /// <returns></returns>
        s3d::Vec2 fixPos(const s3d::Vec2& pos) const;

        /// <summary>
        /// ルームに入っているか
        /// </summary>
        template<class T>
        bool isInRoom(const T& shape)const
        {
            return m_currentRoom.getRegion().intersects(shape);
        }

        void drawDeathLine() const;

        void addCallback(std::shared_ptr<IRoomMoveCallback> callback);
        void onCheckOut();
        void onCheckIn();
    private:
        Manager* m_pManager;
        RoomModel m_currentRoom;
        s3d::Optional<RoomModel> m_nextRoom;

        std::shared_ptr<CameraFix> m_cameraFix;

        s3d::Array<Ref<IRoomMoveCallback>> m_callbacks;
    };
}