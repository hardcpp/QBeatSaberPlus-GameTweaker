#include "Patches/PMusicPackPromoBanner.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/MusicPackPromoBanner.hpp>
#include <UnityEngine/GameObject.hpp>
#include <UnityEngine/Transform.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static CP_SDK::Utils::MonoPtr<MusicPackPromoBanner>  PMusicPackPromoBanner_Instance;
    static std::vector<bool>                             PMusicPackPromoBanner_States;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set if PromoViewController should be hidden
    /// @param p_Enabled New state
    void PMusicPackPromoBanner::SetEnabled(bool p_Enabled)
    {
        if (!PMusicPackPromoBanner_Instance)
            return;

        for (int l_I = 0; l_I < PMusicPackPromoBanner_Instance->get_transform()->get_childCount(); ++l_I)
        {
            auto l_NewState = p_Enabled ? false : (l_I < PMusicPackPromoBanner_States.size() ? PMusicPackPromoBanner_States[l_I] : false);
            PMusicPackPromoBanner_Instance->get_transform()->GetChild(l_I)->get_gameObject()->SetActive(l_NewState);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        MusicPackPromoBanner_Setup, &MusicPackPromoBanner::Setup,
        void, MusicPackPromoBanner* __Instance,

        __DlcPromoPanelModel__PromoInfo* __a, bool __b)
    {
        MusicPackPromoBanner_Setup(__Instance, __a, __b);

        if (__Instance != PMusicPackPromoBanner_Instance)
            PMusicPackPromoBanner_States.clear();

        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled && PMusicPackPromoBanner_States.size() == 0)
        {
            /// Store instance
            PMusicPackPromoBanner_Instance = __Instance;

            /// Backup original states
            for (int l_I = 0; l_I < __Instance->get_transform()->get_childCount(); ++l_I)
                PMusicPackPromoBanner_States.push_back(__Instance->get_transform()->GetChild(l_I)->get_gameObject()->get_activeSelf());

            /// Apply
            PMusicPackPromoBanner::SetEnabled(l_Config->MainMenu->RemoveNewContentPromotional);
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches