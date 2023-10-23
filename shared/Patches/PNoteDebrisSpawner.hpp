#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief Debris remover
    class PNoteDebrisSpawner
    {
        CP_SDK_NO_DEF_CTORS(PNoteDebrisSpawner);

        public:
            /// @brief Set from configuration
            static void SetFromConfig();
            /// @brief Set temp config
            /// @param p_RemoveDebris Should remove debris
            static void SetTemp(bool p_RemoveDebris);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches