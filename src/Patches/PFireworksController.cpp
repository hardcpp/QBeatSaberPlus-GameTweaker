#include "GTConfig.hpp"

#include <CP_SDK/Utils/Il2cpp.hpp>

#include <GlobalNamespace/FireworksController.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        FireworksController_OnEnable, &FireworksController::OnEnable,
        void, FireworksController* __Instance)
    {
        auto l_Config = GTConfig::Instance();
        if (!l_Config->Enabled || !l_Config->MainMenu->DisableFireworks)
        {
            FireworksController_OnEnable(__Instance);
            return;
        }

        /// Skip method
        return;
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches