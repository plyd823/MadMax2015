#ifndef PROJECT_GAME_INTERACTION_USER_PROXY_H
#define PROJECT_GAME_INTERACTION_USER_PROXY_H

class CInteractionUserProxy;

#include <cstdint>
#include <memory>
#include <vector>
#include "ALib/Array.h"
#include "AvaCore/Math/Matrix.h"
#include "AvaCore/Math/Vector.h"
#include "Game/Interaction/InteractionGraphData/InteractionGraphUserEdge.h"
#include "Game/Interaction/InteractionGraphData/InteractionGraphExit.h"
#include "Game/Interaction/InteractionGraphEntry.h"
#include "Game/Interaction/InteractionGraphData/InteractionGraphTransition.h"
#include "Game/Interaction/InteractionGraphData/InteractionGraphNode.h"
#include "Game/Interaction/InteractionGraph.h"
#include "Game/Interaction/InteractionTrigger.h"
#include "Game/Interaction/InteractionContext.h"
#include "Game/Interaction/Interaction.h"
#include "AvaCore/Types/HashString.h"
#include "Game/Character/Character.h"

class CEntryValidationInScope {
    private: 
    CInteractionUserProxy* m_User;
    
    public: 
    CEntryValidationInScope(CInteractionUserProxy*);
    ~CEntryValidationInScope();
    void* __vecDelDtor(uint32_t);
};

class CInteractionMessageData {
    public: 
    TArray<CInteraction *> m_PotentialInteractions;
    CInteractionUserProxy* m_User;

    public: 
    static const uint32_t INTERACTIONS_CAPACITY;
    
    public: 
    CInteractionMessageData(const CInteractionMessageData&);
    CInteractionMessageData(CInteractionUserProxy*);
    ~CInteractionMessageData();
    CInteractionMessageData& operator=(const CInteractionMessageData&);
    void* __vecDelDtor(uint32_t);
};

class CInteractionUserProxy {
    public:
    struct SInteractionGraphMovementToActMapping {
        public:
        TArray<int> m_MovementIdentifiers;
        TArray<int> m_ActEvents;

        public: 
        SInteractionGraphMovementToActMapping(const CInteractionUserProxy::SInteractionGraphMovementToActMapping&);
        SInteractionGraphMovementToActMapping();
        ~SInteractionGraphMovementToActMapping();
        CInteractionUserProxy::SInteractionGraphMovementToActMapping& operator=(const CInteractionUserProxy::SInteractionGraphMovementToActMapping&);
        void* __vecDelDtor(uint32_t);
    };

    enum EIGraphUserState : int32_t {
        IGUS_INACTIVE = 0x0000,
        IGUS_ACTIVE_NODE = 0x0001,
        IGUS_ACTIVE_ENTRY = 0x0002,
        IGUS_ACTIVE_EXIT = 0x0003,
        IGUS_ACTIVE_TRANSITION = 0x0004,
    };

    public: 
    CCharacter* m_Character;
    CInteractionGraph* m_Graph;
    CInteractionGraphNode* m_CurrentNode;
    CInteractionGraphNode* m_TransitionFromNode;
    CInteractionGraphTransition* m_CurrentTransition;
    CInteractionGraphEntry* m_CurrentEntry;
    CInteractionGraphExit* m_CurrentExit;
    CInteractionGraphUserEdge* m_CurrentUserEdge;
    CInteractionGraphUserEdge* m_IntermediateUserEdge;
    CInteractionGraphUserEdge* m_ActiveUserEdge;
    CMatrix4f m_LocalMatrix;
    CMatrix4f m_MoveStartLS;
    CMatrix4f m_MoveEndLS;
    CVector3f m_ScaledAnimationTranslation;
    CMatrix4f m_ScaledAnimationRotationOffset;
    CMatrix4f m_ScaledAnimationRotationCurrentOffset;
    float m_LineNodeFraction;
    float m_MoveFraction;
    CVector2f m_EdgeRelativeInput;
    bool m_MotionStateEnabled;
    bool m_PhysicsUpdateEnable;
    bool m_UseInitFrame;
    TArray<CInteractionGraphEntry *> m_PotentialEntries;
    CHashString m_NamedFailEntry;

    private: 
    CInteractionUserProxy::SInteractionGraphMovementToActMapping m_MovementIdentifierToActMapping;
    std::vector<CInteractionTrigger *,std::allocator<CInteractionTrigger *> > m_InteractionTriggers;
    TArray<CInteractionGraphEntry *> m_ValidEntries;
    TArray<CInteractionGraphEntry *> m_PreviousValidEntries;
    CInteractionUserProxy::EIGraphUserState m_GraphUserState;
    bool m_IsValidatingEntry;
    bool m_ReEnterStateFlag;

    public: 
    static const uint32_t POTENTIAL_ENTRIES_CAPACITY;

    private: 
    static const uint32_t VALID_ENTRIES_CAPACITY;

    public: CInteractionUserProxy(const CInteractionUserProxy&);
    CInteractionUserProxy();
    virtual ~CInteractionUserProxy();
    void Update(float);
    void InitTransform();
    void GetWorldTransform(CMatrix4f&);
    void EnterGraph(CInteractionGraphEntry*);
    void ExitGraph(CInteractionGraph*);
    void EnterNode(CInteractionGraphNode*);
    void EnterTransition(CInteractionGraphTransition*, const CHashString&);
    void EnterExit(CInteractionGraphExit*);
    void UpdateTransitionLerp();
    void UpdateTransitionScaledMotion(float);
    void UpdateTransitionAndRotationScaledMotion(float);
    void UpdateOffsetMotion(float);
    bool SendEventsMappedToMovementIdentifier(int32_t);
    bool GetEventIdFromMovementIdentifier(int32_t, int32_t&) const;
    void AddMovementIdentifierToActMapping(int32_t, int32_t);
    void ClearMovementIdentifierToActMapping();
    bool IsAttachedToGraph() const;
    CInteractionContext* GetContext() const;
    CInteractionGraph* GetGraph() const;
    uint32_t GetCurrentNodeIndex() const;
    void SetGraphUserState(CInteractionUserProxy::EIGraphUserState);
    CInteractionUserProxy::EIGraphUserState GetGraphUserState() const;
    const TArray<CInteractionGraphEntry *>& GetAvailableEntries() const;
    const TArray<CInteractionGraphEntry *>& GetValidEntries();
    bool ValidationAddEntry(CInteractionGraphEntry*);
    void AddValidEntry(CInteractionGraphEntry*);
    void ClearValidEntries();
    const TArray<CInteractionGraphEntry *>& GetPreviousValidEntries() const;
    void ClearPreviousValidEntries();
    bool InEntryValidation() const;
    void SetNamedFailEntry(const char*);
    uint32_t GetAndClearNamedFailEntry();
    void TryReEnter(const CHashString&);
    void ActivateReEnter();
    void DeActivateReEnter();

    private: 
    void OnLeaveEntryTransitionOrExit();
    void SetEntryValidationBegin();
    void SetEntryValidationEnd();
    void RemoveValidEntry(CInteractionGraphEntry*);
    void ClearValidEntriesInternal();

    public: 
    CInteractionUserProxy& operator=(const CInteractionUserProxy&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
};

namespace NEvent {
    template <typename T>
    struct SEventArgumentTraits {
        public: 
        static uint32_t Size(T);
        static void Copy(void*, T);
        static const void* Immediate(T&);
        static T From(const void*);
    };
};

#endif
