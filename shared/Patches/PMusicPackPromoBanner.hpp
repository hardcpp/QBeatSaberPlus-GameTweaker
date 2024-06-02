#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief MusicPackPromoBanner remover
    class PMusicPackPromoBanner
    {
        CP_SDK_NO_DEF_CTORS(PMusicPackPromoBanner);

        public:
            /// @brief Set if MusicPackPromoBanner should be hidden
            /// @param p_Enabled New state
            static void SetEnabled(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches