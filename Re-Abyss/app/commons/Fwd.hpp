#pragma once

/// <summary>
///  前方宣言
/// </summary>

namespace abyss
{
    class GameObject;
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
    class QuakeEpicenter;
	class Distortion;
	class ICameraWork;
	namespace ColSys
	{
		class CollisionManager;
	}
	using ColSys::CollisionManager;

	namespace Physics
	{
		class PhysicsManager;
	}
	using Physics::PhysicsManager;

	class Stage;
	class StageData;
	class Light;
	class Sound;
	class Temporary;
	class TemporaryData;
	class DrawManager;
	
	/// <summary>
	/// Modules/Actor
	/// </summary>
	namespace Actor
	{
        class Actors;
		class ActorObj;

		namespace Player
		{
			class PlayerManager;
		}
	}
    using Actor::Actors;

	namespace Cron
	{
		class Batch;
        class Crons;
    }
    using Cron::Crons;

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
        class Events;
	}
    using Event::Events;

    /// <summary>
    /// Modules/Adv
    /// </summary>
    namespace Adv
    {
        class Adventures;
        class Project;
        class AdvObj;
    }
    using Adv::Adventures;

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

	namespace FieldEnv
	{
		class Environment;
	}
	using FieldEnv::Environment;

	/// <summary>
	/// Modules/Room
	/// </summary>
	namespace Room
	{
        struct RoomBorders;
        class RoomData;
		class RoomManager;
	}
	using Room::RoomManager;

	namespace Sfx
	{
		class SpecialEffects;
		class PostEffects;
	}
	using Sfx::SpecialEffects;
	using Sfx::PostEffects;

	namespace Devs
	{
		class WorldComment;

        namespace Project
        {
            class Project;
        }
 	}
	using Devs::WorldComment;
    using Devs::Project::Project;

    namespace Pause
    {
        class PauseManager;
    }
    using Pause::PauseManager;

    namespace Fade
    {
        class Fader;
        class SceneFader;
    }
    using Fade::Fader;

	/// <summary>
	/// Entities
	/// </summary>
	struct RoomEntity;
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
		namespace Land
		{
			struct LandEntity;
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
	namespace User
	{
        class Storage;
		class UserModel;
	}
    using User::Storage;

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

	/// <summary>
	/// Views
	/// </summary>
	class CameraView;
}
