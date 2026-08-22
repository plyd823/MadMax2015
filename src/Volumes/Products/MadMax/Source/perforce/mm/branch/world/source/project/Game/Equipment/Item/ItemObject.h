#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifndef PROJECT_GAME_ITEM_H
#define PROJECT_GAME_ITEM_H

#include "Base/Misc/Event.h"
#include "GameSystem/GameObject/Physics/PhysicsGameObject.h"
#include "AvaCore/Math/Matrix.h"
#include "AvaCore/Math/Vector.h"
#include "AvaCore/Math/Quaternion.h"
#include "AvaCore/Types/HashString.h"
#include "Game/Character/Character.h"
#include "Game/Equipment/Item/ItemAttachedEffectComponent.h"
#include "GameSystem/EffectSystem/CollisionEffectsExtension.h"

class CItemObject : public CPhysicsGameObject, public NEvent::CEventHandler {
    protected: 
    CMatrix4f m_LocalTransform;
    public: 
    CHashString m_AutoWieldBone;
    protected: 
    CCharacter* m_Owner;
    CHashString m_ItemPickupInteractionType;
    CHashString m_ItemCarryInteractionType;
    CHashString m_Category;
    CHashString m_CurrentAttachBone;
    CHashString m_UnWieldBone;
    CHashString m_AnimationModifier;
    SObjectID m_AnimatedModelID;
    CGameObject* m_AnimatedModel;
    bool m_UpdateWorldMatrix;
    CMatrix4f m_WorldMatrixT1;
    CQuaternion m_Q0;
    CQuaternion m_Q1;
    CVector3f m_T0;
    int32_t m_DropAtStart;
    uint32_t m_PickupTime;
    uint32_t m_ItemTypeNameHash;
    bool m_CanBeDropped;
    bool m_PendingOnNewItemObjectOwner;
    CHashString m_AdditionalType;
    CItemAttachedEffectComponent m_EffectComponent;
    CCollisionEffectsExtension* m_CollisionEffects;
    NEvent::CSendEvent<void,void,void,void,void> m_OnPickedUpEvent;
    NEvent::CSendEvent<void,void,void,void,void> m_OnDroppedEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnableUpdateWorldMatrix;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DisableUpdateWorldMatrix;
    bool m_UsePostApplyRenderTransform : 1; /* BitPos=0 */
    bool m_DynamicLODOverridden : 1; /* BitPos=1 */
    unsigned char m_SavedMinLod;
    unsigned char m_SavedOffsetLod;
    float m_SavedScaleLod;
    CMatrix4f m_PostApplyRenderTransform;
    int64_t m_DroppedTime;
};

#endif
