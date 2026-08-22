#ifndef PROJECT_GAME_PLAYER_H
#define PROJECT_GAME_PLAYER_H

class CCharacter;
struct SResourceHandle;
struct SResourceCache;
class CVehicle;
template <typename T>
class CAvaSingle;

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <cmath>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "AvaCore/Types/Rtti.h"
#include "Game/Character/Avatar.h"
#include "Game/GameObject/InputActionOverride.h"
#include "Game/GUI/GameGui.h"
#include "build/Win64/Final/ctg/components/Animation/include/Animation/AnimationTrack.h"
#include "Game/AI/Util/GraphRenderer.h"
#include "AvaCore/FileHandling/Parsing/RuntimeContainer.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/SaveSystem/SaveContext.h"
#include "Game/AI/Pathfinding/NavMeshSphereObstacle.h"
#include "AvaCore/Math/Ewma.h"
#include "build/Win64/Final/ctg/components/Input/include/Input/InputActionMap.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/DeviceManager.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CameraControl/CameraControlManager.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/Online/OnlineManager.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/Online/EventStructs_gen.h"
#include "Game/Character/CharacterManager.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GlobalDictionary.h"
#include "AvaCore/Types/EventID.h"
#include "Base/Misc/Event.h"
#include "build/Win64/Final/ctg/components/Base/include/Base/Timer/Clock.h"


class CPlayer : public NEvent::CEventHandler, public CAvatar {
    public:
    struct CampThreatValues {
        float m_DetectedValue;
        float m_LastDetectedValue;
        CHashString m_KeyBbAlertLevelHash;
        bool m_Dirty;
        std::map<CCharacter *, float> m_EnemyRangeMap;
    };

    struct SPlayerDistanceTraveledTracker {
        CVector3f m_PositionPreviousFrame;
        float m_AccumulatedDistanceInMeters;
    };

    
    enum EDifficulty : int32_t {

    };

    enum EContextualCamera : int32_t {
        CC_MELEE_COMBAT = 0x0000,
        CC_EXPLORATION = 0x0001,
        MAX_CONTEXTUAL_CAMERA_COUNT = 0x0002,
    };

    
    static const CRttiTypeId& TYPE_ID();
    
    
    public:
    std::map<CHashString, int> m_FuryEventCounter;
    std::vector<CHashString> m_FuryEventQueue;
    std::vector<unsigned int,std::allocator<unsigned int> > m_OverrideActionListSortedIncludes;
    std::vector<unsigned int,std::allocator<unsigned int> > m_OverrideActionListSortedExcludes;
    std::vector<unsigned int,std::allocator<unsigned int> > m_ActionList;
    std::vector<CInputActionOverride *,std::allocator<CInputActionOverride *> > m_ActiveInputActionOverides;
    CHashString m_GuiDeathRunActiveProfileId;
    SGameGuiAmmoPickup m_GUIPickups[4];
    int32_t m_NumGUIPickups;
    CHashString m_PlayerNameHash;
    CHashString m_SoundSystemVocalIdentifier;
    NEvent::CReceiveEvent<char const *,void,void,void,void> m_RemovePlayerItem;
    NEvent::CReceiveEvent<void,void,void,void,void> m_FreezeHealthOnEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_FreezeHealthOffEvent;
    unsigned char* m_SaveBuffer;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_StruggleCountered;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DisableEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnableEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnableInput;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DisableInput;
    NEvent::CReceiveEvent<void,void,void,void,void> m_PlayerUnequipWeaponEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_PlayerPause;
    NEvent::CReceiveEvent<void,void,void,void,void> m_PlayerUnpause;
    NEvent::CReceiveEvent<void,void,void,void,void> m_AiEntityDisable;
    NEvent::CReceiveEvent<void,void,void,void,void> m_AiEntityEnable;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_FreezeFrames;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnableUnlimitedAmmo;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DisableUnlimitedAmmo;
    NEvent::CReceiveEvent<char const *,void,void,void,void> m_TakeDamage;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_TakeDamageTrackEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_GiveHealth;
    NEvent::CReceiveEvent<char const *,void,void,void,void> m_RemoveEquipment;
    NEvent::CReceiveEvent<char const *,void,void,void,void> m_GiveItem;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ConsumeFuelAndDropJerrycan;
    NEvent::CReceiveEvent<void,void,void,void,void> m_GiveSniperBullets;
    NEvent::CReceiveEvent<void,void,void,void,void> m_GiveShotgunBullets;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ClearFury;
    NEvent::CReceiveEvent<void,void,void,void,void> m_KillEveryone;
    NEvent::CReceiveEvent<void,void,void,void,void> m_GivePlayerKnife;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnableMap;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DisableMap;
    NEvent::CReceiveEvent<void,void,void,void,void> m_MapRuntimeBlock;
    NEvent::CReceiveEvent<void,void,void,void,void> m_MapRuntimeUnblock;
    bool m_IsMapRuntimeBlocked;
    unsigned char m_IsMapEnabled;
    NEvent::CReceiveEvent<void,void,void,void,void> m_Sandstorm;
    float m_SandstormTimer;
    NEvent::CSendEvent<void,void,void,void,void> m_OnForcedNeutralStateEvent;
    NEvent::CSendEvent<void,void,void,void,void> m_OnEnterCombat;
    NEvent::CSendEvent<void,void,void,void,void> m_OnExitCombat;
    NEvent::CReceiveEvent<char const *,void,void,void,void> m_CastSpellBuffOnPlayerEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ResurrectForLegendPointsEvent;
    int32_t m_ContextualCameras[2];
    int32_t m_CurrentStateCameraIds[16];
    CPlayer::EDifficulty m_Difficulty;
    float m_GrassFadeTimer;
    std::weak_ptr<CVehicle> m_LastVehicleAttachedTo; // BOOST PTR
    bool m_HasDOFLocked;
    bool m_WaitForLandscapeLoad;
    bool m_Enabled;
    bool m_DelayFrame;
    bool m_UnlimitedAmmo;
    bool m_GroundContact;
    bool m_ReviveCostValuesDirty;
    float m_StartInGodModeTimer;
    float m_CurrentPlayerOpacity;
    float m_InputAccPeriod;
    int32_t m_AimMode;
    CPlayer::CampThreatValues m_CampThreatValues;
    float m_CombatTriggerEnemyRange;
    int32_t m_CombatTriggerRegisterIndex;
    float m_CombatTriggerEnemyRangeTime;
    CGraphRenderer m_GraphRenderer;
    float m_Gravity;
    float m_InputJumpVelocityGain;
    float m_JumpRotationSpeed;
    float m_MovementSpeedMin;
    float m_MovementSpeedMax;
    float m_AimMovementSpeedMin;
    float m_AimMovementSpeedMax;
    float m_CoverCornerMargin;
    float m_AimDelayDuration;
    float m_LastSavedScrapInventoryAmount;
    uint32_t m_DefaultGuiButtonPrompt;
    uint32_t m_DefaultGuiButtonText;
    uint32_t m_ActiveGuiButtonPrompt;
    uint32_t m_ActiveGuiButtonText;
    std::list<unsigned int,std::allocator<unsigned int> > m_LastDeathTimes;
    CEWMA m_NoiseReducingFilters[4];
    float m_InputPosFilterAlpha;
    float m_InputVelFilterAlpha;
    CNavMeshSphereObstacle* m_NavMeshMeleeObstacle;
    uint64_t m_CombatSessionId;
    CPlayer::SPlayerDistanceTraveledTracker m_DistanceTraveledTracker;

    static const CVector3f m_PropGrenadeRotOffset;
    static const CVector3f m_PropGrenadePosOffset;
    static const CVector3f m_PropTriggeredRotOffset;
    static const CVector3f m_PropTriggeredPosOffset;
    static float m_SoftLockVelocity;
    static bool m_NormalCameraUpdate;
    static float m_FireInputAmount;
    static float m_AutomaticWeaponFireSensitivity;
    static float m_FireInputBufferDuration;
    static float m_GUIProgressbarMaxTime;
    static bool m_FreezeHealth;
    static float m_AccuracyIncreaseRate;
    static float m_NoTargetAccuracy;



    virtual bool GetCharacterControllerMapping() const;
    virtual void SetIsFiringAtAvatar(CCharacter* evil_character);
    virtual Input::CInputActionMap* GetInputActionMap();
    virtual void UpdateRender(float dt, float dtf, float real_dt);
    virtual bool IsDead();
    virtual const CRttiTypeId& GetTypeId() const;
    virtual void RegisterPickup(uint32_t weapon_id, uint32_t ammo_change, uint32_t ammo_total);
    virtual uint32_t GetNumRegisteredPickup() const;
    virtual const SGameGuiAmmoPickup& GetPickup(uint32_t pickup_index) const;
    virtual void ClearPickups();
    virtual float GetCombatTriggerTimer() const;
    virtual void UpdateDebug(float dt);
    virtual void UpdateGamezoneInformation();
    virtual void UpdateSoundFocus();
    virtual int32_t GetFaction();
    virtual const CMatrix4f& GetWorldMatrix();
    virtual void SetWorldMatrix(const CMatrix4f& m);
    virtual bool IsDestroyed();
    virtual void SetAimMode(int32_t mode);
    virtual void ReInitCharacter();
    virtual void ReInit();
    virtual void RenderMovementInput(float dt);
    virtual void ResetMovementInputTrail();
    virtual void UpdateMotionGraphs(float dt);
    virtual void RenderMotionGraphs(float dt);
    virtual void Enable(bool enable);
    virtual EDifficulty GetDifficulty() const;
    virtual void SetDifficulty(EDifficulty difficulty);
    virtual void SetInvulnerable(bool invulnerable);
    virtual bool IsInvulnerable() const;
    virtual void PrintDebugVelocity(float dt);
    virtual void RenderDebugBoneMatrices();
    virtual void ResetInvulnerableTimer();
    virtual bool IsUpdatingCameraController() const;
    virtual int32_t GetCurrentStateCameraId(int32_t index) const;
    virtual void SetCurrentStateCameraId(int32_t index, int32_t camera_id);
    virtual int32_t GetContextualCameraId(EContextualCamera camera_type) const;
    virtual void CalculateReviveCost(float& actual_cost, float& default_cost);
    virtual void SetCombatSessionId(unsigned long long session_id);
    virtual void OnActionsRemap();
    virtual void OverrideActionsApplyMerge();
    virtual void OverrideActions(CInputActionOverride* iao);
    virtual void UpdateMoveDirection(float dt);
    virtual void FixupRagdollConstraints(float dt);
    virtual void OnForceNeutralState();
    virtual bool DoReactToHit(const IPfxGameObject::SHitReactInfo& info);
    virtual void DoActReactHitFly();
    virtual void HitByExplosion(CPhysicsGameObject::SHitByExplosionData& data);
    virtual void OnDeath(CHashString type);
    virtual bool IsType(const CRttiTypeId& id) const;
    virtual void GetHorizonDirection(CVector3f& dir);
    virtual bool HitByBullet(CPhysicsGameObject::SHitByBulletData& data);
    virtual void PostWorldMatrixUpdateCallback(float dt);
    virtual bool InCombat();
    virtual void RemoveFromRangeMap(CCharacter* c);
    virtual void GetTransform(CMatrix4f& transform);
    virtual void UpdateControlParams();
    virtual void UpdateController(float dt);
    virtual void UpdatePostPhysics(float dt);
    virtual void UpdateNavMeshMeleeObstacle();
    virtual void InitCombatTriggers(const CRuntimeContainer& p);
    virtual void AddToSmallSceneRender();
    virtual void LoadAccuracyMods(const CRuntimeContainer& p);
    virtual void LoadAlertLevelValues(const CRuntimeContainer& p);
    virtual void Init(const CRuntimeContainer& player_container);
    virtual void SetPaused(bool paused);
    virtual void HandleConsoleEvents(const NEvent::CEventImpl* event, const NEvent::CEventData& data);
    virtual void Save(CSaveContext& save_cont);
    virtual void UpdateGroundContact();
    virtual void UpdatePlayerEffects(float dt);
    virtual bool IsInBalloon() const;
    virtual float GetFuryEventVariationMultiplier(CHashString event_name);
    virtual int32_t GetFuryEventCount(CHashString event_name);
    virtual void PatchMapEnabled();
    virtual void UpdatePrePhysics(float dt);
    virtual void Reset(const CHashString* state);
    virtual void ClearFuryEventCounters();
    virtual ~CPlayer();
    virtual void HandleEvent(const NEvent::CEventImpl* event, const NEvent::CEventData& data);
    CPlayer();
    virtual void Load(const CSaveContext& save_cont);
    virtual void SensedBy(CCharacter* c, const float detectiveness, const float range);
    virtual void OverrideActionsGrowList(CInputActionOverride* iao);
    virtual void RecordFuryEvent(CHashString event_name);
    virtual void ClearOverrideActions(CInputActionOverride* iao);
};

#endif
