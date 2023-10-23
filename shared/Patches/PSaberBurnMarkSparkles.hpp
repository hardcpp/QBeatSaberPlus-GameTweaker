#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief SaberBurnMarkSparkles remover
    class PSaberBurnMarkSparkles
    {
        CP_SDK_NO_DEF_CTORS(PSaberBurnMarkSparkles);

        public:
            /// @brief Set if the effect is removed
            /// @param p_Enabled New state
            static void SetRemoveSaberBurnMarkSparkles(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches