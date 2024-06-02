#include "GTConfig.hpp"
#include "Logger.hpp"

#include <CP_SDK/Utils/Il2cpp.hpp>

#include <GlobalNamespace/ComboUIController.hpp>
#include <UnityEngine/GameObject.hpp>
#include <UnityEngine/Transform.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_ORIG_MATCH(
        ComboUIController_HandleComboBreakingEventHappened, &ComboUIController::HandleComboBreakingEventHappened,
        void, ComboUIController* __Instance)
    {
        auto l_Config = GTConfig::Instance();
        if (!l_Config->Enabled || !l_Config->Environment->RemoveFullComboLossAnimation)
        {
            ComboUIController_HandleComboBreakingEventHappened(__Instance);
            return; ///< Continue to original function
        }

        if (!__Instance->____fullComboLost)
        {
            __Instance->____fullComboLost = true;

            auto l_Line0 = __Instance->get_transform()->Find("Line0");
            auto l_Line1 = __Instance->get_transform()->Find("Line1");

            if (l_Line0) l_Line0->get_gameObject()->SetActive(false);
            if (l_Line1) l_Line1->get_gameObject()->SetActive(false);

            return;   ///< Skip original function
        }

        ComboUIController_HandleComboBreakingEventHappened(__Instance);
        return; ///< Continue to original function
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches