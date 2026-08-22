#ifndef ENGINE_RUNTIME_CONTAINER_H
#define ENGINE_RUNTIME_CONTAINER_H

struct SRuntimeContainer;
struct SRuntimeContainerVariant;
struct SObjectID;

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "AvaCore/FileHandling/Parsing/Variant.h"

class CRuntimeContainerVariant {
    private: 
    uint64_t m_Base;
    const SRuntimeContainerVariant* m_Variant;
    
    public: 
    CRuntimeContainerVariant(uint64_t, const SRuntimeContainerVariant*);
    CRuntimeContainerVariant();
    uint32_t GetKey() const;
    EVariantType GetType() const;
    int32_t GetInteger() const;
    float GetFloat() const;
    const char* GetStringPtr() const;
    void GetVector2f(CVector2f&) const;
    void GetVector3f(CVector3f&) const;
    void GetVector4f(CVector4f&) const;
    void GetMatrix4x4(CMatrix4f&) const;
    const CVector2f& GetVector2Ref() const;
    const CVector3f& GetVector3Ref() const;
    const CVector4f& GetVector4Ref() const;
    void GetMatrix4x4Ref(CMatrix4f&) const;
    const CMatrix4f& GetMatrix4x4Ref() const;
    const SObjectID& GetObjectIDRef() const;
    void GetVectorRef(uint32_t&, const SEventID**) const;
    void GetVectorRef(uint32_t&, const unsigned char**) const;
    void GetVectorRef(uint32_t&, const float**) const;
    void GetVectorRef(uint32_t&, const int32_t**) const;
    void GetVectorInt(std::vector<int,std::allocator<int> >&) const;
    void GetVectorFloat(std::vector<float,std::allocator<float> >&) const;
    void GetVectorByte(std::vector<unsigned char,std::allocator<unsigned char> >&) const;
    void GetVectorEvents(std::vector<SEventID,std::allocator<SEventID> >&) const;
    operator bool() const;
    bool operator==(const CRuntimeContainerVariant&) const;
    bool operator!=(const CRuntimeContainerVariant&) const;
    bool operator<(const CRuntimeContainerVariant&) const;
    bool operator>(const CRuntimeContainerVariant&) const;
    bool operator<=(const CRuntimeContainerVariant&) const;
    bool operator>=(const CRuntimeContainerVariant&) const;
    CRuntimeContainerVariant operator++(int32_t);
    CRuntimeContainerVariant& operator++();
    CRuntimeContainerVariant operator--(int32_t);
    CRuntimeContainerVariant& operator--();
    CRuntimeContainerVariant& operator+=(int32_t);
    CRuntimeContainerVariant& operator-=(int32_t);
    CRuntimeContainerVariant& operator*();
    const CRuntimeContainerVariant& operator*() const;
    CRuntimeContainerVariant* operator->();
    const CRuntimeContainerVariant* operator->() const;
};

class CRuntimeContainer {
    private: 
    uint64_t m_Base;
    const SRuntimeContainer* m_Container;
    
    public: 
    CRuntimeContainer(uint64_t, const SRuntimeContainer*);
    CRuntimeContainer(const unsigned char*);
    CRuntimeContainer();
    void SetContainer(const unsigned char*);
    void ClearContainer();
    uint32_t GetNofContainers() const;
    uint32_t GetNofVariants() const;
    uint32_t GetKey() const;
    CRuntimeContainerVariant GetVariant(uint32_t) const;
    CRuntimeContainer GetContainer(uint32_t) const;
    bool GetValue(uint32_t, std::vector<SEventID,std::allocator<SEventID> >&) const;
    bool GetValue(uint32_t, std::vector<unsigned char,std::allocator<unsigned char> >&) const;
    bool GetValue(uint32_t, std::vector<float,std::allocator<float> >&) const;
    bool GetValue(uint32_t, std::vector<int,std::allocator<int> >&) const;
    bool GetValue(uint32_t, SObjectID&) const;
    bool GetValue(uint32_t, CMatrix4f&) const;
    bool GetValue(uint32_t, CVector4f&) const;
    bool GetValue(uint32_t, CVector3f&) const;
    bool GetValue(uint32_t, CVector2f&) const;
    bool GetValue(uint32_t, std::basic_string<char,std::char_traits<char>,std::allocator<char> >&) const;
    bool GetValue(uint32_t, const char*&) const;
    bool GetValue(uint32_t, float&) const;
    bool GetValue(uint32_t, CHashString&) const;
    bool GetValue(uint32_t, bool&) const;
    bool GetValue(uint32_t, int32_t&) const;
    const char* GetStringUnsafe(uint32_t) const;
    const char* GetStringPtr(uint32_t) const;
    bool GetVectorRef(uint32_t, uint32_t&, const SEventID**) const;
    bool GetVectorRef(uint32_t, uint32_t&, const unsigned char**) const;
    bool GetVectorRef(uint32_t, uint32_t&, const float**) const;
    bool GetVectorRef(uint32_t, uint32_t&, const int32_t**) const;
    const SRuntimeContainerVariant* variant_ptr_begin() const;
    const SRuntimeContainerVariant* variant_ptr_end() const;
    CRuntimeContainerVariant variant_begin() const;
    CRuntimeContainerVariant variant_end() const;
    const SRuntimeContainer* container_ptr_begin() const;
    const SRuntimeContainer* container_ptr_end() const;
    CRuntimeContainer container_begin() const;
    CRuntimeContainer container_end() const;
    operator bool() const;
    bool operator==(const CRuntimeContainer&) const;
    bool operator!=(const CRuntimeContainer&) const;
    bool operator<(const CRuntimeContainer&) const;
    bool operator>(const CRuntimeContainer&) const;
    bool operator<=(const CRuntimeContainer&) const;
    bool operator>=(const CRuntimeContainer&) const;
    CRuntimeContainer operator++(int32_t);
    CRuntimeContainer& operator++();
    CRuntimeContainer operator--(int32_t);
    CRuntimeContainer& operator--();
    CRuntimeContainer& operator*();
    const CRuntimeContainer& operator*() const;
    CRuntimeContainer* operator->();
    const CRuntimeContainer* operator->() const;
};

struct SRuntimeContainerHeader {
    public:
    uint32_t m_MagicNumber;
    uint32_t m_VersionNumber;
};

struct SRuntimeContainerVariant {
    public: 
    uint32_t m_Key;
    uint32_t m_DataOffset;
    unsigned char m_Type;
};

struct SRuntimeContainer {
    public:
    uint32_t m_Key;
    uint32_t m_DataOffset;
    uint16_t m_NumVariants;
    uint16_t m_NumContainers;
};

#endif
