#ifndef COMPONENT_APP_SYSTEM_H
#define COMPONENT_APP_SYSTEM_H

class SResourceCache;

#include "Common/Adf/AdfCommon.h"

namespace Base {
    class IAppSystem {
        bool m_HasBeenInitialized;
    };

    class SAppSystemInitContext {
        public: 
        SResourceCache* m_ResourceCache;
        SAdfContext* m_AdfContext;
    };
};

#endif
