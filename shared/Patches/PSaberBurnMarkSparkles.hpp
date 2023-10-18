#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief SaberBurnMarkSparkles remover
    class PSaberBurnMarkSparkles
    {
        DISABLE_CONSTRUCTORS(PSaberBurnMarkSparkles);

        public:
            /// @brief Set if the effect is removed
            /// @param p_Enabled New state
            static void SetRemoveSaberBurnMarkSparkles(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches