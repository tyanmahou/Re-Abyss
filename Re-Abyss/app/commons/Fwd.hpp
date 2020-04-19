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
	class Stage;
	class Light;
	class Decor;
	class DecorGraphicsManager;
	class BackGround;

	/// Controllers/Actors
	class ICollider;
	class IActor;
	class Attacker;
	class Receiver;
	class PlayerActor;
	class PlayerShotActor;
	class EnemyActor;
	class MapActor;
	class FloorActor;
	class PenetrateFloorActor;
	class LadderActor;
	class DoorActor;

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
	struct SlimeEntity;
	struct RollingTakoEntity;
	struct CaptainTakoEntity;
	struct IkalienEntity;
	struct LaunSharkEntity;
	struct SchieldEntity;

	struct GimmickEntity;
	struct StartPosEntity;
	struct DoorEntity;

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
	class BodyModel;
	class IDecorModel;

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

	class PlayerVM;
	class PlayerShotVM;
	class SlimeVM;
	class RollingTakoVM;
	class CaptainTakoVM;
	class CaptainTakoShotVM;
	class IkalienVM;
	class LaunSharkVM;
	class LaunSharkShotVM;
	class SchieldVM;
	class SchieldShotVM;
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