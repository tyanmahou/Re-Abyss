#pragma once

/// <summary>
///  前方宣言
/// </summary>

namespace abyss
{
	/// <summary>
	/// Controllers
	/// </summary>
	class Camera;
	class ICameraWork;
	class DoorCameraWork;
	class RoomMoveCameraWork;
	class World;

	/// <summary>
	/// Entities
	/// </summary>
	struct RoomEntity;
	struct MapEntity;
	struct EnemyEntity;
	struct DoorEntity;

	/// <summary>
	/// Models
	/// </summary>
	class WorldModel;
	class RoomModel;
	class ICollisionModel;
	class CameraModel;
	class StageModel;

	// Models/Actors
	class ICollider;
	class IActor;
	class PlayerActor;
	class PlayerShotActor;
	class EnemyActor;
	class SlimeActor;
	class MapActor;
	class FloorActor;
	class PenetrateFloorActor;
	class LadderActor;
	class DoorActor;

	/// <summary>
	/// Repositories
	/// </summary>
	class IStageRepository;

	/// <summary>
	/// Types
	/// </summary>
	struct CShape;
	class ColDirection;

	/// <summary>
	/// Views
	/// </summary>
	
	class WorldView;
	class IActorView;
	class PlayerView;
	struct PlayerViewModel;
	class PlayerShotView;
	struct PlayerShotViewModel;
	class SlimeView;
	struct SlimeViewModel;

	class CameraView;
	class DoorCameraWorkView;

	/// <summary>
	/// Visitor
	/// </summary>
	class ActVisitor;
}