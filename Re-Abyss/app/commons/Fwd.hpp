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
	class Decors;
	class BackGround;
	class Effects;
	class Sound;
	class UIs;
	class Crons;
	class Save;
	class SaveData;
	class Master;
	class IMasterObserver;
	class DrawManager;

	/// Modules/Actors
	namespace Actor
	{
		class ActorObj;
		namespace Player
		{
			class PlayerManager;
		}
	}

	namespace Cron
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

	namespace UI
	{
		class UIObj;
	}

	namespace Decor
	{
		class DecorObj;
	}

	/// <summary>
	/// Datastores
	/// </summary>
	class IRoomDataStore;
	class IEnemyDataStore;
	class IGimmickDataStore;
	class IMapDataStore;
	class IBackGroundDataStore;

	/// <summary>
	/// Entities
	/// </summary>
	struct RoomEntity;
	struct MapEntity;
	struct EnemyEntity;
	struct GimmickEntity;
	struct BackGroundEntity;
	namespace Actor
	{
		namespace Item
		{
			struct ItemEntity;
		}
	}
	namespace Decor
	{
		struct DecorEntity;
		struct AnimationEntity;
		struct GraphicsEntity;
	}

	/// <summary>
	/// Models
	/// </summary>
	struct RoomBorders;
	class RoomModel;
	class ICollisionModel;
	class IMapCollisionModel;
	class CameraModel;
	class QuakeModel;
	namespace User
	{
		class UserModel;
	}

	/// <summary>
	/// Components
	/// </summary>
	namespace Actor
	{
		class ClockCtrl;
		class Terrain;
		class MapCollider;
		class DeadChecker;
		class CustomCollider;
		class RotateCtrl;
		class HP;
		class ScaleCtrl;
		class StateCtrl;
		class Body;
		class Foot;
		class IPhysics;
		class ICollider;
		class ICollision;
		class CollisionCtrl;
	}

	/// <summary>
	/// Services
	/// </summary>
	class IStageService;
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

	class BackGroundVM;
}