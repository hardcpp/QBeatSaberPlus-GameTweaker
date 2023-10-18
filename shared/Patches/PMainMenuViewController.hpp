#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief MainMenuViewController
    class PMainMenuViewController
    {
        DISABLE_CONSTRUCTORS(PMainMenuViewController);

        public:
            /// @brief Set if Pack music promo banner should be hidden
            /// @param p_Enabled New state
            static void SetRemovePackMusicPromoBanner(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches