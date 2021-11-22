#pragma once

/// <summary>
///  前方宣言
/// </summary>

namespace abyss
{
	class IComponent;

	namespace Sys
	{
		class IBooter;
	}
	/// <summary>
	/// Modules
	/// </summary>
	class Manager;
	class GlobalTime;
	class Camera;
	class Quake;
	class Distortion;
	class ICameraWork;
	class World;
	namespace Collision
	{
		class CollisionManager;
	}
	using Collision::CollisionManager;

	namespace Physics
	{
		class PhysicsManager;
	}
	using Physics::PhysicsManager;

	class Events;
	class Stage;
	class StageData;
	class Light;
	class BackGround;
	class Sound;
	class Crons;
	class Temporary;
	class TemporaryData;
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
	/// Modules/Effect
	/// </summary>
	namespace Effect
	{
		class Effects;
		class EffectObj;
	}
	using Effect::Effects;

	/// <summary>
	/// Modules/Event
	/// </summary>
	namespace Event
	{
		class EventObj;
	}

	/// <summary>
	/// Modules/Novel
	/// </summary>
	namespace Novel
	{
		class Novels;
		class CharaTable;
		class TalkObj;
	}
	using Novel::Novels;

	namespace UI
	{
		class UIs;
		class UIObj;
	}
	using UI::UIs;

	namespace Decor
	{
		class Decors;
		class DecorObj;
	}
	using Decor::Decors;

	/// Modules/Cycle
	namespace Cycle
	{
		class CycleObj;
		class CycleMaster;
	}
	using Cycle::CycleMaster;

	namespace Env
	{
		class Environment;
	}
	using Env::Environment;

	/// <summary>
	/// Modules/Room
	/// </summary>
	namespace Room
	{
		class RoomManager;
	}
	using Room::RoomManager;

	namespace Sfx
	{
		class PostEffects;
	}
	using Sfx::PostEffects;

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
	class ClockCtrl;
	namespace Actor
	{
		class MapCollider;
		class DeadChecker;
		class CustomCollider;
		class RotateCtrl;
		class HP;
		class ScaleCtrl;
		class StateCtrl;
		class Body;
		class Foot;
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