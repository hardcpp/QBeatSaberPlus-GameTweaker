#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief ObstacleSaberSparkleEffect remover
    class PObstacleSaberSparkleEffectManager
    {
        DISABLE_CONSTRUCTORS(PObstacleSaberSparkleEffectManager);

        public:
            /// @brief Set if the effect is removed
            /// @param p_Enabled New state
            static void SetRemoveObstacleParticles(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches