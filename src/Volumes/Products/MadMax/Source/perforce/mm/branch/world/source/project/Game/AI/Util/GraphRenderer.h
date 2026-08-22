#ifndef PROJECT_GAME_GRAPH_RENDERER_H
#define PROJECT_GAME_GRAPH_RENDERER_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "AvaCore/Math/Vector.h"

class CGraphRenderer {
    struct SEntry {
        float m_Time;
        float m_Value;
        CVector4f m_Color;
    };

    private:
    float m_Time;
    float m_MaxTime;
    float m_MaxValue;
    float m_MinValue;
    std::vector<CGraphRenderer::SEntry,std::allocator<CGraphRenderer::SEntry> > m_Entries;
    CVector4f m_LineColor;
    CVector4f m_BackgroundColor;
    CVector4f m_GridColor;
};

#endif
