#ifndef PROJECT_GAME_INPUT_ACTION_OVERRIDE_H
#define PROJECT_GAME_INPUT_ACTION_OVERRIDE_H

#include "Base/Misc/Event.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/GameObject.h"

class CInputActionOverride : public CGameObject, public NEvent::CEventHandler {
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnableEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DisableEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ActivateEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DeactivateEvent;
    bool m_Includer;
    std::vector<unsigned int,std::allocator<unsigned int> > m_ActionListSorted;
    bool m_Enabled;
    bool m_Active;
};

#endif
