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
	class Camera;
	class ICameraWork;
	class DoorCameraWork;
	class RoomMoveCameraWork;
	class World;
	class Stage;

	/// Controllers/Actors
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
	/// Entities
	/// </summary>
	struct RoomEntity;
	struct MapEntity;
	struct EnemyEntity;
	struct DoorEntity;

	/// <summary>
	/// Models
	/// </summary>
	class RoomModel;
	class ICollisionModel;
	class CameraModel;
	class BodyModel;

	/// <summary>
	/// Repositories
	/// </summary>
	class IStageRepository;

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

	class CameraView;
	class DoorCameraWorkView;

	class IStageView;

	/// <summary>
	/// Visitor
	/// </summary>
	class ActVisitor;
}