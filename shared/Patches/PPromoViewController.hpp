#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief PromoViewController remover
    class PPromoViewController
    {
        CP_SDK_NO_DEF_CTORS(PPromoViewController);

        public:
            /// @brief Set if PromoViewController should be hidden
            /// @param p_Enabled New state
            static void SetEnabled(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches