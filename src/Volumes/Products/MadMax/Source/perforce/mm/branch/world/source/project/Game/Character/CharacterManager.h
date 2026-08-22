#ifndef PROJECT_GAME_CHARACTERMANAGER_H
#define PROJECT_GAME_CHARACTERMANAGER_H

namespace NCharacterSystem {
    class CCharacterManagerBase {

    };
};

#include "AvaCore/Misc/Singleton.h"
#include "project/Game/Character/Character.h"
#include "build/Win64/Final/ctg/components/Base/include/Base/Misc/AppSystem.h"

class CCharacterManager : public NCharacterSystem::CCharacterManagerBase, public CAvaSingle<CCharacterManager>, public Base::IAppSystem {
    public:
    CCharacter* GetFirstCharacter();
    CCharacter* GetNextCharacter();
};

#endif
