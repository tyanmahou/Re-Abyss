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
	class Distortion;
	class ICameraWork;
	class World;
	namespace Physics
	{
		class PhysicsManager;
	}
	using Physics::PhysicsManager;

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
	class Temporary;
	class TemporaryData;
	class Master;
	class IMasterObserver;
	class DrawManager;

	class ICollision;
	
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

	/// Modules/Cycle
	namespace Cycle
	{
		class CycleObj;
		class CycleMaster;
	}
	using Cycle::CycleMaster;

	/// <summary>
	/// Entities
	/// </summary>
	struct RoomEntity;
	struct BackGroundEntity;
	namespace Actor
	{
		namespace Enemy
		{
			struct EnemyEntity;
		}
		namespace Gimmick
		{
			struct GimmickEntity;
		}
		namespace Item
		{
			struct ItemEntity;
		}
		namespace Map
		{
			struct MapEntity;
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
		class MapCollider;
		class DeadChecker;
		class CustomCollider;
		class RotateCtrl;
		class HP;
		class ScaleCtrl;
		class StateCtrl;
		class Body;
		class Foot;
		class ICollider;
		class ICollision;
		class CollisionCtrl;
	}

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