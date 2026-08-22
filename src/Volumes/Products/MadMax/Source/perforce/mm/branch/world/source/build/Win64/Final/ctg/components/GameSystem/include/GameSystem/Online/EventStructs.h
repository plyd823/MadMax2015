#ifndef COMPONENT_EVENT_STRUCTS_H
#define COMPONENT_EVENT_STRUCTS_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "GameSystem/Online/IEventData.h"

struct SEventBaseData : public NMetricsEvent::IEventData {
    public:
    static std::basic_string<char,std::char_traits<char>,std::allocator<char> > m_PlayerId;
    static std::basic_string<char,std::char_traits<char>,std::allocator<char> > m_ProfileGuid;
    static std::basic_string<char,std::char_traits<char>,std::allocator<char> > m_SessionId;
    static const uint32_t m_EventVersion;
};

#endif
