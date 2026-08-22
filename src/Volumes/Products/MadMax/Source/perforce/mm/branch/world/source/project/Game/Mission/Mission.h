#ifndef PROJECT_GAME_MISSION_H
#define PROJECT_GAME_MISSION_H

struct SMissionObjective;
struct SMissionData;
class CSaveContainer;
namespace NMissionSystem {
    enum EMissionEventType : int;
}

#include "Base/Misc/Event.h"
#include "Game/Mission/adf/mission_types.h"
#include "GameSystem/Online/EventStructs_gen.h"
#include "GameSystem/SaveSystem/SaveContainer.h"
#include "Game/Mission/MissionManager.h"

namespace NMissionSystem {
    enum EMissionEventType : int32_t {
        EVENT_TYPE_UNLOCK = 0x0000,
        EVENT_TYPE_ACTIVATE = 0x0001,
        EVENT_TYPE_COMPLETE = 0x0002,
        EVENT_TYPE_UNLOCKED = 0x0003,
        EVENT_TYPE_ACTIVATED = 0x0004,
        EVENT_TYPE_COMPLETED = 0x0005,
        EVENT_TYPE_ABORTED = 0x0006,
        EVENT_TYPE_FAILED = 0x0007,
        EVENT_TYPE_LOCKED = 0x0008,
        EVENT_TYPE_DEBUG_COMPLETE = 0x0009,
        EVENT_TYPE_LOCATION_LOAD = 0x0000,
        EVENT_TYPE_LOCATION_UNLOAD = 0x0001,
        EVENT_TYPE_LOCATION_ONLOADED = 0x0002,
        EVENT_TYPE_LOCATION_ONUNLOADED = 0x0003,
    };

    class CMission : public NEvent::CEventHandler {
        private: 
        SMissionData* m_Data;
        float m_TimeSpentOnMission;
        NEvent::CReceiveEvent<void,void,void,void,void> m_ReceiveUnlockEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_ReceiveActivateEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_ReceiveCompleteEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_ReceiveParentEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_ResourceLoadedEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_ResourceUnloadedEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_MissionObjectiveEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_ReceiveDebugCompleteEvent;
        
        public: 
        CMission(const NMissionSystem::CMission&);
        CMission(SMissionData*);

        private: 
        CMission();
        const NMissionSystem::CMission& operator=(const NMissionSystem::CMission&);

        public: 
        virtual ~CMission();
        void UnlockMsg();
        uint32_t GetID() const;
        const char* GetIDString() const;
        void SetLocked(bool);
        void SetActivated(bool);
        void SetCompleted(bool);
        bool Unlock();
        bool Activate();
        void SendQuestData(Quest::QUEST_TYPE, SMissionObjective*, bool);
        void SendQuestData(Quest::QUEST_TYPE, SMissionData*);
        bool Complete();
        void DebugComplete();
        bool Abort();
        void Fail();
        unsigned char GetStateFlags() const;
        void SetStateFlags(const unsigned char);
        bool IsLocked() const;
        bool IsActivated() const;
        bool IsCompleted() const;
        bool IsAchieved() const;
        bool IsResourceLoaded() const;
        bool IsParentEventReceived() const;
        bool IsMainMission() const;
        bool IsMissionOfType(const unsigned char) const;
        SMissionObjective* GetMissionObjective(const uint32_t) const;
        void ActivateObjective(const uint32_t);
        const char* GetActiveObjectiveIdString() const;
        uint32_t GetActiveObjectiveId() const;
        uint32_t GetMissionNameKey() const;
        void CompleteActiveObjective();
        void ForceSendObjectiveEvents() const;
        bool RequiresActiveMissionToComplete();
        void Save(CSaveContainer&, int32_t&) const;
        void Load(const CSaveContainer&, int32_t&);
        bool LoadResource();
        void UnloadResource();
        const NEvent::CReceiveEvent<void,void,void,void,void>& GetResourceLoadedReceiveEvent() const;
        const SMissionData& GetMissionData() const;
        bool CompleteObjective(uint32_t);
        void Restart();
        void UpdateTimeSpentOnMission(float);
        void RestTimeSpentOnMission();
        float GetTimeSpentOnMission() const;

        private: 
        void Reset();
        void CreateAndSendEvent(NMissionSystem::EMissionEventType) const;
        virtual void HandleEvent(const NEvent::CEventImpl*, const NEvent::CEventData&);
        bool HandleObjectiveEvent(const NEvent::CEventImpl*, const NEvent::CEventData&);
        void CreateObjectives();
        void RegisterEvents();
        bool DeactivateObjective(uint32_t);
        void SendProgressionCompleteData();

        public: 
        void __local_vftable_ctor_closure();
        virtual void* __vecDelDtor(uint32_t);
    };
};

#endif
