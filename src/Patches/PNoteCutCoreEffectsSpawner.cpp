#include "Patches/PNoteCutCoreEffectsSpawner.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/NoteCutCoreEffectsSpawner.hpp>
#include <GlobalNamespace/NoteCutParticlesEffect.hpp>
#include <UnityEngine/GameObject.hpp>
#include <UnityEngine/Transform.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static CP_SDK::Utils::MonoPtr<NoteCutParticlesEffect> PNoteCutCoreEffectsSpawner_NoteCutParticlesEffect;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set if the effect is removed
    /// @param p_Enabled New state
    void PNoteCutCoreEffectsSpawner::SetRemoveCutParticles(bool p_Enabled)
    {
        if (!PNoteCutCoreEffectsSpawner_NoteCutParticlesEffect)
            return;

        PNoteCutCoreEffectsSpawner_NoteCutParticlesEffect->get_gameObject()->set_active(!p_Enabled);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        NoteCutCoreEffectsSpawner_Start, &NoteCutCoreEffectsSpawner::Start,
        void, NoteCutCoreEffectsSpawner* __Instance)
    {
        NoteCutCoreEffectsSpawner_Start(__Instance);

        PNoteCutCoreEffectsSpawner_NoteCutParticlesEffect = __Instance->____noteCutParticlesEffect;

        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled)
        {
            /// Apply
            PNoteCutCoreEffectsSpawner::SetRemoveCutParticles(l_Config->RemoveAllCutParticles);
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches