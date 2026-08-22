#ifndef COMPONENT_EVENT_STRUCTS_GEN_H
#define COMPONENT_EVENT_STRUCTS_GEN_H

#include <cstdint>
#include <memory>
#include <string>

#include "GameSystem/Online/EventStructs.h"
#include "AvaCore/Types/HashString.h"

class GlobalDifficultySetting : public SEventBaseData {
    public:
    int32_t difficulty;

    public: 
    virtual CHashString InstanceClassId() const;
    virtual bool IsInstanceOf(CHashString) const;
    virtual SEventBaseData* Clone() const;
    virtual const char* EventType() const;
    virtual const char* EventName() const;
    virtual float GetNumericalField(CHashString) const;
    virtual uint32_t GetIntegerField(CHashString, bool&) const;
    virtual int32_t GetSignedIntegerField(CHashString, bool&) const;
    GlobalDifficultySetting(const GlobalDifficultySetting&);
    GlobalDifficultySetting();
    virtual ~GlobalDifficultySetting();
    GlobalDifficultySetting& operator=(const GlobalDifficultySetting&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    static CHashString ClassId();
};

class SProgressionBaseData : public SEventBaseData {
    public: 
    std::basic_string<char,std::char_traits<char>,std::allocator<char> > m_MapName;
    std::basic_string<char,std::char_traits<char>,std::allocator<char> > m_AreaName;
    float x;
    float y;
    float z;
    uint32_t level;
    uint32_t difficulty;
    uint64_t time_stamp;
    
    public: 
    virtual CHashString InstanceClassId() const;
    virtual bool IsInstanceOf(CHashString) const;
    virtual const char* EventType() const;
    virtual const char* EventName() const;
    virtual float GetNumericalField(CHashString) const;
    virtual uint32_t GetIntegerField(CHashString, bool&) const;
    virtual int32_t GetSignedIntegerField(CHashString, bool&) const;
    SProgressionBaseData(const SProgressionBaseData&);
    SProgressionBaseData();
    virtual ~SProgressionBaseData();
    SProgressionBaseData& operator=(const SProgressionBaseData&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    
    public: 
    static CHashString ClassId();
};

class Quest : public SProgressionBaseData {
    public:
    enum QUEST_TYPE : int32_t {
        E_QUEST_STARTED = 0x0000,
        E_QUEST_MISSION_OBJECTIVE_COMPLETED = 0x0001,
        E_QUEST_FAILED = 0x0002,
        E_QUEST_ABORTED = 0x0003,
        E_QUEST_MISSION_COMPLETED = 0x0004,
    };

    public: 
    std::basic_string<char,std::char_traits<char>,std::allocator<char> > quest_name;
    uint32_t quest_id;
    Quest::QUEST_TYPE quest_event_type;
    bool quest_critical_path;
    
    public: 
    virtual CHashString InstanceClassId() const;
    virtual bool IsInstanceOf(CHashString) const;
    virtual SEventBaseData* Clone() const;
    virtual const char* EventType() const;
    virtual const char* EventName() const;
    virtual float GetNumericalField(CHashString) const;
    virtual uint32_t GetIntegerField(CHashString, bool&) const;
    virtual int32_t GetSignedIntegerField(CHashString, bool&) const;
    Quest(const Quest&);
    Quest();
    virtual ~Quest();
    Quest& operator=(const Quest&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    
    public: 
    static CHashString ClassId();
};

class OpenWorldProgressionEvent : public SEventBaseData {
    public: 
    uint32_t activity_tag;
    uint32_t location_item_type;
    uint32_t total_world_count;
    uint32_t total_active_count;
  
    public: 
    virtual CHashString InstanceClassId() const;
    virtual bool IsInstanceOf(CHashString) const;
    virtual SEventBaseData* Clone() const;
    virtual const char* EventType() const;
    virtual const char* EventName() const;
    virtual float GetNumericalField(CHashString) const;
    virtual uint32_t GetIntegerField(CHashString, bool&) const;
    virtual int32_t GetSignedIntegerField(CHashString, bool&) const;
    OpenWorldProgressionEvent(const OpenWorldProgressionEvent& other);
    OpenWorldProgressionEvent();
    virtual ~OpenWorldProgressionEvent();
    OpenWorldProgressionEvent& operator=(const OpenWorldProgressionEvent&);

    static CHashString ClassId();
};

#endif
