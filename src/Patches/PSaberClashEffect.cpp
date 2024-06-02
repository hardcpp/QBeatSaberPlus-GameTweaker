#include "Patches/PSaberClashEffect.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/SaberClashEffect.hpp>
#include <UnityEngine/GameObject.hpp>
#include <UnityEngine/ParticleSystem.hpp>
#include <UnityEngine/Transform.hpp>

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static CP_SDK::Utils::MonoPtr<ParticleSystem> PSaberClashEffect_SparkleParticleSystem;
    static CP_SDK::Utils::MonoPtr<ParticleSystem> PSaberClashEffect_GlowParticleSystem;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set if the effect is removed
    /// @param p_Enabled New state
    void PSaberClashEffect::SetRemoveClashEffects(bool p_Enabled)
    {
        if (p_Enabled)
        {
            if (PSaberClashEffect_SparkleParticleSystem) PSaberClashEffect_SparkleParticleSystem->Pause();
            if (PSaberClashEffect_GlowParticleSystem)    PSaberClashEffect_GlowParticleSystem->Pause();
        }
        else
        {
            if (PSaberClashEffect_SparkleParticleSystem) PSaberClashEffect_SparkleParticleSystem->Play();
            if (PSaberClashEffect_GlowParticleSystem)    PSaberClashEffect_GlowParticleSystem->Play();
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        SaberClashEffect_Start, &SaberClashEffect::Start,
        void, SaberClashEffect* __Instance)
    {
        SaberClashEffect_Start(__Instance);

        PSaberClashEffect_SparkleParticleSystem = __Instance->____sparkleParticleSystem;
        PSaberClashEffect_GlowParticleSystem    = __Instance->____glowParticleSystem;

        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled)
        {
            /// Apply
            PSaberClashEffect::SetRemoveClashEffects(l_Config->RemoveSaberClashEffects);
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches