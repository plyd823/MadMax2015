#ifndef PROJECT_GAME_AVATAR_H
#define PROJECT_GAME_AVATAR_H

#include "AvaCore/Types/Rtti.h"
#include "project/Game/Character/Character.h"
#include "project/Game/Equipment/Item/Weapon/Weapon.h"

class CAvatar : public CRtti {
    protected:
    CCharacter* m_Character;
    CAvatar* weak_this;
    uint32_t m_HitByBulletTimeStamp;
    CWeapon* m_FiringWeapon;
    CVector3f m_DefaultAimTargetMS;

    public:
    void UpdateRender(float dt, float dtf, float real_dt);
};

#endif
