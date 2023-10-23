#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief PlayerSettingsPanelController modifier
    class PPlayerSettingsPanelController
    {
        CP_SDK_NO_DEF_CTORS(PPlayerSettingsPanelController);

        public:
            /// @brief Set if the effect is enabled
            /// @param p_Enabled New state
            static void SetReorderEnabled(bool p_Enabled, bool p_AddOverrideLightsIntensityOption);
            /// @brief Should merge the two lights options
            /// @param p_Enabled New state
            static void SetLightsOptionMerging(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches