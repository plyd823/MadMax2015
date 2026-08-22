#include "Player.h"

#ifdef BATCH_GAME_826130353_19_50

uint32_t HashString(const char *str);

float SpeedLerp(float from, float to, float units_per_second, float dt, bool clamp_to_01);

uint32_t GetFastHash(const char* str);

bool GameFactionsIsHostile(int firstFaction, int secondFaction);

bool CPlayer::GetCharacterControllerMapping() const {
    return false;
}

void CPlayer::SetIsFiringAtAvatar(CCharacter* evil_character) {
    return;
}

Input::CInputActionMap* CPlayer::GetInputActionMap() {
    Input::IInputDeviceManager* inputMgr = CAvaSingle<CDeviceManager>::Instance->GetInputManager();
    return inputMgr->GetActionMap(Input::HASH_player);
}

void CPlayer::UpdateRender(float dt, float dtf, float real_dt) {
    CCameraControlManager* pCamMgr = CAvaSingle<CCameraControlManager>::Instance;
    float opacity = pCamMgr->GetPlayerOpacity();

    float currOpacity = this->m_CurrentPlayerOpacity;

    if(0.5f <= opacity)
    {
        currOpacity = SpeedLerp(currOpacity, opacity, dt, 1.0f, true);

        if(currOpacity < 0.2f)
        {
            if (opacity < 0.2f)
            {
                currOpacity = 0.0f;
            }
            else
            {
                currOpacity = 0.2f;
            }
        }
        this->m_CurrentPlayerOpacity = currOpacity;
    }
    else
    {
        currOpacity = SpeedLerp(currOpacity, 0.0f, dt, 1.0f, true);

        if(currOpacity < 0.2f)
        {
            currOpacity = 0.0f;
        }

        this->m_CurrentPlayerOpacity = currOpacity;
    }

    CAvatar::UpdateRender(dt, dtf, real_dt);
}

bool CPlayer::IsDead()
{
    CCharacter* pCharacter = this->m_Character;
    return pCharacter->IsDead(2.0);
}

const CRttiTypeId& CPlayer::TYPE_ID() {
    static const CRttiTypeId s_type_id(HashString("CPlayer"));
    return s_type_id;
}

const CRttiTypeId& CPlayer::GetTypeId() const {
    return CPlayer::TYPE_ID();
}

void CPlayer::RegisterPickup(uint32_t weapon_id, uint32_t ammo_change, uint32_t ammo_total) {
    int count = this->m_NumGUIPickups;

    if (count <= 3)
    {
        this->m_GUIPickups[count].m_WeaponId = weapon_id;
        this->m_GUIPickups[count].m_Change = ammo_change;
        this->m_GUIPickups[count].m_Total = ammo_total;

        this->m_NumGUIPickups = count + 1;
    }
};

uint32_t CPlayer::GetNumRegisteredPickup() const {
    return static_cast<uint32_t>(m_NumGUIPickups);
}

const SGameGuiAmmoPickup& CPlayer::GetPickup(uint32_t pickup_index) const {
    return this->m_GUIPickups[pickup_index];
}

void CPlayer::ClearPickups() {
    this->m_NumGUIPickups = 0;
}

float CPlayer::GetCombatTriggerTimer() const {
    CCharacter* pCharacter = this->m_Character;
    return pCharacter->GetFloatRegister(this->m_CombatTriggerRegisterIndex);
}

void CPlayer::UpdateDebug(float dt) {
    bool freeze = this->m_FreezeHealth;
}

void CPlayer::UpdateGamezoneInformation() {
    return;
}

void CPlayer::UpdateSoundFocus() {
    return;
}

int32_t CPlayer::GetFaction() {
    return this->m_Character->GetFaction();
}

const CMatrix4f& CPlayer::GetWorldMatrix() {
    return this->m_Character->GetWorldMatrixRef();
}

void CPlayer::SetWorldMatrix(const CMatrix4f& m) {
    this->m_Character->SetTransform(m);
}

bool CPlayer::IsDestroyed() {
    return this->m_Character->m_CurHealth <= 0;
}

void CPlayer::SetAimMode(int32_t mode) {
    this->m_AimMode = mode;
}

void CPlayer::ReInitCharacter() {

}

void CPlayer::ReInit() {
    ReInitCharacter();
    this->m_Character->Revive();

    this->m_GuiDeathRunActiveProfileId = 0;

    this->m_IsMapRuntimeBlocked = false;
}

void CPlayer::RenderMovementInput(float dt) {
    return;
}

void CPlayer::ResetMovementInputTrail() {
    return;
}

void CPlayer::UpdateMotionGraphs(float dt) {
    return;
}

void CPlayer::RenderMotionGraphs(float dt) {
    return;
}

void CPlayer::Enable(bool enable) {
    this->m_Enabled = enable;

    CCharacter* pCharacter = this->m_Character;

    if(pCharacter != nullptr) {
        pCharacter->Enable(enable);
    }
}

CPlayer::EDifficulty CPlayer::GetDifficulty() const {
    return this->m_Difficulty;
}

void CPlayer::SetDifficulty(CPlayer::EDifficulty difficulty) {
    this->m_Difficulty = difficulty;

    NNetwork::COnlineManager* pOnlineMgr = CAvaSingle<NNetwork::COnlineManager>::Instance;

    GlobalDifficultySetting event;
    event.difficulty = static_cast<int32_t>(difficulty);

    pOnlineMgr->AddMetricData(&event);
}

void CPlayer::SetInvulnerable(bool invulnerable){
    CCharacter* pCharacter = this->m_Character;

    if(pCharacter)
    {
        pCharacter->m_Invulnerable = invulnerable;
    }
}

bool CPlayer::IsInvulnerable() const {
    CCharacter* pCharacter = this->m_Character;

    if(pCharacter)
    {
        return pCharacter->m_Invulnerable;
    }
    return false;
}

void CPlayer::PrintDebugVelocity(float dt) {
    return;
}

void CPlayer::RenderDebugBoneMatrices() {
    return;
}

void CPlayer::ResetInvulnerableTimer() {
    CCharacter* pCharacter = this->m_Character;

    this->m_StartInGodModeTimer = 5.0f;
    pCharacter->m_Invulnerable = true;
}

bool CPlayer::IsUpdatingCameraController() const {
    if(!this->m_Enabled) return false;

    return !this->m_WaitForLandscapeLoad;
}

int32_t CPlayer::GetCurrentStateCameraId(int32_t index) const {
    return this->m_CurrentStateCameraIds[index];
}

void CPlayer::SetCurrentStateCameraId(int32_t index, int32_t camera_id) {
    this->m_CurrentStateCameraIds[index] = camera_id;
}

int32_t CPlayer::GetContextualCameraId(CPlayer::EContextualCamera camera_type) const {
    return this->m_ContextualCameras[camera_type];
}

void CPlayer::CalculateReviveCost(float& actual_cost, float& default_cost) {
    actual_cost = 0.0f;
    default_cost = 0.0f;
}

void CPlayer::SetCombatSessionId(unsigned long long session_id) {
    this->m_CombatSessionId = session_id;
}

void CPlayer::OnActionsRemap() {
    if(this->m_ActiveInputActionOverides.begin() != this->m_ActiveInputActionOverides.end())
    {
        OverrideActionsApplyMerge();
    }
}

void CPlayer::OverrideActions(CInputActionOverride* iao) {
    return;
}

void CPlayer::UpdateMoveDirection(float dt) {
    if (dt <= 0.0f) return;

    CCharacter* pCharacter = this->m_Character;
    if(pCharacter == nullptr) return;
    
    CVector2f input(0.0f, 0.0f);
    Input::IInputDeviceManager* pIDMgr = CDeviceManager::GetInputManager();
    Input::CInputActionMap* pActionMap = Input::IInputDeviceManager::GetActionMap(Input::HASH_player);

    if(pActionMap != nullptr) {
        float right = pActionMap->GetValue(0xa97a58ba);
        float left = pActionMap->GetValue(0x24b2ac1b);
        float up = pActionMap->GetValue(0x2a6b81fb);
        float down = pActionMap->GetValue(0x16bbbb1c);

        input.x = right - left;
        input.y = up - down;
    }

    float inputMagnitude = sqrtf((input.x * input.x) + (input.y * input.y));
}

void CPlayer::FixupRagdollConstraints(float dt) {
    return;
}

void CPlayer::OnForceNeutralState() {
    return;
}

bool CPlayer::DoReactToHit(const IPfxGameObject::SHitReactInfo& info) {
    return false;
}

void CPlayer::DoActReactHitFly() {
    return;
}

void CPlayer::HitByExplosion(CPhysicsGameObject::SHitByExplosionData& data) {
    if (data.m_Damage > 0.0f) {
        SEventID eventID(0x52d877b2, 0);
    
        NEvent::CEventData eventData(0xffffffffff, nullptr, nullptr, nullptr, nullptr, nullptr);
        CAvaSingle<CEventSystem>::Instance->SendEvent(&eventID, 1, eventData);
    }
}

void CPlayer::OnDeath(CHashString type) {
    uint32_t deathType = 0x55d68f0d;
    SEventID eventID(deathType, 0);
    
    NEvent::CEventData eventData(0xffffffffff, nullptr, nullptr, nullptr, nullptr, nullptr);

    CAvaSingle<CEventSystem>::Instance->SendEvent(&eventID, 1, eventData);
        
    size_t count = 0;
    auto iterator = m_LastDeathTimes.begin();
    auto endIterator = m_LastDeathTimes.end();

    while (iterator != endIterator) {
        count++;
        iterator++;
    }

    if(count > 2) {
        m_LastDeathTimes.pop_front();
    }

    uint32_t gameTime = CAvaSingle<Base::CClock>::Instance->GetGameTime(true);

    m_LastDeathTimes.push_back(gameTime);

    this->m_ReviveCostValuesDirty = true;
}

bool CPlayer::IsType(const CRttiTypeId& id) const {
    return false;
}

void CPlayer::GetHorizonDirection(CVector3f& dir) {
    return;
}

bool CPlayer::HitByBullet(CPhysicsGameObject::SHitByBulletData& data) {
    return false;
}

void CPlayer::PostWorldMatrixUpdateCallback(float dt) {
    return;
}

bool CPlayer::InCombat() {
    CCharacter* pCharacter = this->m_Character;

    CCharacterManager* pCharMgr = CCharacterManager::Instance;
    float combatRange = this->m_CombatTriggerEnemyRange;
    float rangeSquared = combatRange * combatRange;

    const CMatrix4f& selfMatrix = pCharacter->GetWorldMatrixRef();
    float selfX = selfMatrix.m30;
    float selfY = selfMatrix.m31;
    float selfZ = selfMatrix.m32;

    CCharacter* pItChar = pCharMgr->GetFirstCharacter();

    while (pItChar != nullptr)
    {
        if (pItChar != pCharacter)
        {
            if (!(pItChar->m_CurHealth <= 0.0f))
            {
                int selfFaction = pCharacter->GetFaction();
                int otherFaction = pCharacter->GetFaction();

                if(GameFactionsIsHostile(selfFaction, otherFaction))
                {
                    const CMatrix4f& otherMatrix = pItChar->GetWorldMatrixRef();
                    float otherX = otherMatrix.m30;
                    float otherY = otherMatrix.m31;
                    float otherZ = otherMatrix.m32;

                    float diffX = otherX - selfX;
                    float diffY = otherY - selfY;
                    float diffZ = otherZ - selfZ;

                    float distSq = (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ);

                    if(rangeSquared > distSq)
                    {
                        return true;
                    }
                }
            }
        }
        pItChar = pCharMgr->GetNextCharacter();
    }

    return false;
}

void CPlayer::RemoveFromRangeMap(CCharacter* c) {
    return;
}

void CPlayer::GetTransform(CMatrix4f& transform) {
    return;
}

void CPlayer::UpdateControlParams() {
    return;
}

void CPlayer::UpdateController(float dt) {
    return;
}

void CPlayer::UpdatePostPhysics(float dt) {
    return;
}

void CPlayer::UpdateNavMeshMeleeObstacle() {
    return;
}

void CPlayer::InitCombatTriggers(const CRuntimeContainer& p) {
    int firstHash = 0xc611961;
    int secondHash = 0x45e3551e;
    int thirdHash = 0x21b0ad46;
}

void CPlayer::AddToSmallSceneRender() {
    return;
}

void CPlayer::LoadAccuracyMods(const CRuntimeContainer& p) {
    return;
}

void CPlayer::LoadAlertLevelValues(const CRuntimeContainer& p) {
    return;
}

void CPlayer::Init(const CRuntimeContainer& player_container) {
    return;
}

void CPlayer::SetPaused(bool paused) {
    CCharacter* pCharacter = this->m_Character;

    if(pCharacter) {
        this->m_Enabled = !paused;
        pCharacter->SetPaused(paused);
    }
}

void CPlayer::HandleConsoleEvents(const NEvent::CEventImpl* event, const NEvent::CEventData& data) {
    return;
}

void CPlayer::Save(CSaveContext& save_cont) {
    return;
}

void CPlayer::UpdateGroundContact() {
    return;
}

void CPlayer::UpdatePlayerEffects(float dt) {
    return;
}

bool CPlayer::IsInBalloon() const {
    CInteractionUserProxy* pInteractionProxy = &this->m_Character->m_InteractionUserProxy;
    CGameObject* pGO = pInteractionProxy->GetContext();

    if (pGO != nullptr) {
        return pGO->IsTagged(GetFastHash("Balloon"));
    }
    
    return false;
}

float CPlayer::GetFuryEventVariationMultiplier(CHashString event_name) {
    // size_t i;

    // for (i = 0; i < this->m_FuryEventQueue.size(); i++) {
    //     if (this->m_FuryEventQueue[i] == event_name) {
    //         break;
    //     }
    // }

    size_t count = 0;

    for (auto it = m_FuryEventQueue.begin(); it != m_FuryEventQueue.end(); ++it) {
        if (*it == event_name) {
            count++;
        }
    }

    if (count == 0) {
        return 0.5f;
    }

    return count * 0.25f * 0.4f + 0.5f;
}

int32_t CPlayer::GetFuryEventCount(CHashString event_name) {
    auto it = this->m_FuryEventCounter.find(event_name);
    if(it != this->m_FuryEventCounter.end()) {
        return it->second;
    }
    return 0;
}

void CPlayer::PatchMapEnabled() {
    int x; 

    this->m_IsMapEnabled = !this->m_IsMapRuntimeBlocked;

    int enabledState = this->m_IsMapEnabled ? 1 : 0;

    if (NGlobalDictionary::Exists(0xb8e3941b)) {
        int dummy;

        if(NGlobalDictionary::Get<int>(0xb8e3941b, dummy) == NGlobalDictionary::EGLOBALDICTIONARY_OK) {
            if (enabledState != dummy) {
                NGlobalDictionary::Update<int>(0xb8e3941b, enabledState);
            }
        }
    }
    else {
        NGlobalDictionary::Put<int>(0xb8e3941b, enabledState);
    }
}

void CPlayer::UpdatePrePhysics(float dt) {
    return;
}

void CPlayer::Reset(const CHashString* state) {
    return;
}

void CPlayer::ClearFuryEventCounters() {
    return;
}

CPlayer::~CPlayer() {
    return;
}

void CPlayer::HandleEvent(const NEvent::CEventImpl* event, const NEvent::CEventData& data) {
    return;
}

CPlayer::CPlayer() {
    return;
}

void CPlayer::Load(const CSaveContext& save_cont) {
    return;
}

void CPlayer::SensedBy(CCharacter* c, const float detectiveness, const float range) {
    if(detectiveness > this->m_CampThreatValues.m_DetectedValue) {
        this->m_CampThreatValues.m_DetectedValue = detectiveness;
    }

    size_t oldSize = this->m_CampThreatValues.m_EnemyRangeMap.size();
    this->m_CampThreatValues.m_EnemyRangeMap[c] = range;

    if (this->m_CampThreatValues.m_EnemyRangeMap.size() != oldSize) {
        this->m_CampThreatValues.m_Dirty = true;
    }
}

void CPlayer::OverrideActionsGrowList(CInputActionOverride* iao) {
    return;
}

void CPlayer::RecordFuryEvent(CHashString event_name) {
    return;
}

void CPlayer::ClearOverrideActions(CInputActionOverride* iao) {
    return;
}

#endif
