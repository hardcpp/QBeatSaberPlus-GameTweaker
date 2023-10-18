#include "Patches/PMainMenuViewController.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/MainMenuViewController.hpp>
#include <GlobalNamespace/MusicPackPromoBanner.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static CP_SDK::Utils::MonoPtr<MusicPackPromoBanner> PMainMenuViewController_MusicPackPromoBanner;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set if Pack music promo banner should be hidden
    /// @param p_Enabled New state
    void PMainMenuViewController::SetRemovePackMusicPromoBanner(bool p_Enabled)
    {
        if (!PMainMenuViewController_MusicPackPromoBanner)
            return;

        PMainMenuViewController_MusicPackPromoBanner->get_gameObject()->SetActive(!p_Enabled);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        MainMenuViewController_DidActivate, &MainMenuViewController::DidActivate,
        void, MainMenuViewController* __Instance,

        bool __a, bool __b, bool __c)
    {
        MainMenuViewController_DidActivate(__Instance, __a, __b, __c);

        if (PMainMenuViewController_MusicPackPromoBanner != __Instance->musicPackPromoBanner)
            PMainMenuViewController_MusicPackPromoBanner = __Instance->musicPackPromoBanner;

        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled)
        {
            PMainMenuViewController::SetRemovePackMusicPromoBanner(l_Config->MainMenu->RemoveNewContentPromotional);
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches