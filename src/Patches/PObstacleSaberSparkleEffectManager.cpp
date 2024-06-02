#include "Patches/PObstacleSaberSparkleEffectManager.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/ObstacleSaberSparkleEffectManager.hpp>
#include <GlobalNamespace/ObstacleSaberSparkleEffect.hpp>
#include <UnityEngine/GameObject.hpp>
#include <UnityEngine/Transform.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static std::vector<CP_SDK::Utils::MonoPtr<ObstacleSaberSparkleEffect>> PObstacleSaberSparkleEffectManager_ObstacleSaberSparkleEffects;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set if the effect is removed
    /// @param p_Enabled New state
    void PObstacleSaberSparkleEffectManager::SetRemoveObstacleParticles(bool p_Enabled)
    {
        if (PObstacleSaberSparkleEffectManager_ObstacleSaberSparkleEffects.empty())
            return;

        for (auto& l_Current : PObstacleSaberSparkleEffectManager_ObstacleSaberSparkleEffects)
        {
            if (!l_Current || !l_Current->get_gameObject())
                continue;

            l_Current->get_gameObject()->set_active(!p_Enabled);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        ObstacleSaberSparkleEffectManager_Start, &ObstacleSaberSparkleEffectManager::Start,
        void, ObstacleSaberSparkleEffectManager* __Instance)
    {
        ObstacleSaberSparkleEffectManager_Start(__Instance);

        PObstacleSaberSparkleEffectManager_ObstacleSaberSparkleEffects.clear();
        for (auto& l_Current : __Instance->____effects)
            PObstacleSaberSparkleEffectManager_ObstacleSaberSparkleEffects.push_back(l_Current.unsafePtr());

        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled)
        {
            /// Apply
            PObstacleSaberSparkleEffectManager::SetRemoveObstacleParticles(l_Config->RemoveObstacleParticles);
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches