#include "Managers/CustomMenuLightManager.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/Il2cpp.hpp>

#include <GlobalNamespace/MenuLightsManager.hpp>
#include <GlobalNamespace/MenuLightsPresetSO.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        MenuLightsManager_SetColorPreset, &MenuLightsManager::SetColorPreset,
        void, MenuLightsManager* __Instance,

        MenuLightsPresetSO* __a, bool __b, float __c)
    {
        MenuLightsManager_SetColorPreset(__Instance, Managers::CustomMenuLightManager::GetPresetForPatch(__a), __b, __c);
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches