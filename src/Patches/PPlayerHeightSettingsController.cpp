#include "GTConfig.hpp"

#include <CP_SDK/Utils/Il2cpp.hpp>

#include <sstream>

#include <GlobalNamespace/PlayerHeightSettingsController.hpp>
#include <TMPro/TextMeshProUGUI.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        PlayerHeightSettingsController_RefreshUI, &PlayerHeightSettingsController::RefreshUI,
        void, PlayerHeightSettingsController* __Instance)
    {
        PlayerHeightSettingsController_RefreshUI(__Instance);

        if (GTConfig::Instance()->Enabled)
        {
            std::ostringstream l_Builder;
            l_Builder.precision(2);
            l_Builder << std::fixed << __Instance->____value;

            __Instance->____text->set_text(l_Builder.str());
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches