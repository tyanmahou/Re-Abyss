#pragma once
#include <functional>

#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Camera/CameraParam.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
	class ICameraTarget;
	class CameraTargetCtrl;
    class CameraErpCtrl;
	class ICameraFix;
	class CameraFixCtrl;
	class SnapshotView;

    class Camera
    {
	private:
		Manager* m_pManager = nullptr;
        CameraParam m_camera;
		std::unique_ptr<CameraTargetCtrl> m_target;
		std::unique_ptr<CameraFixCtrl> m_fixCtrl;
        std::unique_ptr<CameraErpCtrl> m_erpCtrl;
        std::unique_ptr<Quake> m_quake;
		std::unique_ptr<SnapshotView> m_snapshot;
	public:
		Camera();
		~Camera();

		void setManager(Manager* pManager);

		void update(double dt);

		/// <summary>
		/// カメラ座標取得
		/// </summary>
		/// <returns></returns>
		const s3d::Vec2& getPos() const;

		/// <summary>
		/// カメラターゲット追加
		/// </summary>
		/// <param name="target"></param>
		void addTarget(const std::shared_ptr<ICameraTarget>& target);

		/// <summary>
		/// カメラ補正追加
		/// </summary>
		/// <param name="target"></param>
		void addCameraFix(const std::shared_ptr<ICameraFix>& fix);

		/// <summary>
		/// カメラ補正削除
		/// </summary>
		/// <param name="target"></param>
		void removeCameraFix(const std::shared_ptr<ICameraFix>& fix);

		/// <summary>
		/// 地震開始
		/// </summary>
		/// <param name="maxOffset"></param>
		/// <param name="timeSec"></param>
		Ref<QuakeEpicenter> startQuake(double maxOffset = 5.0, double timeSec = -1.0);

		/// <summary>
		/// 地震停止
		/// </summary>		
		void stopQuake();

		/// <summary>
		/// 地震中か
		/// </summary>	
		bool isQuake() const;

        const s3d::Vec2& getQuakeOffset() const;

		/// <summary>
		/// ズームスケール取得
		/// </summary>
		/// <returns></returns>
		double getZoomScale() const;

		template<class T>
		bool inScreen(const T& shape)const
		{
			return this->screenRegion().intersects(shape);
		}

		/// <summary>
		/// スクリーンの範囲取得
		/// </summary>
		/// <returns></returns>
		s3d::RectF screenRegion() const;

		/// <summary>
		/// 座標をカメラ行列で変換する
		/// </summary>
		/// <param name="pos"></param>
		/// <returns></returns>
		s3d::Vec2 transform(const s3d::Vec2& pos) const;

        const CameraParam* getViewParam() const
        {
            return &m_camera;
        }
		SnapshotView* getSnapshot() const;
    };
}
