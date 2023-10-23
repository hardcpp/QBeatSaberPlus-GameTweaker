#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief SaberBurnMarkArea remover
    class PSaberBurnMarkArea
    {
        CP_SDK_NO_DEF_CTORS(PSaberBurnMarkArea);

        public:
            /// @brief Set if the effect is removed
            /// @param p_Enabled New state
            static void SetRemoveSaberBurnMarks(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches