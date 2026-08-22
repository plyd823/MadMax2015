#ifndef PROJECT_GAME_CHARACTER_H
#define PROJECT_GAME_CHARACTER_H

class CItemObject;
class CEffectInstance;
class CAvatar;
class CWeapon;
class CRuntimeContainer;
struct SGameEffectContainer;

#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CharacterSystem/CharacterBase.h"
#include "project/Game/Interaction/InteractionUserProxy.h"
#include "project/Game/Health/HealthWrapper.h"
#include "libs/CoreLibs/main/include/ALib/HashTable.h"
#include "project/Game/Equipment/Item/Weapon/Explosive.h"
#include "project/Game/Inventory/Inventory.h"
#include "project/Game/Character/CharacterStats.h"
#include "build/Win64/Final/ctg/components/Physics/include/Physics/PfxCharacterInstance.h"
#include "project/Game/Character/BoneAttachment/BoneOffsetAlias.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/EffectSystem/Effects/AOVolume.h"
#include "project/Game/Character/AnimStateTransitionObserver.h"
#include "project/Game/AI/Pathfinding/AiPathfinderContext.h"
#include "project/fragments/ai/include/AiBehavior/ObjectBlackboard.h"
#include "project/Game/Character/ControlParameters.h"
#include "project/Game/Character/Helpers/AnimationAlignmentHelper.h"
#include "project/Game/Character/CharacterSounds.h"
#include "project/Game/Character/CharacterVocals.h"
#include "project/Game/AI/AiEntitiesGame.h"
#include "project/Game/Character/LookAtIKDirector.h"
#include "project/Game/GameObject/StateContainerDatas.h"
#include "project/Game/Character/TargetHandler.h"
#include "project/Game/Character/LocomotionGraph.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/Effects/Outline.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/AnimatedModel.h"
#include "project/Game/Character/CharacterIK.h"
#include "project/Game/Character/DeformerJointTwister.h"
#include "project/Game/Character/BoneAttachment/SecondaryMotionController.h"
#include "project/Game/Damage/DamageDecal.h"
#include "build/Win64/Final/ctg/components/Animation/include/Ragdoll/RagdollCollisionListener.h"
#include "build/Win64/Final/ctg/components/Animation/include/Ragdoll/Ragdoll.h"
#include "build/Win64/Final/ctg/components/Animation/include/Ragdoll/RagdollInstance.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CharacterSystem/RagdollProxyPhantom.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/Physics/DamageInflictor.h"
#include "project/Game/Character/FootstepFX.h"
#include "build/Win64/Final/ctg/components/Base/include/Base/Types/Static_string.h"
#include "build/Win64/Final/ctg/components/Animation/include/Animation/JointInfo.h"
#include "project/Game/Character/BoneIndices.h"
#include "build/Win64/Final/ctg/components/System/include/System/Model/ModelInstance.h"
#include "project/Game/Equipment/Item/Ammunition/Ammunition.h"
#include "build/Win64/Final/ctg/components/Animation/include/Animation/AnimationTrack.h"
#include "build/Win64/Final/ctg/components/Animation/include/Animation/Animation.h"
#include "AvaCore/Types/VectorMap.h"
#include "build/Win64/Final/ctg/components/Animation/include/Animation/StateMachine/Transition.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CharacterSystem/AnimationRuleSystem.h"
#include "AvaCore/Math/Geometrics/AABBox.h"
#include "build/Win64/Final/ctg/components/Physics/include/Physics/PfxRigidBody.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CharacterSystem/AnimatedBodyPart.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CharacterSystem/AnimationDriverTransition.h"
#include "build/Win64/Final/ctg/components/Animation/include/Animation/StateMachine/StateMachineInstance.h"
#include "build/Win64/Final/ctg/components/Animation/include/Animation/AnimationSet.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CharacterSystem/AnimationControl.h"
#include "build/Win64/Final/ctg/components/Animation/include/IK/IKTwoJoints.h"
#include "build/Win64/Final/ctg/components/Animation/include/Animation/StateMachine/State.h"

struct SSpellHitInfo {

};

struct SExplosionHitData {

};

struct SBulletHitData {

};

class CSetTransformConstraint {

};

struct HThreadMutexName { // could not find where this is actually defined

};

class hkpRigidBody { // inherits from hkpEntity

};

class hkpShape { // inherits from hkpShapeBase

};

struct SGameObjectInitContext {

};

struct SGameObjectUpdateContext {

};

struct SGameObjectRenderContext {

};

struct SGameObjectSetPropertiesContext {

};

struct SCastRayInfo {

};

class CCharacter : public CDamageable, public NCharacterSystem::CCharacterBase, public IPhysicsGameObjectListenable {
    struct SQueuedImpulsePair {
        public:
        CVector3f m_LinearImpulse;
        CVector3f m_AngularImpulse;
    };

    struct SAttachedEffectInfo {

    };

    struct SShapeImpulsePair {

    };

    struct SHitByFireData {

    };

    struct SMeleeLoopEffect {

    };

    struct SMatrixSpring {

    };

    struct SSpellTargetCharacterInfo {

    };

    enum EMotionState : int32_t {
        COMBINED_VELOCITY = 0x0000,
        ANIMATION_VELOCITY = 0x0001,
        STEERING_VELOCITY = 0x0002,
        COMBINED_ATTACHED = 0x0003,
        STEERING_ATTACHED = 0x0004,
        POSITIONING = 0x0005,
        SCALED_POSITIONING = 0x0006,
        ROTATED_VELOCITY = 0x0007,
        ROTATED_VELOCITY_JUMPING = 0x0008,
        HIPS_ALIGNED_COMBINED_VELOCITY = 0x0009,
        HIPS_ALIGNED_STEERING_VELOCITY = 0x000a,
        HIPS_ALIGNED_COMBINED_ATTACHED = 0x000b,
        CUSTOM_UP_COMBINED_VELOCITY = 0x000c,
        CUSTOM_UP_COMBINED_ATTACHED = 0x000d,
        CUSTOM_UP_STEERING_ATTACHED = 0x000e,
        SHARED_ANIMATION = 0x000f,
        SHARED_ANIMATION_ATTACHED = 0x0010,
        STATIC_ATTACHED = 0x0011,
        INTERACTION_GRAPH_POSITIONING = 0x0012,
        COMBINED_VELOCITY_NO_ROTATION = 0x0013,
        STEERING_VELOCITY_NO_ROTATION = 0x0014,
        CONSTRAINT_POSITIONING = 0x0015,
        NOF_MOTIONSTATES = 0x0016,
    };
    
    public: 
    THashTable<int,unsigned int,1,unsigned short> m_DecalTargetHashes;
    uint32_t m_CurrentDecalSlot;
    uint32_t m_DefaultControllerId;
    unsigned char m_IntervalOrder;
    bool m_IntervalUpdateFrame;
    float m_IntervalTimeSkipMultiplier;
    unsigned char m_IntervalFramesSkipped;

    private: 
    TArray<CCharacter::SQueuedImpulsePair> m_QueuedImpulses;

    public: 
    std::shared_ptr<CExplosives> m_ActiveGrenade; // BOOST PTR
    uint32_t m_SpellCastSeed;
    uint32_t m_SpellCritSeed;
    float m_HeightOverGround;
    float m_HeightOverGroundExcludingWater;
    bool m_Visible : 1; /* BitPos=0 */
    bool m_Enabled : 1; /* BitPos=1 */
    bool m_StartEnabled : 1; /* BitPos=2 */
    bool m_GhostMode : 1; /* BitPos=3 */
    bool m_PendingGhostMode : 1; /* BitPos=4 */
    bool m_DontReactToHit : 1; /* BitPos=5 */
    bool m_DistanceCulledInVehicle : 1; /* BitPos=6 */
    bool m_InScoutingMode : 1; /* BitPos=7 */
    bool : 0; /* BitPos=8 */
    bool m_InPlayerUpgrade : 1; /* BitPos=0 */
    bool m_WasVisible : 1; /* BitPos=1 */
    bool m_AimingEnabled : 1; /* BitPos=2 */
    bool m_UpdatePhysics : 1; /* BitPos=3 */
    bool m_UseFinalTransparency : 1; /* BitPos=4 */
    bool m_IsPlayer : 1; /* BitPos=5 */
    bool m_PendingSetTransform : 1; /* BitPos=6 */
    bool m_UseScopeFresnelEffect : 1; /* BitPos=7 */
    bool : 0; /* BitPos=8 */
    bool m_SetPropertiesOK : 1; /* BitPos=0 */
    bool m_InSequence : 1; /* BitPos=1 */
    bool m_WasDestroyed : 1; /* BitPos=2 */
    bool m_Gibed : 1; /* BitPos=3 */
    bool m_SyncRagdollState : 1; /* BitPos=4 */
    bool m_SyncRagdollPartialEnable : 1; /* BitPos=5 */
    bool m_RagdollFullyEnabled : 1; /* BitPos=6 */
    bool m_SyncRagdollUsePoseBoneVelocities : 1; /* BitPos=7 */
    float m_ContinousRagdollPartialEnableTimer;
    CInventory* m_Inventory;
    std::shared_ptr<CItemObject> m_WieldedItem; // BOOST PTR
    CCharacterStats m_Stats;
    CCharacterDaze m_Daze;
    std::vector<std::shared_ptr<CItemObject>,std::allocator<std::shared_ptr<CItemObject> > > m_InventoryAttachedItems; // BOOST PTR
    CPhysicsGameObjectListenerContainer m_Listeners;
    int32_t m_MaterialBelow;
    CVector3f m_SurfaceNormal;
    unsigned char m_SpawnTypeId;
    unsigned char m_SpawnTypeIdUnModified;
    uint32_t m_SpawnTeam;
    int32_t m_Faction;
    float m_CharacterLootTime;
    int32_t m_CharacterLevel;
    uint64_t m_InteractionContextId;
    uint64_t m_InteractionId;
    CPfxCharacterInstance::EProxyState m_PendingProxyState;
    bool m_PendingProxyStateCheckCollision;
    float m_CorpseCoolingTime;
    uint32_t m_TimeOfDeath;
    float m_AdvancedMoveToTimer;
    float m_CurrentAccuracy;
    float m_CurrentInternalAccuracy;
    float m_MinAccuracy;
    float m_MaxAccuracy;
    CVector3f m_AnimationTranslationScaling;
    CMatrix4f* m_DynamicAnimScalingGoal;
    CMatrix4f* m_DynamicAnimScalingStartOffset;
    CMatrix4f* m_DynamicAnimScalingGoalOffset;
    CVector3f m_CurrentScaledAnimationTranslation;
    std::vector<CCharacter::SAttachedEffectInfo,std::allocator<CCharacter::SAttachedEffectInfo> > m_AttachedCharacterEffects;
    std::vector<CEffectInstance *,std::allocator<CEffectInstance *> > m_IntensityEffects;
    float m_IntensityClamp;
    bool m_IntensityEffectRestart;

    protected: 
    std::vector<CBoneOffsetAlias::SBoneOffset,std::allocator<CBoneOffsetAlias::SBoneOffset> > m_BoneOffsets;

    public:
    float m_MaxHealth;
    CHashString m_RagdollCacheID;
    float m_HitReaction_ExplosionRagdollImpactThreshold;
    float m_HitReaction_MaxExplosionImpactForce;
    float m_HitReaction_MinorImpactMultiplier;
    float m_HitReaction_MajorImpactMultiplier;
    float m_HitReaction_ExtremeImpactMultiplier;
    float m_HitReaction_KillingBulletImpulseScale;
    float m_HitReaction_ImpactForceDecaySpeed;
    float m_HitReaction_ExplosionImpulseMultiplier;
    float m_HitReaction_ImpactMassThreshold;
    CEffectInstance* m_CollisionEffect;
    float m_ImpactDamageFactor;
    float m_ImpactDamageThreshold;
    float m_CurrentLean;
    CVector3f m_GrenadeTargetOffset;
    CVector3f m_LeftFootPosT0;
    CVector3f m_LeftFootPosT1;
    CVector3f m_RightFootPosT0;
    CVector3f m_RightFootPosT1;
    CAOVolumeInstance* m_AOVolumeInstance[2];
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_HideEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ShowEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DisableEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DetachEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DetachVehicleDeathEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_WieldRightSlotRightHandEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_WieldRightSlotLeftHandEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_RightSlotShowEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_RightSlotHideEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DropItemBehindEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_UnequipWeaponEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_UnequipMeleeWeaponEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_AttachWieldedItemToBoneEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ChangeWeaponEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_FireWeaponAtRangedWeaponTargetsEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_FireInteractionWeapon;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_SendActToInteractioAnimatedModel;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_SpawnItemEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ThrowThunderStickEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ThrowStoneEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_PlantLandMineEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DisarmLinkTarget;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_LinkTargetGiveItemEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_LinkTargetStabShivEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ReloadWeapon;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ReloadWeaponPartial;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ConsumeMagazineAmmo;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_EvadeLandEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_FootTouchEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_FootStrikeEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_InflictDamageEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_CastSpellEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_CastSpellBuffOnSelfEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_CastSpellBuffOnPlayerEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_InstantDeathEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DetachFromInteractionContextEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_LinkTargetDoActEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_LinkSourcesDoActEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_SelfDoActEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_RotateTowardsLinkSourcesEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_CallPlayerAttentionEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_UserVMRegisterSetEvent[35];
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_UserVMRegisterAddEvent[35];
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_AcquireLinkTargetEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ReleaseLinkTargetEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_AcquireMeleeTargetEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_SendFloatEventEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_InteractionGraphEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DialogueIntentEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DialogueIntentTriggerEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_RunInteractionBehaviorEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnterScoutModeEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ExitScoutModeEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnterSniperModeEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ExitSniperModeEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnableCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DisableCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ShowCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_HideCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_FadeInCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_FadeOutCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ClearAttachedEffectsEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnterHighLodMode;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ExitHighLodMode;
    NEvent::CSendEvent<void,void,void,void,void> m_OnCharacterDestroyedEvent;
    NEvent::CSendEvent<void,void,void,void,void> m_OnCharacterBuffAdded;
    THashTable<CHashString,unsigned int,1,unsigned short> m_AnimationTriggerEvents;
    std::vector<IAnimStateTransitionObserver *,std::allocator<IAnimStateTransitionObserver *> > m_StateTransitionObservers;

    private: 
    CAvatar* m_Avatar;
    IPfxGameObject::SHitReactInfo m_LatestHitReactInfo;
    SSpellHitInfo m_LastSpellHitInfo;
    SExplosionHitData m_LastExplosionHitData;
    CPhysicsGameObject::SHitByFireData m_LastFireHitData;
    SBulletHitData m_LastBulletHitData;
    bool m_LatestFireHitValid;
    float m_RecentFireDamageTimer;
    float m_LatestSuccesfullSPellGivenTime;
    float m_LatestSuccesfullSPellReceivedTime;
    int32_t m_AiBaseUpgradeLevel;
    bool m_IsHostileEvenIfAlliedFaction;
    uint64_t m_SavedTiltTowardsTargetId;
    bool m_IsNarrativeEncounterPerson;
    std::vector<CCharacter::SShapeImpulsePair,std::allocator<CCharacter::SShapeImpulsePair> > m_BulletImpulseStorage;
    CAiPathfinderContext* m_PathfinderContext;
    CAiPathfinderTarget m_PathfinderTargets[2];

    public: 
    volatile uint64_t m_BlackboardLock;
    SBlackboard m_Blackboard;
    float m_HeavyLanding_FallTime;
    CControlParameters* m_ControlParameters;
    bool m_FreezeFrameSafetyBool;
    CVector3f m_HipsPfxOffsetMS;
    float m_WaterLevel;
    CVector3f m_CustomUpStart;
    CVector3f m_CustomUpEnd;
    float m_CustomUpStartCursorPosition;
    float m_CustomUpEndCursorPosition;
    std::vector<std::pair<IPfxGameObject *,float>,std::allocator<std::pair<IPfxGameObject *,float> > > m_ImpactCooldowns;
    char m_CurrentMotionState;
    const char m_DefaultMotionState;
    CAnimationAlignmentHelper m_AlignmentHelper;
    CCharacterSounds* m_CharacterSounds;
    int32_t m_SoundGroup;
    int32_t m_SoundPresetID;
    CCharacterVocals* m_CharacterVocals;
    uint32_t m_VoiceOverId;
    int32_t m_VoiceOverResourceID;
    uint32_t m_DefaultContextBits;
    bool m_AiEntityEnabled;
    CAiCharacterEntity m_AiEntity;
    CLookAtIKDirector* m_LookAtDirector;
    float m_PenetrationTime;
    std::vector<CCharacter::SMeleeLoopEffect,std::allocator<CCharacter::SMeleeLoopEffect> > m_MeleeLoopEffects;

    private: 
    CHealthWrapper* m_HealthWrapper;

    protected: 
    std::vector<SObjectID,std::allocator<SObjectID> > m_GiveItems;
    SObjectID m_TargetInfo;
    std::weak_ptr<CStateContainerDataTargetInfo> m_wpTargetInfo; // BOOST PTR
    CCharacterTargetHandler m_targetHandler;
    CLocomotionGraph m_LocomotionGraph;
    std::weak_ptr<COutline> m_BerserkOutline; // BOOST PTR
    float m_DetectedByPlayerMaxRadius;
    float m_DetectedByPlayerCooldown;
    float m_TimeSinceDetectedByPlayer;
    int32_t m_DetectedByPlayerProgress;
    bool m_DetectedByPlayer;

    public: 
    bool m_RagdollPostSimMappingEnabled;
    CSetTransformConstraint m_SetTransformConstraint;
    CAnimatedModel m_AnimatedModel;
    CInteractionUserProxy m_InteractionUserProxy;
    CCharacterIK m_IK;
    bool m_DeformTwistsEnabled;
    CDeformerJointTwister m_DeformerJointTwister;
    std::vector<CSecondaryMotionController *,std::allocator<CSecondaryMotionController *> > m_SecondaryMotionControllers;
    CDamageDecal m_DamageDecal;
    CCharacter::SMatrixSpring m_MatSpring;
    int32_t m_HeadBoneHiIndex;
    int32_t m_HipsBoneHiIndex;
    CRagdollCollisionListener* m_RagdollCollisionListener;
    const NAnimationSystem::SRagdollParams* m_CurrentRagdollParams;
    CHashString m_CurrentRagdollParamsID;
    std::shared_ptr<NAnimationSystem::CRagdollInstanceImpl> m_Ragdoll; // BOOST PTR
    CPfxRagdollProxyPhantom m_PfxRagdollProxyPhantom;
    float m_TimeBeforeSystemGroupReset;
    float m_TimeBeforeNoCollideIDReset;
    uint32_t m_OriginalSystemGroup;
    uint32_t m_CurrentSystemGroup;
    uint32_t m_PendingSystemGroup;
    uint32_t m_OriginalNoCollideID;
    uint32_t m_CurrentNoCollideID;
    uint32_t m_PendingNoCollideID;
    SGameEffectContainer* m_FireFlameEffectContainer;
    SGameEffectContainer* m_FireSoundEffectContainer;
    SGameEffectContainer* m_DazeEffectContainer;
    SGameEffectContainer* m_GibEffectContainer;
    std::vector<CCharacter::SSpellTargetCharacterInfo,std::allocator<CCharacter::SSpellTargetCharacterInfo> > m_SpellTargetCharacterInfo;

    private: 
    unsigned char m_FadeOut : 1; /* BitPos=0 */
    unsigned char m_FadeIn : 1; /* BitPos=1 */
    unsigned char m_FadeInResetOpacity : 1; /* BitPos=2 */
    float m_Opacity;
    uint32_t m_LastAnimStateChange;
    CDamageInflictor m_LastDamage;
    CHashString m_DestroyedDamageType;
    CFootstepFX m_FootstepFX;
    bool m_UsePostApplyRenderTransform : 1; /* BitPos=0 */
    CMatrix4f m_PostApplyRenderTransform;
    bool m_ModelMatrixInitialized;
    unsigned char m_SavedMinLod;
    unsigned char m_SavedOffsetLod;
    bool m_DynamicLODOverridden;
    float m_SavedScaleLod;

    // static variables
    public: 
    static CHashString FullBody;
    static CHashString UpperBody;
    static CHashString ALL_LAYERS;
    static CHashString RagdollRB_Head;
    static CHashString RagdollRB_Spine1;
    static CHashString RagdollRBGroup_Head;
    static CHashString RagdollRBGroup_Torso;
    static CHashString RagdollRBGroup_LeftArm;
    static CHashString RagdollRBGroup_RightArm;
    static CHashString RagdollRBGroup_LeftLeg;
    static CHashString RagdollRBGroup_RightLeg;
    static const uint32_t MAX_DECAL_TO_BONE_MAPPING_SLOTS;
    static uint32_t sIntervalCounter;
    static uint32_t sCreationID;
    static CHashString on_fire;
    static CHashString on_fire_light;
    static CHashString max_on_fire;
    static CHashString max_on_fire_light;
    static CHashString max_on_fire_buffed;
    static CHashString s_OnFireAct;
    static CHashString s_ForceOffFireAct;
    static bool sDebugBulletDamagesEnabled;
    static bool sDebugTrackMessagesEnabled;
    static float HeightC_FallNoDamage;
    static float VehicleDamageMin;
    static float VehicleDamageFactor;
    static float VehiclePainMin;
    static float VehiclePainFactor;
    static float VehicleDeathSpeed;
    static float VehicleReactSpeed;
    static float m_WeaponDespawnTime;
    static float m_ExplosiveDespawnTime;
    static float m_UpperDecalSpawnDmg;
    static float m_LowerDecalSpawnDmg;
    static float m_BloodDecalDistance;
    static bool m_BloodEnabled;
    static bool m_GibsEnabled;
    static bool m_DoIntervalUpdate;

    private: 
    static const float s_LodLimits[5];
    static const float s_LodScale[5];
    static float HeightD_Jump;
    static float HeightE_Ground;
    static int32_t NofCharacters;
    static const float m_MovementInputThreshold;
    static bool m_DebugHealth;

    public: 
    static HThreadMutexName* m_OnStateTransitionLock;

    protected: 
    static int32_t m_NofDetectedByPlayer;

    public: 
    static uint64_t m_PlayerDeaths;
    static uint64_t m_NPCDeaths;

    private: 
    static unsigned char m_PictureModeMinLod;
    static unsigned char m_PictureModeOffsetLod;
    static float m_PictureModeScaleLod;
    
    // methods
    public: 
    virtual static_string GetKlassName() const;
    virtual const CMatrix4f& GetLocalTransform();
    virtual void SetLocalTransform(const CMatrix4f&);
    virtual bool HasLocalTransform();
    virtual const CRttiTypeId& GetTypeId() const;
    virtual bool IsType(const CRttiTypeId&) const;
    int32_t GetDecalIndexForBoneOffset(const uint32_t);
    int32_t GetSafeIndex(NBone::ESafeBoneIndex) const;
    void GetJoint(NBone::ESafeBoneIndex, NAnimationSystem::CJointInfo&);
    void GetSafeBoneMatrix(NBone::ESafeBoneIndex, CMatrix4f&) const;
    void GetWorldMatrixForBone(NBone::ESafeBoneIndex, CMatrix4f&) const;
    void GetWorldMatrixForBoneBindPose(NBone::ESafeBoneIndex, CMatrix4f&) const;
    void GetWorldMatrixForBoneByHash(const CHashString&, CMatrix4f&) const;
    void GetWorldMatrixForBoneBindPoseByHash(const CHashString&, CMatrix4f&) const;
    void GetLocalMatrixForBoneByHash(const CHashString&, CMatrix4f&) const;
    void GetLocalMatrixForBoneOffset(uint64_t, CMatrix4f&) const;
    float GetFloatTrack(int32_t);
    void AddMenuVariables();
    void RemoveMenuVariables();
    uint32_t GetControllerId(const CHashString&);
    uint64_t GetNumAnimationLayers() const;
    void SetMotionState(CCharacter::EMotionState);
    CCharacter::EMotionState GetMotionState();
    void SetCustomUpStartVector(const CVector3f&, float);
    void SetCustomUpEndVector(const CVector3f&, float);
    void ResetCustomUpVectors();
    int32_t ReplaceModel(uint32_t, const char*);
    void SetModel(int32_t, NModelSystem::CModelInstance*, bool);
    void SetModel(int32_t, const char*, uint32_t, bool);
    virtual void HitByFire(CPhysicsGameObject::SHitByFireData&);
    virtual void HitByFire(float, bool);
    void AddFireBuff(CHashString, float);
    virtual bool HitByBullet(CPhysicsGameObject::SHitByBulletData&);
    virtual void HitByExplosion(CPhysicsGameObject::SHitByExplosionData&);
    virtual float InflictDamage(const CDamageInflictor&);
    void AddBuff(const CHashString&, float);
    void RemoveBuff(const CHashString&);
    void UpdateCharacterStats(float);
    void NotifyShooter(CAmmunition*);
    void PlayHitByFireEffect(const float);
    CAvatar* GetAvatar() const;
    virtual void HandleEvent(const NEvent::CEventImpl*, const NEvent::CEventData&);
    bool MatchEvent(NAnimationSystem::STrackEventData&, const NEvent::CEventImpl*, const NEvent::CEventData&, NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void>&) const;
    void HandleTrackMessage(NAnimationSystem::SAnimationMessageData*);
    CEffectInstance* PlayAttachedEffectOnBone(const CHashString&, const CHashString&);
    virtual void UpdateGraphicsMatrix();
    virtual void SyncGraphicsMatricesToWorld();
    void SetModelMatrix(const CMatrix4f&, bool);
    uint32_t GetAiEntityHandle() const;
    void SetAiEntityEnabled(bool);
    void UpdateAiEntityInstance();
    void UpdateNavMeshObstacle();
    void UpdateHealthWrapper(const float);

    protected: 
    virtual void Init(SGameObjectInitContext*);

    public: 
    void Init(const CHashString&, const CHashString&);
    virtual void PostInit();
    void UpdateVisuals(float);
    void UpdateUserVM(float);
    virtual bool IsAnimationBlendingDone() const;
    bool IsAnimationDone(const CHashString&) const;
    virtual void AttachTo(const CMatrix4f*, void*, NCharacterSystem::CCharacterBase::AttachType, CMatrix4f*, uint32_t);
    void SetYAlignedAttachTo(CMatrix4f*, void*, NCharacterSystem::CCharacterBase::AttachType, uint32_t);
    void AttachToWithCurrentOffset(const CMatrix4f*, void*, NCharacterSystem::CCharacterBase::AttachType, uint32_t);
    virtual void Detach(float);
    void UpdateAttached(const CVector3f&);
    const CVector3f SetupAnimationScaling(const CHashString&, const CMatrix4f&, const CMatrix4f&);
    void CalcAnimationScaling(const CMatrix4f&, const TResourceCachePtr<NAnimationSystem::CAnimationImpl>&, CVector3f&, const CMatrix4f*);
    const CVector3f& ExtractCurrentScalingAnimTranslation(const TResourceCachePtr<NAnimationSystem::CAnimationImpl>&);
    void SetStaticAnimationScaling(const CVector3f&);
    void SetDynamicAnimationScaling(CMatrix4f*, CMatrix4f*, CMatrix4f*);
    void UpdateEquippedProperties(const CSortedVectorMap<CHashString,int>&);
    bool DoAct(const CHashString&, const CHashString&);
    virtual bool DoAct(const CHashString&);
    void QueueAct(const CHashString&, const CHashString&);
    void QueueAct(const CHashString&);
    bool DoActAndModify(const CHashString&, const CHashString&, const CHashString&);
    bool DoActAndModify(const CHashString&, const CHashString&);
    bool TryAct(const CHashString&, const CHashString&);
    virtual bool TryAct(const CHashString&);
    const NAnimationSystem::CTransition* QueryAct(const CHashString&, const CHashString&);
    void SetModifier(const CHashString&, CAnimationRuleSystem::EAnimationModifierType);
    void SetModifier(const CHashString&, const CHashString&, CAnimationRuleSystem::EAnimationModifierType);
    void SetModifier(const CHashString&, const CHashString&);
    void SetModifier(const CHashString&);
    bool IsModifierSet(const CHashString&) const;
    void QueueState(const CHashString&, const CHashString&);
    bool SetState(const CHashString&, const CHashString&, const CHashString&);
    bool SetState(const CHashString&, const CHashString&);
    virtual bool SetState(const CHashString&);
    const CHashString& GetState(const CHashString&) const;
    virtual const CHashString& GetState() const;
    const CHashString& GetStateByIndex(uint32_t) const;
    void UpdateProxyState();
    void SetProxyState(const CPfxCharacterInstance::EProxyState, bool);
    CPfxCharacterInstance::CharacterInput& GetPhysicsInputState();
    virtual IPfxInstance* GetIPfxInstance();
    hkpRigidBody* GetRigidBody();
    void QueueImpulses(const CVector3f*, const CVector3f*);
    void UpdateQueuedImpulses();
    virtual void AddToUpdate();
    virtual bool NeedsUpdate();
    virtual void UpdateRender(SGameObjectRenderContext*);
    virtual void InitTransform(const CMatrix4f&);
    virtual void SetTransform(const CMatrix4f&);
    virtual bool GetTransform(CMatrix4f*);
    virtual const bool GetRenderTransform(CMatrix4f*, const float);
    void SetPostApplyRenderTransform(const CMatrix4f*);
    virtual void Enable(bool);
    virtual bool NotifyOutOfBroadphase() const;
    void SetTransformWithConstraint(const CMatrix4f&);
    CCharacter(const CCharacter&);
    CCharacter();
    virtual ~CCharacter();
    bool ValidForUpdate();
    void UpdateInterval();
    void UpdatePassStateMachines(SGameObjectUpdateContext*);
    void UpdatePassAnimations1(SGameObjectUpdateContext*);
    void UpdatePassAnimations2(SGameObjectUpdateContext*);
    void UpdatePassPrePhysics(SGameObjectUpdateContext*);
    void UpdatePassPostPhysics(SGameObjectUpdateContext*);
    void UpdatePassPostPose(SGameObjectUpdateContext*);
    void SetFloatRegister(int32_t, float);
    float GetFloatRegister(int32_t);
    void SetGlobalXvmFloat(int32_t, float);
    float GetGlobalXvmFloat(int32_t);
    std::shared_ptr<CCharacter> GetSharedRef(); // BOOST PTR
    virtual NModelSystem::CModelInstance* GetModel(uint64_t) const;
    virtual uint64_t GetNumModels() const;
    virtual bool GetModelAABB(CAABox&) const;
    virtual bool GetModelSpaceAABB(CAABox&) const;
    virtual CAnimatedModel* GetAnimatedModel();
    virtual void* GetInterface(uint32_t, uint32_t);
    void UpdateCurrentWeapon();
    void SetVisible(bool);
    bool IsVisible() const;
    void SetDontReactToHit(bool);
    void SetEnableEvent(const NEvent::CReceiveEvent<void,void,void,void,void>&);
    void SetDisableEvent(const NEvent::CReceiveEvent<void,void,void,void,void>&);
    void ValidateWorldPos();
    void VehicleWeaponUpdate();
    bool IsAttachedToLandVehicle() const;
    bool IsAttachedToAirVehicle() const;
    bool IsAttachedToSeaVehicle() const;
    CInventory* GetInventory() const;
    CWeapon* GetWieldedWeapon() const;
    CWeapon* GetSelectedWeapon() const;
    CItemObject* GetWieldedItem() const;
    CItemObject* GetSelectedItem() const;
    bool SelectItem(const CHashString&);
    bool SelectItem(CItemObject*);
    void GiveItem(CItemObject*);
    void RemoveItem(CItemObject*);
    // void ForEachInventoryObject(std::tr1::function<void __cdecl(CCharacter *,CItemObject *)>);
    const CMatrix4f* GetMuzzleMatrix();
    void Revive();
    void GetHeadMatrix(CMatrix4f&) const;
    void GetNeckMatrix(CMatrix4f&) const;
    void GetHipsMatrix(CMatrix4f&) const;
    void GetBodyMatrix(CMatrix4f&) const;
    CVector3f GetHeadPosition() const;
    CVector3f GetNeckPosition() const;
    CVector3f GetBodyPosition() const;
    CVector3f GetRandomBonePosition() const;
    CVector3f GetHipsPosition() const;
    CVector3f GetLeftFootPosition() const;
    CVector3f GetRightFootPosition() const;
    CVector3f GetLeftHandPosition() const;
    CVector3f GetRightHandPosition() const;
    void GetRightAttachBone(CMatrix4f&);
    void GetLeftAttachBone(CMatrix4f&);
    virtual int32_t GetUpdateOrder() const;
    bool DoFireAt(const CVector3f&);
    bool DoFireAtRangedWeaponTargets();
    void DoFireInteractionWeapon();
    bool ShouldSustainFire();
    void DoReloadRH();
    void DoReloadSecondaryRH();
    void DoReloadLH();
    void DoReloadSecondaryLH();
    void DoSelectNextItem();
    void DoSelectPrevItem();
    bool IsThrowingExplosive() const;
    bool IsPlacingExplosive() const;
    void SetGrenadeTargetOffset(const CVector3f&);
    void Wield(const CHashString&, CItemObject*);
    void Wield(const CHashString&);
    void Wield();
    void UnWield();
    void DropWieldedItem();
    void AttachWieldedItemToBone(const CHashString&);
    void OnWield(CItemObject*);
    void OnUnwield();
    void DoAim(const CVector3f&);
    void SetAimingEnabled(bool);
    bool GetAimingEnabled() const;
    bool IsDead(float) const;
    void UpdateCorpseCooling(float);
    bool IsGibed() const;
    void UpdateMyselfTarget();
    void UpdateFreezeFrame(float);
    void ClearIKGains();
    void HandleIKUsage(float);
    virtual void OnDestroyed(CHashString);
    void CheckAndSetDestroyed();
    void OnDespawn();
    void AddLootBag();
    bool HasLoot();
    float GetFallTime() const;
    void ResetDamageDecals();
    void FadeOutDamageDecals(float);
    void ScaleDamageDecalFactors(float);
    bool CanSeePosition(const CVector3f&);
    bool IsPlayer() const;
    void SetPlayer(bool);
    void SetInfMassOnSelf(bool);
    virtual void SetProperties(const CRuntimeContainer&, SGameObjectSetPropertiesContext*);
    void SetPropertiesSGiveItem(const CRuntimeContainer&);
    void SetPropertiesSMeleeLoopEffect(const CRuntimeContainer&);
    void DrawDebugName();
    void DrawPfxLayerName();
    uint64_t GetNofRuleSystems();
    void SetDebugRuleSystem(int32_t, bool);
    void SetDebugRuleSystems(bool);
    void SetDebugModifiers(bool);
    bool GetGhostMode() const;
    void ForceNeutralState();
    void ForceState(CHashString&, bool, bool);
    void AbortDriving();
    void SetGodMode(bool);
    bool GetGodMode() const;
    virtual bool IsPlayerControlled() const;
    bool GetClosestPoint(const CPfxRigidBody*, CVector3f&, CVector3f&);
    CHashString GetHitReactionZone(const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&);
    void HitReaction(const CVector3f, const float, CHashString, CHashString, CVehicle*, const float, const bool);
    void HandleHitReaction(CHashString);
    void HandleHitReactionVehicle(float, CVector3f);
    const IPfxGameObject::SHitReactInfo& GetLatestHitReactInfo();
    const SSpellHitInfo& GetLatestSpellHitInfo();
    const SExplosionHitData& GetLatestExplosionHitData();
    const SBulletHitData& GetLatestBulletHitData();
    const CPhysicsGameObject::SHitByFireData& GetLatestFireHitData();
    bool IsLatestFireHitDataValid();
    const float GetLatestSuccesfullSPellGivenTime();
    void SetLatestSuccesfulSpellReceivedTime(const float);
    const float GetLatestSuccesfullSPellReceivedTime();
    void UpdateLastSpellHitInfo(const std::weak_ptr<CGameObject>&, const CVector3f&, const CVector3f&, uint32_t); // BOOST PTR on CGameObject
    bool HasActiveGrenade() const;
    void SetHeightOverGround(float, bool);
    float GetHeightOverGround(bool) const;
    void ForceUpright();
    int32_t GetMaterialBelow() const;
    const CVector3f& GetSurfaceNormal() const;
    bool AlignWorldMatrixToGround(float);
    void SetCharacterGravity(float);
    void Pause();
    void UnPause();
    void SetPaused(bool);
    virtual std::shared_ptr<CVehicle> GetVehicle() const; // BOOST PTR
    CVehicle* GetVehiclePtr() const;
    bool IsAttachedToVehicle() const;
    void ClearAttachedAnimScaleStuff();
    virtual void ResetController();
    void KickOutFromSequence();
    bool GetEnabled() const;
    virtual void SetOpacity(float);
    float GetOpacity() const;
    CAvatar* SetAvatar(CAvatar*);
    float CalculateVelocityGain();
    void SetFaction(int32_t);
    int32_t GetFaction() const;
    int32_t GetCharacterLevel() const;
    bool CanBeAutoDisabled() const;
    virtual IPfxGameObject* GetPfxGameObject();
    bool IsHeadShot(const SCastRayInfo*);
    void AddAnimStateObserver(IAnimStateTransitionObserver*);
    void RemoveAnimStateObserver(IAnimStateTransitionObserver*);
    void OnThrowThunderStick();
    void OnThrowStone();
    void OnSpawnItem(const CHashString&);
    void OnPlantLandMine();
    void OnDisarmLinkTarget();
    bool GetUseFinalTransparency() const;
    void SetUseFinalTransparency(bool);
    float GetCurrentAccuracy() const;
    void SetCurrentAccuracy(float);
    float GetCurrentInternalAccuracy() const;
    void SetCurrentInternalAccuracy(const float);
    float GetMaxAccuracy() const;
    void SetMaxAccuracy(float);
    float GetMinAccuracy() const;
    void SetMinAccuracy(float);
    void ModifyCurrentAccuracy(float);
    void ModifyCurrentInternalAccuracy(float);
    void HandleGettingUpFromRagdoll();
    void CommitDelayedCharacterPhysicsOperations();
    CAnimationRuleSystem* GetRuleSystem(const CHashString&) const;
    CAnimationRuleSystem* GetRuleSystemByIndex(uint32_t) const;
    CAnimatedBodyPart* GetBodyPart(const CHashString&) const;
    CAnimatedBodyPart* GetBodyPartByIndex(uint32_t) const;
    CAnimationDriverTransition* GetAnimationDriver(const CHashString&) const;
    CAnimationDriverTransition* GetAnimationDriverByIndex(uint32_t) const;
    CLocomotionGraph* GetLocomotionGraph();
    void ReplaceLayerState(int32_t, std::shared_ptr<NAnimationSystem::CStateMachineInstance>&, TResourceCachePtr<NAnimationSystem::CAnimationSet>&); // BOOST PTR
    void SetupForSequence();
    bool InSequence() const;
    void ReplaceAnimationLayer(const CHashString&, const CHashString&, const CHashString&);
    void ResetForSequence3(const CHashString&, const char*, const char*);
    void ResetAfterSequence3();
    void HandleAnimationEvent(const CHashString&);
    void SetUpdatePhysics(bool);
    void SetGhostMode(bool);
    bool DoActReactHitFly(CHashString);
    bool DoActReactHitFall();
    void UpdateRagdollCollisionListenerState();
    virtual void DoReactToHit(const IPfxGameObject::SHitReactInfo&);
    void TryCollisionEffect(const CVector3f&, const float);
    int32_t GetSoundGroup();
    void SetSoundGroup(int32_t);
    int32_t GetSoundPresetID() const;
    void InitAnimationsSystem(const CHashString&);
    void InitRagdollAndIK(const CHashString&);
    virtual void UpdateIntegratingPhysics(float);
    virtual void UpdateAttachedPhysics(float);
    virtual void UpdateRuleSystem();
    void UpdateStateTasksInRange(float, uint32_t);
    void UpdateRenderStateTasks(float, float);
    void SwapContextBits();
    void ClearAnimationModifiers();
    void UpdatePropEffects();
    void UpdatePropTransforms();
    void InitPropTransforms();
    bool IsRotationEnabled();
    virtual void DoRotateToward(float);
    void UpdateGroundInfo(bool);
    void UpdateMaterialBelow();
    void CalculateHeightOverGround();
    void CheckPenetrations();
    void UpdateModelVisibility();
    void UpdateAOVolumes(float, const CMatrix4f&);
    void UpdateCharacterEffects(float, const CMatrix4f&);
    int32_t GetClosestBoneIndex(const CMatrix4f&);
    void CastSpell(CHashString, std::vector<CCharacter *,std::allocator<CCharacter *> >&, const CHashString*);
    void CastSpell(CHashString, CHashString*);
    float CalculateSpellDamage(CHashString, uint32_t*);
    float CalculateSpellResistance(CHashString);
    bool CastSpellBuff(CHashString, CCharacter*, uint32_t*);
    bool CastSpellBuffGuaranteed(CHashString, CCharacter*);
    bool CalculateSpellBuffProc(CHashString, CCharacter*, uint32_t*);
    float CalculateSpellBuffValueMultiplier(CHashString);
    float GetCriticalDamageMultiplier();
    bool IsImmuneToBuff(CHashString);
    int32_t GetAiBaseUpgradeLevel();
    bool GetIsHostileEvenIfAlliedFaction();
    void SetSavedTiltTowardsTargetId(uint64_t);
    uint64_t GetSavedTiltTowardsTargetId();
    const TResourceCachePtr<NAnimationSystem::CSkeletonImpl>& GetSkeleton() const;
    void SetInPlayerUpgrade(bool);
    void UpdateAimConstraints(float);
    bool GetDeadDespawnTime(float&);
    virtual CPhysicsGameObjectListenerContainer& GetGameObjectListenerContainer();
    void AddBoneOffset(const CBoneOffsetAlias::SBoneOffset&);
    void RemoveBoneOffset(const CHashString&);
    int32_t FindBoneOffset(const CHashString&) const;
    void PlayAttachedEffect(const CVector3f&, const CVector3f&, const CHashString&, int32_t);
    CEffectInstance* PlayAttachedEffect(const CHashString&, int32_t, const CMatrix4f*);
    void StopAttachedEffect(CEffectInstance*);
    void ClearAttachedEffect();
    void AttachExternItemToBone(CItemObject*, CHashString);
    void ApplyImpulseToSOParent(const CVector3f&);
    void ApplyImpulseToSOAGoal(const CVector3f&);
    bool DoReload(const std::shared_ptr<CWeapon>&); // BOOST PTR
    CGameObject* GetLinkTarget() const;
    void SetLinkTarget(CGameObject*);
    void MoveLinkSourceFirst(CGameObject*);
    int32_t GetLinkSourceCount() const;
    CGameObject* GetLinkSource(int32_t) const;
    void AddLinkSource(CGameObject*);
    void RemoveLinkSource(CGameObject*);
    void DebugLinks(float);
    void DebugMeleeTargeting(float);
    void UpdateHitReactions(float);
    void GibIfDestroyed(CVector3f);
    float GetDamageFromImpact(float);
    void AddAnimationTriggerEvent(uint32_t, const CHashString&);
    void RemoveAnimationTriggerEvent(uint32_t);
    void UpdateQueuedAnimationEvents();
    void PrintDebug();
    void PrintDebugRuleSystems();
    void PrintDebugHealth();
    void DebugRenderFloatSlots();
    void SetDynamicLODProperties(unsigned char, unsigned char, float);
    void EnableDynamicLODOverride(unsigned char, unsigned char, float);
    void DisableDynamicLODOverride();

    private: 
    void SendDamageReceivedEvent(const CDamageInflictor&, float, bool);
    void SendDamageDealtEvent(const CDamageInflictor&, float, bool);
    float CalculateLod(const CVector3f&) const;
    void InitBlackboard();

    public: 
    void UpdateSounds(const float);
    void SetCharacterVoiceOverId(uint32_t);
    void SetCharacterVocals(CCharacterVocals*);

    protected: 
    void UpdateDetectedByPlayer(const float);

    public: 
    std::shared_ptr<CStateContainerDataTargetInfo> GetAimSystemTargetInfo(); // BOOST PTR
    bool IsDetectedByPlayer() const;
    NCharacterSystem::CAnimationControl* GetAnimController();
    uint32_t GetFullBodyIndex();
    bool FadeIn(float);
    bool FadeOut(float);
    bool IsFaded() const;
    std::shared_ptr<NAnimationSystem::IIKTwoJoints>& GetTwoJointsIKChain(CCharacterIK::ETypes); // BOOST PTR
    void UpdateIKTargets(float);
    int32_t GetBoneIndex(const CHashString&) const;
    bool HasBone(const CHashString&) const;
    int32_t GetFloatTrackIndex(int16_t) const;
    void GetBoneMatrix(int32_t, CMatrix4f&) const;
    int32_t HitBoneAt(const CVector3f&, const CVector3f&, CVector3f&);
    void UpdateWorldMatrixSpring(float, float);
    void UpdateAnimations(float);
    void UpdateIK(float);
    void SetDeformTwistsEnabled(bool);
    void UpdateDeformTwists();
    void UpdateSecondaryMotion(SGameObjectUpdateContext*);
    void RegisterSecondaryMotionController(CSecondaryMotionController*);
    CFootstepFX& GetFootstepFX();
    void UpdateSkinning(float);
    void UpdateRotationFromAnimation();
    bool VerifyRagdollPelvis(float);
    void PrePhysicsUpdateRagdoll(float);
    void PostPhysicsUpdateRagdoll(float);
    void UpdateRagdoll(float);
    void StartPartialRagdollEnable();
    void UpdatePartialEnabledRagdoll(const float&);
    void DebugDrawPartialRagdollEnable();
    bool VerifyRagdollConstraints(bool, float);
    void FixupRagdollConstraints(float);
    void SyncWorldMatrixToRagdoll();
    void SyncRagdollToWorldMatrix();
    const std::shared_ptr<NAnimationSystem::CRagdollInstanceImpl>& GetRagdoll(); // BOOST PTR
    void SetCurrentRagdollParamsID(const CHashString&, bool, bool);
    void SetRagdollParams(const NAnimationSystem::SRagdollParams&);
    const CHashString& GetCurrentRagdollParamsID();
    void DoSyncRagdollState(float);
    bool HasRagdoll() const;
    void InitRagdollVelocity();
    void PrepareRagdoll(const TResourceCachePtr<NAnimationSystem::CSkeletonImpl>&);
    void SyncToRagdoll(const std::shared_ptr<NAnimationSystem::CRagdollInstanceImpl>&, const NAnimationSystem::CRagdollInstanceImpl*&); // BOOST PTR
    bool GetVelocityForBone(int32_t, CVector3f&, CVector3f&) const;
    std::weak_ptr<CPfxRigidBody> GetRagdollRigidBodyForHiBone(int32_t); // BOOST PTR
    std::weak_ptr<CPfxRigidBody> GetRagdollRigidBodyForLoBone(int32_t); // BOOST PTR
    bool GetRagdollPositionForBone(int32_t, CVector3f&) const;
    const char* GetRagdollProxyShapeName(const hkpShape*);
    CPfxRagdollProxyPhantom& GetRagdollProxyPhantom();
    void SyncRagdollProxyTransform();
    void SyncRagdollProxyPose();
    virtual void SetWaterLevel(float);
    void SetSystemGroupAndResetTimer(uint32_t);
    uint32_t GetCurrentSystemGroup() const;
    uint32_t GetOriginalSystemGroup() const;
    bool IsDueForSystemGroupReset() const;
    void SetSystemGroupResetTimer(float);
    void SetNoCollideIDResetTimer(float);
    void SetNoCollideIDAndResetTimer(uint32_t);
    void UpdateNoCollideIDResetTimer(float);
    void UpdateSystemGroupResetTimer(float);
    virtual void OnAttached(uint32_t);
    virtual void OnDetached(float);
    virtual void UpdatePhysics(float);
    void UpdateInteractionPhysics(float, bool);
    virtual void UpdateMovement(float, bool);
    void UpdatePhysicsInput(float, const CMatrix4f&);
    void UpdatePhysicsInputAnimation(float, const CMatrix4f&);
    void UpdatePhysicsInputSteering(float, const CMatrix4f&);
    void AdvancePhysics(float, CMatrix4f&);
    void PositionPhysics(float, const CMatrix4f&);
    void AdvanceAndPositionPhysics(float, const CMatrix4f&);
    bool GetGroundContact() const;
    int32_t GetGroundObjectType() const;
    void RenderEditorSpecifics(bool);
    const CInteractionUserProxy* GetInteractionUserProxy() const;
    CInteractionUserProxy* GetInteractionUserProxy();
    CHealthWrapper* GetHealthWrapper() const;
    void SendTrackEvent(const char*, float, const char*);
    void ReleaseContainers();
    void SetLastUsedAnimation(uint32_t);
    uint32_t GetLastAnimationStateChange() const;
    CCharacter& operator=(CCharacter&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    
    public: 
    static static_string GetClassNameStatic();
    static const CRttiTypeId& TYPE_ID();
    static void InitializeConsoleVariables();
    static void UninitializeConsoleVariables();
    static uint32_t GetTotalNofCharacters();
    static void OnStateTransition(CAnimationRuleSystem*, NAnimationSystem::CState*, NAnimationSystem::CState*);
};

#endif
