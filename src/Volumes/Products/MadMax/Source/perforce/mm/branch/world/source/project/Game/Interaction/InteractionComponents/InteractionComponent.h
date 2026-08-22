#ifndef PROJECT_GAME_INTERACTION_COMPONENT_H
#define PROJECT_GAME_INTERACTION_COMPONENT_H

class CInteractionUserProxy;

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "AvaCore/Types/Rtti.h"
#include "project/Game/Interaction/InteractionContext.h"
#include "AvaCore/FileHandling/Parsing/RuntimeContainer.h"
#include "project/Game/Interaction/InteractionUserProxy.h"

class CInteractionComponent : public CRtti {
    public:
    enum EInteractionComponentUserFilter : int32_t {
        ECUF_BOTH = 0x0000,
        ECUF_PLAYER_ONLY = 0x0001,
        ECUF_NPC_ONLY = 0x0002,
    };

    public: 
    CInteractionComponent::EInteractionComponentUserFilter m_UserFilter;
    
    public: 
    virtual const CRttiTypeId& GetTypeId() const;
    virtual bool IsType(const CRttiTypeId&) const;
    CInteractionComponent(const CInteractionComponent&);
    CInteractionComponent();
    virtual ~CInteractionComponent();
    virtual void SetProperties(CInteractionContext*, const CRuntimeContainer&);
    virtual void Activate(CInteractionUserProxy*);
    virtual void Deactivate(CInteractionUserProxy*);
    virtual void Execute(CInteractionUserProxy*);
    virtual bool AllowUser(CInteractionUserProxy*);
    CInteractionComponent& operator=(const CInteractionComponent&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    
    public: 
    static const CRttiTypeId& TYPE_ID();
};

#endif
