#ifndef COMPONENT_I_EVENT_DATA_H
#define COMPONENT_I_EVENT_DATA_H

#include "AvaCore/Types/HashString.h"

namespace NMetricsEvent {

    class IEventData {
        public: 
        virtual void ToJson(std::basic_string<char,std::char_traits<char>,std::allocator<char> >&) const;
        virtual const char* ServiceName() const;
        virtual bool IsInstanceOf(CHashString) const;
        virtual bool RequiresImmediateProcessing() const;
        IEventData(const NMetricsEvent::IEventData&);
        IEventData();
        NMetricsEvent::IEventData& operator=(const NMetricsEvent::IEventData&);
    };

    class IEventDataHelper {
        public:
        enum EBuiltInValues : int32_t {
            BUILTIN_METRIC_CAMERA_X = 0x0000,
            BUILTIN_METRIC_CAMERA_Y = 0x0001,
            BUILTIN_METRIC_CAMERA_Z = 0x0002,
            BUILTIN_METRIC_MACHINE_NAME = 0x0003,
            BUILTIN_METRIC_USER_NAME = 0x0004,
            BUILTIN_METRIC_CODE_VERSION = 0x0005,
            BUILTIN_METRIC_CONTENT_VERSION = 0x0006,
            BUILTIN_METRIC_PLATFORM = 0x0007,
        };

        private: 
        std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > m_StringNames;
        std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > m_IntegerNames;
        std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > m_FloatNames;
        std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > m_BoolNames;
        std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > m_StringValues;
        std::vector<int,std::allocator<int> > m_IntegerValues;
        std::vector<float,std::allocator<float> > m_FloatValues;
        std::vector<bool,std::allocator<bool> > m_BoolValues;
        
        public: 
        void AddStringValue(const char*, const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&, bool);
        void AddStringValue(const char*, const char*, bool);
        void AddIntegerValue(const char*, int32_t);
        void AddFloatValue(const char*, float);
        void AddBoolValue(const char*, bool);
        void AddBuiltInValue(const char*, NMetricsEvent::IEventDataHelper::EBuiltInValues);
        void ToJson(std::basic_string<char,std::char_traits<char>,std::allocator<char> >&) const;
        IEventDataHelper(const NMetricsEvent::IEventDataHelper&);
        IEventDataHelper();
        ~IEventDataHelper();
        NMetricsEvent::IEventDataHelper& operator=(const NMetricsEvent::IEventDataHelper&);
        void* __vecDelDtor(uint32_t);
        
        public: 
        static std::basic_string<char,std::char_traits<char>,std::allocator<char> > escapeJsonString(const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&);
    };
};

#endif
