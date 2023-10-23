#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches { namespace Lights {

    /// @brief LightSwitchEventEffect patch
    class PLightsPatches
    {
        CP_SDK_NO_DEF_CTORS(PLightsPatches);

        public:
            /// @brief Set from configuration
            static void SetFromConfig();
            /// @brief Set temp config
            /// @param p_Intensity New intensity
            static void SetTempLightIntensity(float p_Intensity);

            static void SetIsValidScene(bool p_IsValid);

    };

}   ///< namespace Lights
}   ///< namespace QBeatSaberPlus_GameTweaker::Patches