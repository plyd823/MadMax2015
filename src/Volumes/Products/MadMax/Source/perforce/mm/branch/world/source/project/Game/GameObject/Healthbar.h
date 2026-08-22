#ifndef PROJECT_GAME_HEALTHBAR_H
#define PROJECT_GAME_HEALTHBAR_H

#include "Base/Misc/Event.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/GameObject.h"
#include "AvaCore/Math/Matrix.h"
#include "AvaCore/Types/ObjectID.h"
#include "project/Game/GameObject/TurnTakerGameObject.h"

enum EHealthbarType : int32_t {
    VEHICLE = 0x0000,
    FOLLOW_CHAR = 0x0001,
    BIGBOSS = 0x0002,
    BIGBOSS_SCROTUS = 0x0003,
    BIGBOSS_STANKGUM = 0x0004,
    BIGBOSS_TENDERLOIN = 0x0005,
    ON_INFOBOX = 0x0006,
    AIMED_AT_STRUCTURE = 0x0007,
};

class CHealthbar : public CGameObject, public NEvent::CEventHandler {
    protected:
    CMatrix4f m_LocalTransform;
    CMatrix4f m_WorldMatrix;

    private:
    CMatrix4f m_LastRenderTransform;
    bool m_Enabled;
    bool m_Registered;
    EHealthbarType m_Type;
    SObjectID m_InfoboxId;
    uint64_t m_DisplayObjectId;
    bool m_ShowOnInfobox;
    SObjectID m_TargetId;
    bool m_ShowOnlyWhenAimingAtTarget;
    bool m_IsAimedAt;
    SObjectID m_GroupId;
    bool m_IsGroupHealthbar;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DisableEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnableEvent;
    float m_UnitHealth;
    float m_CurrentUnitDamage;
    float m_ArmourValue;
    float m_ArmourWeighting;
    float m_UnitHealthWeightingScalar;
    unsigned char m_ArmourLevel;
    CGameObject::EUpdateType m_UpdateType;
    CTurnTakerHelperStaticRaycastTracker m_TurnTakerRaycast;
    float m_CullingValidationRange;
    float m_CullFadeFactor;
    float m_CullFadeTime;   
};

#endif
