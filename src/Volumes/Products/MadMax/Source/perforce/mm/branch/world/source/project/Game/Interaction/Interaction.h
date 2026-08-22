#ifndef PROJECT_GAME_INTERACTION_H
#define PROJECT_GAME_INTERACTION_H

class CInteractionUserProxy;
class CInteractionMessageData;

#include "Base/Misc/Event.h"
#include "Game/Interaction/InteractionComponents/InteractionComponent.h"
#include "Game/Interaction/InteractionCondition.h"

class CInteraction : public NEvent::CEventHandler {
    struct SInteractionActivator {
        public: 
        SObjectID m_Id;
        CInteractionUserProxy* m_User;
        
        public: 
        bool operator!=(const SInteractionActivator&);
        SInteractionActivator();
    };

    private: 
    uint64_t m_UserId;
    uint64_t m_InteractionId;
    CHashString m_NameHash;
    uint32_t m_UserAlias;
    NEvent::CReceiveEvent<void,void,void,void,void> m_AliasActivationEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ObjectIdActivationEvent;
    NEvent::CReceiveEvent<CInteractionMessageData *,void,void,void,void> m_InteractionActivationEvent;
    CInteractionComponent* m_Components[16];
    CInteractionCondition* m_Conditions[8];
    CInteraction::SInteractionActivator m_CurrentActivators[64];

    private: 
    static const uint32_t INTERACTION_COMPONENT_CAPACITY;
    static const uint32_t INTERACTION_CONDITION_CAPACITY;
    static const uint32_t INTERACTION_ACTIVATORS_CAPACITY;
    
    public: 
    CInteraction(const CInteraction&);
    CInteraction();
    virtual ~CInteraction();
    void SetProperties(CInteractionContext*, const CRuntimeContainer&);
    virtual void HandleEvent(const NEvent::CEventImpl*, const NEvent::CEventData&);
    bool DoInteraction(CInteractionUserProxy*);
    void ActivateComponents(CInteractionUserProxy*, uint64_t);
    bool EvaluateConditions(CInteractionUserProxy*, uint64_t);
    void ExecuteComponents(CInteractionUserProxy*, uint64_t);
    void DeactivateComponents(CInteractionUserProxy*, uint64_t);
    bool IsActive(CInteractionUserProxy*, uint64_t);
    uint64_t GetId() const;
    uint32_t GetNameHash() const;

    private: 
    void AddActivator(CInteractionUserProxy*, uint64_t);
    void RemoveActivator(CInteraction::SInteractionActivator*);
    bool IsActivatedForUser(CInteractionUserProxy*);
    CInteraction::SInteractionActivator* GetActivator(CInteractionUserProxy*, uint64_t);
    CInteraction::SInteractionActivator* GetFirstActivator(CInteractionUserProxy*);

    public: 
    CInteraction& operator=(CInteraction&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

#endif
