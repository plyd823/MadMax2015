#include "Mission.h"

#ifdef BATCH_GAME_826130353_18_50

void NMissionSystem::CMission::UnlockMsg() {
    SEventID eventId(this->m_Data->m_Objectives.m_Data->m_EventHash[0], 0);

    NEvent::CEventData eventData(0xffffffffff, nullptr, nullptr, nullptr, nullptr, nullptr);
    
    CAvaSingle<CEventSystem>::Instance->SendEvent(&eventId, 1, eventData);
}

void NMissionSystem::CMission::SetCompleted(bool completed) {
    this->m_Data->m_Completed = completed;
}

void NMissionSystem::CMission::SetActivated(bool activated) {
    this->m_Data->m_Activated = activated;
}

NMissionSystem::CMission::~CMission() {

}

const char* NMissionSystem::CMission::GetActiveObjectiveIdString() const {
    for(int i = 0; i < this->m_Data->m_Objectives.m_Count; i++) {
        if(this->m_Data->m_Objectives.m_Data[i].m_Activated &&
        !this->m_Data->m_Objectives.m_Data[i].m_Completed) {
            return this->m_Data->m_Objectives.m_Data[i].m_IDString;
        }
    }

    return nullptr;
}

uint32_t NMissionSystem::CMission::GetActiveObjectiveId() const {

}

bool NMissionSystem::CMission::LoadResource() {

}

void NMissionSystem::CMission::UnloadResource() {

}

void NMissionSystem::CMission::CreateAndSendEvent(NMissionSystem::EMissionEventType) const {

}

bool NMissionSystem::CMission::Unlock() {

}

void NMissionSystem::CMission::Restart() {

}

void NMissionSystem::CMission::Reset() {

}

void NMissionSystem::CMission::DebugComplete() {

}

bool NMissionSystem::CMission::IsResourceLoaded() const {
    return this->m_Data->m_ResourceStatusFlags & 2;
}

void NMissionSystem::CMission::ForceSendObjectiveEvents() const {

}

SMissionObjective* NMissionSystem::CMission::GetMissionObjective(unsigned int) const {

}

void NMissionSystem::CMission::SetLocked(bool locked) {
    this->m_Data->m_Locked = locked;
}

void NMissionSystem::CMission::CompleteActiveObjective() {

}

unsigned char NMissionSystem::CMission::GetStateFlags() const {

}

void NMissionSystem::CMission::SetStateFlags(unsigned char) {

}

void NMissionSystem::CMission::Save(CSaveContainer&, int&) const {

}

void NMissionSystem::CMission::SendQuestData(Quest::QUEST_TYPE, SMissionData*) {

}

bool NMissionSystem::CMission::Activate() {

}

void NMissionSystem::CMission::Load(CSaveContainer const&, int&) {

}

bool NMissionSystem::CMission::Abort() {

}

void NMissionSystem::CMission::Fail() {

}

void NMissionSystem::CMission::SendQuestData(Quest::QUEST_TYPE, SMissionObjective*, bool) {

}

bool NMissionSystem::CMission::DeactivateObjective(unsigned int) {

}

void NMissionSystem::CMission::ActivateObjective(unsigned int) {

}

bool NMissionSystem::CMission::IsAchieved() const {

}

void NMissionSystem::CMission::SendProgressionCompleteData() {
    CAvaSingle<NMissionSystem::CMissionManager>::Instance->UpdateStats(this->m_Data->m_MissionType);
}

bool NMissionSystem::CMission::Complete() {

}

bool NMissionSystem::CMission::CompleteObjective(unsigned int) {

}

bool NMissionSystem::CMission::HandleObjectiveEvent(NEvent::CEventImpl const*, NEvent::CEventData const&) {

}

void NMissionSystem::CMission::HandleEvent(NEvent::CEventImpl const*, NEvent::CEventData const&) {

}

void NMissionSystem::CMission::CreateObjectives() {

}

void NMissionSystem::CMission::RegisterEvents() {

}

NMissionSystem::CMission::CMission(SMissionData*) {

}

#endif
