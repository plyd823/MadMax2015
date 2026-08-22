#include "GameSystem/Online/EventStructs_gen.h"

#ifdef BATCH_GAME_826130353_17_50

CHashString OpenWorldProgressionEvent::InstanceClassId() const {
    return CHashString(0x150b9ebc);
}

bool OpenWorldProgressionEvent::IsInstanceOf(CHashString classId) const {
    return SEventBaseData::IsInstanceOf(classId);
}

SEventBaseData* OpenWorldProgressionEvent::Clone() const {
    
}

const char* OpenWorldProgressionEvent::EventType() const {
    return "Progression";
}

const char* OpenWorldProgressionEvent::EventName() const {
    return "OpenWorldProgressionEvent";
}

float OpenWorldProgressionEvent::GetNumericalField(CHashString fieldToCheck) const {
    switch (fieldToCheck.m_Hash) {
        case 0x3f922b5d:
            return this->total_active_count;
        case 0x78f1e28e:
            return this->total_world_count;
        case 0xa14e22ab:
            return this->location_item_type;
        case 0x375b0af0:
            return this->activity_tag;
        default:
            return 0.0f;
    }
}

uint32_t OpenWorldProgressionEvent::GetIntegerField(CHashString fieldToCheck, bool& foundField) const {
    foundField = true;

    switch (fieldToCheck.m_Hash) {
        case 0x3f922b5d:
            return this->total_active_count;
        case 0x78f1e28e:
            return this->total_world_count;
        case 0xa14e22ab:
            return this->location_item_type;
        case 0x375b0af0:
            return this->activity_tag;
        default:
            foundField = false;
            return 0.0f;
    }
}

int32_t OpenWorldProgressionEvent::GetSignedIntegerField(CHashString fieldToCheck, bool& foundField) const {
    foundField = false;
    return 0;
}

OpenWorldProgressionEvent::~OpenWorldProgressionEvent() {

}

OpenWorldProgressionEvent& OpenWorldProgressionEvent::operator=(const OpenWorldProgressionEvent&) {

}

CHashString OpenWorldProgressionEvent::ClassId() {

}

#endif


#ifdef BATCH_GAME_826130353_18_50

CHashString Quest::InstanceClassId() const {
    return CHashString(0xb31d19ce);
}

bool Quest::IsInstanceOf(CHashString classId) const {
    return SEventBaseData::IsInstanceOf(classId);
}

SEventBaseData* Quest::Clone() const {

}

const char* Quest::EventType() const {
    return "Progression";
}

const char* Quest::EventName() const {
    return "Quest";
}

float Quest::GetNumericalField(CHashString fieldToCheck) const {
    switch (fieldToCheck.m_Hash) {
        case 0x35468946:
            return this->quest_id;
        case 0x6ee2f4c1:
            return this->quest_event_type;
        case 0x5418bc88:
            return this->quest_critical_path ? 1.0f : 0.0f;
        default:
            return 0.0f;
    }
}

uint32_t Quest::GetIntegerField(CHashString fieldToCheck, bool& foundField) const {
    foundField = true;

    switch (fieldToCheck.m_Hash) {
        case 0x35468946:
            return this->quest_id;
        case 0x6ee2f4c1:
            return this->quest_event_type;
        case 0x5418bc88:
            return this->quest_critical_path;
        case 0xc76776bb:
            return CHashString(this->quest_name.c_str()).get();
        default:
            foundField = false;
            return 0.0f;
    }
}

int32_t Quest::GetSignedIntegerField(CHashString fieldToCheck, bool& foundField) const {
    foundField = false;
    return 0;
}

#endif
