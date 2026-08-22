#ifndef PROJECT_GAME_MISSION_MANAGER_H
#define PROJECT_GAME_MISSION_MANAGER_H

namespace NMissionSystem {
    class CMission;
    class CRestartPointGlobal;
}

#include <cstdint>
#include <memory>
#include <vector>
#include "Base/Misc/Event.h"
#include "AvaCore/Math/Matrix.h"
#include "AvaCore/Math/Vector.h"
#include "Game/Mission/adf/mission_types.h"
#include "Base/Misc/AppSystem.h"
#include "Game/Mission/adf/restartpoint_types.h"
#include "Base/Types/Static_string.h"
#include "AvaCore/FileHandling/Parsing/RuntimeContainer.h"
#include "Base/Misc/AppSystem.h"
#include "ResourceCache/ResourceCache.h"

namespace NMissionSystem {
    class CMissionManager : public CAvaSingle<NMissionSystem::CMissionManager>, public Base::IAppSystem, public NEvent::CEventHandler {
        class CDisableSaveTriggersScope {
            private: 
            bool m_OldState;
            
            public: 
            CDisableSaveTriggersScope();
            ~CDisableSaveTriggersScope();
            void* __vecDelDtor(uint32_t);
        };

        enum EAutoSaveType : int32_t {
            E_NONE = 0xff,
            E_NORMAL = 0x0000,
        };

        enum EFastTravelState : int32_t {
            FAST_TRAVEL_INACTIVE = 0x0000,
            FAST_TRAVEL_WAIT_UNTIL_UPDATE = 0x0001,
            FAST_TRAVEL_WAIT_FOR_SIGNAL = 0x0002,
            FAST_TRAVEL_LOCKED = 0x0003,
        };

        private: 
        std::vector<std::pair<SMissionCollection *,NMissionSystem::CMission *>,std::allocator<std::pair<SMissionCollection *,NMissionSystem::CMission *> > > m_MissionCollections;
        std::vector<NMissionSystem::CMission *,std::allocator<NMissionSystem::CMission *> > m_Missions;
        SRestartPointCollection* m_RestartPointCollection;
        std::vector<SRestartPoint const *,std::allocator<SRestartPoint const *> > m_FastTravelPoints;
        std::vector<SRestartPoint const *,std::allocator<SRestartPoint const *> > m_FreeRoamPoints;
        NMissionSystem::CRestartPointGlobal* m_GlobalEventRestartPoints;
        CVector3f m_FreeRoamCheckPosition;
        CMatrix4f m_LastGroundContactTransform;
        CMatrix4f m_BookmarkPosition;
        const NMissionSystem::CMission* m_MissionsToEvaluate[64];
        int32_t m_MissionsToEvaluateCount;
        NMissionSystem::CMission* m_ActiveMission;
        uint64_t m_ActiveRestartPointId;
        uint64_t m_ExtraRestartPointId;
        uint64_t m_LatestUsedCheckPoints[4];
        uint32_t m_StartPointEvent;
        uint32_t m_LastStartPointEvent;
        uint32_t m_CompleteBookmarkEvent;
        const SRestartPoint* m_GlobalBookmarkRestartPoint;
        const SRestartPoint* m_FrontEndRestartPoint;
        NEvent::CReceiveEvent<void,void,void,void,void> m_LoadFrontEndEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_StartPointLoadedEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_CheckpointLoadedEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_AbortActiveMissionEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_FailActiveMissionEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_CompleteActiveObjectiveEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_CompleteActiveMissionEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_RestartMissionSystemEvent;
        NEvent::CReceiveEvent<char const *,void,void,void,void> m_DumpMissionInfoEvent;
        NEvent::CSendEvent<void,void,void,void,void> m_MissionAbortedEvent;
        NEvent::CSendEvent<void,void,void,void,void> m_MissionFailedEvent;
        NEvent::CSendEvent<void,void,void,void,void> m_GameRestarted;
        NEvent::CSendEvent<void,void,void,void,void> m_SaveCheckpointEvent;
        NEvent::CSendEvent<void,void,void,void,void> m_SaveEvent;
        NEvent::CSendEvent<void,void,void,void,void> m_GameOverEvent;
        bool m_OverrideStartPosition;
        bool m_MissionsLoaded;
        bool m_ActiveMissionFailed;
        bool m_ShowMissionInfo;
        bool m_ShowNoActiveRestartPoint;
        bool m_ShowSideMissionInfo;
        bool m_MissionStateChanged;
        bool m_MainMissionStateChanged;
        bool m_DoAutoSave;
        bool m_TriggerSaveCheckpoint;
        NMissionSystem::CMissionManager::EAutoSaveType m_TriggerAutoSave;
        NMissionSystem::CMissionManager::EFastTravelState m_FastTravelState;
        NEvent::CSendEvent<void,void,void,void,void> m_FastTravelRequested;
        NEvent::CReceiveEvent<void,void,void,void,void> m_FastTravelWaitRequested;
        NEvent::CReceiveEvent<void,void,void,void,void> m_FastTravelExecute;
        NEvent::CReceiveEvent<void,void,void,void,void> m_FastTravelLock;
        NEvent::CReceiveEvent<void,void,void,void,void> m_FastTravelUnlock;
        NEvent::CReceiveEvent<void,void,void,void,void> m_FastTravelRuntimeBlock;
        NEvent::CReceiveEvent<void,void,void,void,void> m_FastTravelRuntimeUnblock;
        uint32_t m_FastTravelMessageStringId;
        int32_t m_FastTravelPointIndex;
        float m_FlashTime;
        unsigned char m_BlockEventFlags;
        bool m_FastTravelRuntimeBlocked;
        bool m_FastTravelSpeedBlocked;
        bool m_FastTravelPlayerDeadBlocked;

        private: 
        static const int32_t MAX_MISSIONS_TO_EVALUATE;
        static const int32_t MAX_LATEST_CHECKPOINTS;
        static bool m_TriggersEnabled;
        
        public: 
        virtual static_string GetKlassName() const;
        virtual bool InitializeSystem(const CRuntimeContainer&, const Base::SAppSystemInitContext&);
        virtual bool PostInitializeSystem(const CRuntimeContainer&);
        CMissionManager(const NMissionSystem::CMissionManager&);
        CMissionManager();
        void UpdateStats(unsigned char);
        void RestartSystem();
        void Update(float);
        void UpdateRender(float);
        NMissionSystem::CMission* GetMission(const uint32_t) const;
        const char* GetActiveMissionName() const;
        uint32_t GetActiveMissionNameKey() const;
        void Save(CSaveContainer&) const;
        void Load(const CSaveContainer&);
        bool IsFreeRoaming() const;
        void TriggerCheckpointSave();
        void TriggerAutoSave(NMissionSystem::CMissionManager::EAutoSaveType);
        void EnableTriggers(bool);
        NMissionSystem::CMission* GetActiveMission() const;
        void SetActiveMission(NMissionSystem::CMission*);
        void AddMissionToEvaluate(const NMissionSystem::CMission*);
        void SetMissionCompleted(const NMissionSystem::CMission*);
        bool IsActiveMissionFailed() const;
        void RequestFastTravelToPoint(int32_t);
        bool IsFastTravelAllowed() const;
        uint32_t GetFastTravelMessage() const;
        const SRestartPointCollection* GetRestartPointCollection() const;
        const SRestartPoint* GetRestartPointByNameHash(uint32_t) const;
        const SRestartPoint* GetRestartPointById(uint64_t) const;
        bool RegisterActiveRestartPoint(uint64_t, bool);
        void UnRegisterActiveRestartPoint(uint64_t);
        uint64_t GetActiveRestartPointId() const;
        bool HasValidActiveRestartPoint() const;
        void SetRestartPointEnable(uint64_t, bool);
        void SetRestartPointEnableByNameHash(uint32_t);
        int32_t GetClosestFastTravelPointIndex() const;
        const std::vector<SRestartPoint const *,std::allocator<SRestartPoint const *> >& GetFastTravelPoints() const;
        void RegisterPlayerPosition(const CMatrix4f&, const CVector3f&, bool);
        bool GetPlayerStartTransform(CMatrix4f&, uint64_t) const;
        const SRestartPoint* GetGlobalBookmarkRestartPoint() const;
        void SetStartPointEvent(uint32_t);
        void OnMissionStateChanged(NMissionSystem::CMission*);
        float CompletionRatio(bool);
        void GetMissionTypeSummary(const unsigned char, uint64_t&, uint64_t&);
        float TimeSpentOnMissions(bool);
        bool CanAutosave() const;
        int32_t CountActiveSideMissions() const;
        bool JumpToMainMenuRestartPoint();
        bool IsAbandonableMission() const;
        void SetBookmarkData(const CMatrix4f&, uint32_t);
        void ApplyBookmarkData();
        void BlockStartPointLoadedEvent();
        void BlockCheckpointLoadedEvent();
        void OnPlayerDeath();

        private: 
        bool ConsumedBlockEventFlag(const unsigned char);
        void SetMissionSoundInformation();
        virtual void ReleaseSystem();
        virtual void HandleEvent(const NEvent::CEventImpl*, const NEvent::CEventData&);
        void ResetLatestUsedCheckpoints();
        void SetClosestFreeRoamPoint();
        void SetLatestUsedCheckpoint(uint64_t, bool);
        void RemoveLatestUsedCheckpoint(uint64_t);
        const SRestartPoint* GetClosestFreeRoamPoint() const;
        void OnStartPointLoadedEvent();
        bool OnCheckpointLoadedEvent();
        void SetActiveObjective(const uint32_t, const uint32_t);
        void AbortActiveMission();
        void FailActiveMission();
        void CompleteActiveMission();
        void CompleteActiveObjective();
        void SortMissions();
        bool EvaluateMissions();
        void TeleportToFastTravelPointIndex(int32_t);

        public: 
        virtual ~CMissionManager();
        NMissionSystem::CMissionManager& operator=(NMissionSystem::CMissionManager&);
        
        public: 
        static static_string GetClassNameStatic();
        static void LoadAdfs(SAdfContext*);
        static void* CreateMissions(SResourceCache*, void*, SResourceAllocator*, SResourceAllocator*, uint32_t, const void*, uint64_t, void*, const char*);
        static void DestroyMissions(SResourceCache*, void*, SResourceAllocator*, SResourceAllocator*, uint32_t, void*);
        static void* CreateRestartPoints(SResourceCache*, void*, SResourceAllocator*, SResourceAllocator*, uint32_t, const void*, uint64_t, void*, const char*);
        static void DestroyRestartPoints(SResourceCache*, void*, SResourceAllocator*, SResourceAllocator*, uint32_t, void*);
    };

    class CRestartPointGlobal : public NEvent::CEventHandler {
        private: 
        NEvent::CReceiveEvent<void,void,void,void,void> m_GlobalEnableEvent;
        NEvent::CReceiveEvent<void,void,void,void,void> m_GlobalDisableEvent;
        SRestartPoint* m_RestarPointData;
        
        public: 
        CRestartPointGlobal(const NMissionSystem::CRestartPointGlobal&);
        CRestartPointGlobal(SRestartPoint*);

        private: 
        CRestartPointGlobal();
        virtual void HandleEvent(const NEvent::CEventImpl*, const NEvent::CEventData&);

        public: 
        virtual ~CRestartPointGlobal();
        NMissionSystem::CRestartPointGlobal& operator=(NMissionSystem::CRestartPointGlobal&);
        void __local_vftable_ctor_closure();
        virtual void* __vecDelDtor(uint32_t);
    };
};

#endif
