#ifndef PROJECT_GAME_DAMAGEABLE_H
#define PROJECT_GAME_DAMAGEABLE_H

struct SGameObjectSetPropertiesContext;
class CDamageInflictor;

#include "Base/Misc/Event.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/Physics/PhysicsGameObject.h"
#include "AvaCore/Types/HashString.h"
#include "AvaCore/Math/Matrix.h"
#include "project/Game/GameObject/Healthbar.h"

class CDamageable : public CPhysicsGameObject, public NEvent::CEventHandler {
    friend class CPlayer;

    struct SExtraHitEvents {
        public:
        NEvent::CSendEvent<void,void,void,void,void> m_OnHitByPlayer;
        NEvent::CSendEvent<void,void,void,void,void> m_OnHitByEnemy;
    };

    struct SPerDamageTypeEvents {
        public:
        CHashString m_Type;
        NEvent::CSendEvent<void,void,void,void,void> m_OnHit;
        NEvent::CSendEvent<float,void,void,void,void> m_OnHitDamaged;
        NEvent::CSendEvent<void,void,void,void,void> m_OnHitNotDamaged;
        NEvent::CSendEvent<CMatrix4f,void,void,void,void> m_OnDestroy;
        NEvent::CReceiveEvent<void,void,void,void,void> m_ForceDestroy;
    };

    protected:
    bool m_Destroyed;
    bool m_Invulnerable;
    bool m_InvulnerableE3;
    NEvent::CReceiveEvent<void,void,void,void,void> m_RestoreHealth;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ForceDestroy;
    NEvent::CReceiveEvent<void,void,void,void,void> m_MakeInvulnerable;
    NEvent::CReceiveEvent<void,void,void,void,void> m_MakeVulnerable;
    NEvent::CReceiveEvent<void,void,void,void,void> m_MakeInvulnerableE3;
    NEvent::CSendEvent<void,void,void,void,void> m_OnHit;
    NEvent::CSendEvent<float,void,void,void,void> m_OnHitDamaged;
    NEvent::CSendEvent<void,void,void,void,void> m_OnHitNotDamaged;
    NEvent::CSendEvent<CMatrix4f,void,void,void,void> m_OnDestroy;
    NEvent::CSendEvent<void,void,void,void,void> m_OnRemoved;
    NEvent::CSendEvent<void,void,void,void,void> m_OnHealthIncreased;
    NEvent::CSendEvent<void,void,void,void,void> m_OnHealthDecreased;
    CDamageable::SExtraHitEvents* m_ExtraHitEvents;
    std::vector<CDamageable::SPerDamageTypeEvents *,std::allocator<CDamageable::SPerDamageTypeEvents *> >* m_PerDamageTypeEvents;
    std::vector<std::pair<float,NEvent::CSendEvent<void,void,void,void,void> >,std::allocator<std::pair<float,NEvent::CSendEvent<void,void,void,void,void> > > > m_OnHealthDecreasedPastThreshold;
    float m_MaxHealth;
    float m_CurHealth;
    float m_LastHealth;
    float m_Armor[8];
    CHashString m_OnlyAcceptDamageFromType;
    uint32_t m_DamageFromPlayerTimeStamp;
    CHealthbar* m_HealthbarPtr;

    public:
    static const float s_MagicInvunerableHealth;

    public: 
    virtual const CRttiTypeId& GetTypeId() const;
    virtual bool IsType(const CRttiTypeId&) const;
    CDamageable(const CDamageable&);
    CDamageable();
    virtual ~CDamageable();
    virtual void SetProperties(const CRuntimeContainer&, SGameObjectSetPropertiesContext*);
    virtual void HandleEvent(const NEvent::CEventImpl*, const NEvent::CEventData&);
    virtual float InflictDamage(const CDamageInflictor&);
    virtual float CalculateDamage(const CDamageInflictor&);
    float ApplyArmor(const CDamageInflictor&);
    void SetArmor(CHashString, float);
    void SetMaxHealth(float);
    void SetHealth(float, CHashString);
    void RestoreHealth();
    bool IsInvulnerable() const;
    void SetInvulnerable(bool);
    void SetSendOnHealthZero(const NEvent::CSendEvent<CMatrix4f,void,void,void,void>&);
    void SetSendOnDesctructor(const NEvent::CSendEvent<void,void,void,void,void>&);
    void SetSendOnDamage(const NEvent::CSendEvent<float,void,void,void,void>&);
    void SetSendOnHitNoDamage(const NEvent::CSendEvent<void,void,void,void,void>&);
    void SetSendOnHit(const NEvent::CSendEvent<void,void,void,void,void>&);
    void SetKillOn(const NEvent::CReceiveEvent<void,void,void,void,void>&);
    void SetSendOnHealthDecreased(const std::vector<std::pair<float,NEvent::CSendEvent<void,void,void,void,void> >,std::allocator<std::pair<float,NEvent::CSendEvent<void,void,void,void,void> > > >&);
    void ReplaceMakeInvulnerableEvent(NEvent::CReceiveEvent<void,void,void,void,void>&);
    void ReplaceMakeVulnerableEvent(NEvent::CReceiveEvent<void,void,void,void,void>&);
    float GetMaxHealth() const;
    float GetHealth() const;
    float GetLastHealth() const;
    float GetUnitHealth() const;
    bool IsDestroyed() const;
    bool IsDestroyedOrExploding() const;
    bool IsDestroyedRecursive() const;
    virtual bool IsTargetable() const;
    float GetArmor(CHashString) const;
    bool IsInvulnerableE3();
    void SetInvulnerableE3(bool);
    void SetHitByPlayer();
    bool WasHitByPlayer(const float&) const;
    void SetHealthbar(CHealthbar*);

    protected: 
    virtual void OnDestroyed(CHashString);
    virtual void SendOnDestroyEvent(CHashString);
    void CheckHealthDecreasedEvents();
    CDamageable::SPerDamageTypeEvents* GetPerDamageTypeEvents(CHashString);

    public: 
    CDamageable& operator=(CDamageable&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

#endif
