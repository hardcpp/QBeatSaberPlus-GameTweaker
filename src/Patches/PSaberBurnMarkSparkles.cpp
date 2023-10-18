#include "Patches/PSaberBurnMarkSparkles.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/SaberBurnMarkSparkles.hpp>
#include <UnityEngine/GameObject.hpp>
#include <UnityEngine/Transform.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static CP_SDK::Utils::MonoPtr<SaberBurnMarkSparkles> PSaberBurnMarkSparkles_SaberBurnMarkSparkles;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set if the effect is removed
    /// @param p_Enabled New state
    void PSaberBurnMarkSparkles::SetRemoveSaberBurnMarkSparkles(bool p_Enabled)
    {
        if (!PSaberBurnMarkSparkles_SaberBurnMarkSparkles)
            return;

        PSaberBurnMarkSparkles_SaberBurnMarkSparkles->get_gameObject()->set_active(!p_Enabled);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        SaberBurnMarkSparkles_Start, &SaberBurnMarkSparkles::Start,
        void, SaberBurnMarkSparkles* __Instance)
    {
        SaberBurnMarkSparkles_Start(__Instance);

        PSaberBurnMarkSparkles_SaberBurnMarkSparkles = __Instance;

        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled)
        {
            /// Apply
            PSaberBurnMarkSparkles::SetRemoveSaberBurnMarkSparkles(l_Config->RemoveSaberBurnMarkSparkles);
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches