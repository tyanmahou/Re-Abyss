#pragma once

/// <summary>
///  前方宣言
/// </summary>

namespace abyss
{
	/// <summary>
	/// Controllers
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

	/// Controllers/Actors
	class IActor;
	class Attacker;
	class Receiver;
	inline namespace Enemy
	{
		class EnemyActor;
	}
	namespace Ooparts
	{
		class OopartsActor;
	}
	namespace Actor
	{
		namespace Player
		{
			class PlayerActor;
		}
		namespace Map
		{
			class MapActor;

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
		}
		namespace Gimmick
		{
			namespace Door
			{
				class DoorActor;
			}
		}
	}

	/// <summary>
	/// Controllers/Event
	/// </summary>
	namespace Event
	{
		class IEvent;

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
	class IMapCollisionModel;
	class CameraModel;
	class QuakeModel;
	class IDecorModel;

	/// <summary>
	/// Models / Components
	/// </summary>
	class ActorTimeModel;
	class BodyModel;
	class CustomColliderModel;
	class DeadCheckerModel;
	class RotateModel;
	class HPModel;
	class IColliderModel;
	class IPhysicsModel;
	class MapColliderModel;
	class ScaleModel;
	class StateModel;
	class TerrainModel;

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

	/// <summary>
	/// Visitor
	/// </summary>
	class ActVisitor;
}