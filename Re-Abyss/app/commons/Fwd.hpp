#pragma once

/// <summary>
///  前方宣言
/// </summary>

namespace abyss
{
	class IComponent;

	/// <summary>
	/// Modules
	/// </summary>
	class System;
	class Manager;
	class GlobalTime;
	class Camera;
	class Quake;
	class ICameraWork;
	class World;
	class Events;
	class Stage;
	class StageData;
	class Light;
	class Decor;
	class DecorGraphicsManager;
	class BackGround;
	class Effects;
	class Sound;
	class UI;
	class Cron;
	class Save;
	class SaveData;
	class Master;
	class IMasterObserver;

	/// Modules/Actors
	namespace Actor
	{
		class IActor;
		namespace Player
		{
			class PlayerManager;
		}
	}

	namespace cron
	{
		class Batch;
	}

	/// <summary>
	/// Modules/Event
	/// </summary>
	namespace Event
	{
		class IEvent;

		namespace Talk
		{
			class TalkObj;

			class SerifCtrl;
			class FaceTable;
			class TriggerFactory;
		}
	}

	namespace ui
	{
		class IUserInterface;
	}

	/// <summary>
	/// Datastores
	/// </summary>
	class IRoomDataStore;
	class IEnemyDataStore;
	class IGimmickDataStore;
	class IMapDataStore;
	class IDecorDataStore;
	class IDecorGraphicsDataStore;
	class IDecorAnimationDataStore;
	class IBackGroundDataStore;

	/// <summary>
	/// Entities
	/// </summary>
	struct RoomEntity;
	struct MapEntity;
	struct EnemyEntity;
	struct GimmickEntity;
	struct BackGroundEntity;
	struct DecorEntity;
	struct DecorGraphicsEntity;
	struct DecorAnimationEntity;

	/// <summary>
	/// Models
	/// </summary>
	struct RoomBorders;
	class RoomModel;
	class ICollisionModel;
	class IMapCollisionModel;
	class CameraModel;
	class QuakeModel;
	class IDecorModel;

	/// <summary>
	/// Components
	/// </summary>
	namespace Actor
	{
		class ActorTime;
		class Terrain;
		class MapCollider;
		class DeadChecker;
		class CustomCollider;
		class RotateCtrl;
		class HP;
		class ScaleCtrl;
		class StateCtrl;
		class Body;
		class IPhysics;
		class ICollider;
		class ICollision;
		class CollisionCtrl;
	}

	/// <summary>
	/// Services
	/// </summary>
	class IStageService;
	class IDecorService;
	class IDecorGraphicsService;
	class IBackGroundService;

	/// <summary>
	/// Types
	/// </summary>
	struct CShape;
	class ColDirection;
	struct MapColInfo;

	/// <summary>
	/// Views
	/// </summary>
	
	class WorldView;
	class CameraView;

	class DecorView;
	class IDecorVM;
	class BackGroundVM;
}