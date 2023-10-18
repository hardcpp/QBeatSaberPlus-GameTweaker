#include "Patches/PSaberBurnMarkArea.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/SaberBurnMarkArea.hpp>
#include <UnityEngine/GameObject.hpp>
#include <UnityEngine/Transform.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static CP_SDK::Utils::MonoPtr<SaberBurnMarkArea> PSaberBurnMarkArea_SaberBurnMarkArea;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set if the effect is removed
    /// @param p_Enabled New state
    void PSaberBurnMarkArea::SetRemoveSaberBurnMarks(bool p_Enabled)
    {
        if (!PSaberBurnMarkArea_SaberBurnMarkArea)
            return;

        PSaberBurnMarkArea_SaberBurnMarkArea->get_gameObject()->set_active(!p_Enabled);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        SaberBurnMarkArea_Start, &SaberBurnMarkArea::Start,
        void, SaberBurnMarkArea* __Instance)
    {
        SaberBurnMarkArea_Start(__Instance);

        PSaberBurnMarkArea_SaberBurnMarkArea = __Instance;

        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled)
        {
            /// Apply
            PSaberBurnMarkArea::SetRemoveSaberBurnMarks(l_Config->RemoveSaberBurnMarks);
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches