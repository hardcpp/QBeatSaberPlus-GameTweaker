#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief SaberBurnMarkArea remover
    class PSaberBurnMarkArea
    {
        DISABLE_CONSTRUCTORS(PSaberBurnMarkArea);

        public:
            /// @brief Set if the effect is removed
            /// @param p_Enabled New state
            static void SetRemoveSaberBurnMarks(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches