#pragma once

/// <summary>
///  前方宣言
/// </summary>

namespace abyss
{
	/// <summary>
	/// Controllers
	/// </summary>
	class ActionSystem;
	class ActManager;
	class Camera;
	class ICameraWork;
	class DoorCameraWork;
	class RoomMoveCameraWork;
	class World;
	class Events;
	class Stage;
	class Light;
	class Decor;
	class DecorGraphicsManager;
	class BackGround;

	/// Controllers/Actors
	class IActor;
	class Attacker;
	class Receiver;
	namespace Player
	{
		class PlayerActor;
	}
	inline namespace Enemy
	{
		class EnemyActor;
	}
	inline namespace Map
	{
		class MapActor;
	}
	namespace Floor
	{
		class FloorActor;
	}
	namespace PenetrateFloor
	{
		class PenetrateFloorActor;
	}
	namespace Ladder
	{
		class LadderActor;
	}
	namespace Door
	{
		class DoorActor;
	}

	/// <summary>
	/// Controllers/Event
	/// </summary>
	namespace Event
	{
		namespace Talk
		{
			class FaceManager;
			class TriggerManager;
		}
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

	// Factory
	class DIContainer;

	/// <summary>
	/// Models
	/// </summary>
	struct RoomBorders;
	class RoomModel;
	class ICollisionModel;
	class CameraModel;
	class IDecorModel;

	/// <summary>
	/// Models / Components
	/// </summary>
	class BodyModel;
	class IColliderModel;
	class CustomColliderModel;
	class ActorTimeModel;
	class PosModel;
	class HPModel;

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
	class DoorCameraWorkView;

	class IStageView;
	class DecorView;
	class IDecorVM;
	class BackGroundVM;

	/// <summary>
	/// Visitor
	/// </summary>
	class ActVisitor;
}