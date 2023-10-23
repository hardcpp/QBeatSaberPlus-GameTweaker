#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief SaberClashEffect remover
    class PSaberClashEffect
    {
        CP_SDK_NO_DEF_CTORS(PSaberClashEffect);

        public:
            /// @brief Set if the effect is removed
            /// @param p_Enabled New state
            static void SetRemoveClashEffects(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches