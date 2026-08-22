#ifndef PROJECT_GAME_ITEM_ATTACHED_EFFECT_COMPONENT_H
#define PROJECT_GAME_ITEM_ATTACHED_EFFECT_COMPONENT_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "AvaCore/Math/Matrix.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/EffectSystem/EffectInstance.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/EffectSystem/GameEffect.h"

class CItemAttachedEffectComponent {
    struct SAttachedEffectInstance {
        public:
        int32_t m_Index;
        CEffectInstance* m_Effect;
    };

    struct SAttachedEffect {
        public:
        CMatrix4f m_Transform;
        uint32_t m_NameHash;
        SGameEffectContainer* m_EffectContainer;
    };

    std::vector<CItemAttachedEffectComponent::SAttachedEffectInstance,std::allocator<CItemAttachedEffectComponent::SAttachedEffectInstance> > m_AttachedEffectsInstances;
    std::vector<CItemAttachedEffectComponent::SAttachedEffect,std::allocator<CItemAttachedEffectComponent::SAttachedEffect> > m_AttachedEffects;
};

#endif
