#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches { namespace Lights {

    /// @brief LightSwitchEventEffect patch
    class PLightsPatches
    {
        DISABLE_CONSTRUCTORS(PLightsPatches);

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