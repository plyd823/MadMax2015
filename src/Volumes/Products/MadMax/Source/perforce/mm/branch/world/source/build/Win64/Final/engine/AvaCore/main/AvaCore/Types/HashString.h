#ifndef ENGINE_HASHSTRING_H
#define ENGINE_HASHSTRING_H

#include <cstdint>
#include <memory>
#include <string>

class CHashString {
    public:
    uint32_t m_Hash;

    public: 
    CHashString(const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&);
    CHashString(uint32_t, const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&);
    CHashString(const char*);
    CHashString(uint32_t, const char*);
    CHashString(CHashString&&);
    CHashString(const CHashString&);
    CHashString(uint32_t hash) : m_Hash(hash) {};
    CHashString();
    CHashString& operator=(const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&);
    CHashString& operator=(const char*);
    CHashString& operator=(CHashString&&);
    CHashString& operator=(const CHashString&);
    void reset(uint32_t);
    void reset(const std::basic_string<char,std::char_traits<char>,std::allocator<char> >&);
    void reset(const char*);
    bool operator==(uint32_t) const;
    
    bool operator==(const CHashString& rhs) const {
        return get() == rhs.get();
    }

    bool operator!=(uint32_t) const;
    bool operator!=(const CHashString&) const;
    bool operator<(const CHashString& other) const {
        return this->m_Hash < other.m_Hash;
    };
    uint32_t get() const {
        return m_Hash;
    };
    
    static uint32_t Hash(const char*);
};

#endif
