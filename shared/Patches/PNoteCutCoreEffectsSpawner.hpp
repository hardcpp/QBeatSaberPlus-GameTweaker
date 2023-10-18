#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief Cut ribbon remover
    class PNoteCutCoreEffectsSpawner
    {
        DISABLE_CONSTRUCTORS(PNoteCutCoreEffectsSpawner);

        public:
            /// @brief Set if the effect is removed
            /// @param p_Enabled New state
            static void SetRemoveCutParticles(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches