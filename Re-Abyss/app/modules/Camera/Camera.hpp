#pragma once
#include <functional>

#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Camera/CameraModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
	class ICameraTarget;
	class CameraTargetCtrl;
	class SnapshotView;

    class Camera
    {
	private:
		Manager* m_pManager;
		std::unique_ptr<CameraModel> m_camera;
		std::unique_ptr<CameraTargetCtrl> m_target;
		std::unique_ptr<Quake> m_quake;
		std::unique_ptr<SnapshotView> m_snapshot;
	public:
		Camera();
		~Camera();

		void setManager(Manager* pManager);

		void update(double dt);

		/// <summary>
		/// カメラ座標をセット
		/// </summary>
		/// <param name="cameraPos"></param>
		void setPos(const s3d::Vec2& cameraPos) const;

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
		/// 地震開始
		/// </summary>
		/// <param name="maxOffset"></param>
		/// <param name="timeSec"></param>
		Ref<QuakeModel> startQuake(double maxOffset = 5.0, double timeSec = -1.0);

		/// <summary>
		/// 地震停止
		/// </summary>		
		void stopQuake();

		/// <summary>
		/// 地震中か
		/// </summary>	
		bool isQuake() const;

		template<class T>
		bool inScreen(const T& shape)const
		{
			return this->screenRegion().intersects(shape);
		}

		/// <summary>
		/// View作成
		/// </summary>
		/// <returns></returns>
		CameraView createView() const;

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

		SnapshotView* getSnapshot() const;
    };
}
