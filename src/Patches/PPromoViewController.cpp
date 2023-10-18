#include "Patches/PPromoViewController.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/PromoViewController.hpp>
#include <UnityEngine/GameObject.hpp>
#include <UnityEngine/Transform.hpp>

using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static CP_SDK::Utils::MonoPtr<PromoViewController>  PPromoViewController_Instance;
    static std::vector<bool>                            PPromoViewController_States;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set if PromoViewController should be hidden
    /// @param p_Enabled New state
    void PPromoViewController::SetEnabled(bool p_Enabled)
    {
        if (!PPromoViewController_Instance)
            return;

        for (int l_I = 0; l_I < PPromoViewController_Instance->get_transform()->get_childCount(); ++l_I)
        {
            auto l_NewState = p_Enabled ? false : (l_I < PPromoViewController_States.size() ? PPromoViewController_States[l_I] : false);
            PPromoViewController_Instance->get_transform()->GetChild(l_I)->get_gameObject()->SetActive(l_NewState);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        PromoViewController_DidActivate, &PromoViewController::DidActivate,
        void, PromoViewController* __Instance,

        bool __a, bool __b, bool __c)
    {
        PromoViewController_DidActivate(__Instance, __a, __b, __c);

        if (__Instance != PPromoViewController_Instance)
            PPromoViewController_States.clear();

        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled && PPromoViewController_States.size() == 0)
        {
            /// Store instance
            PPromoViewController_Instance = __Instance;

            /// Backup original states
            for (int l_I = 0; l_I < __Instance->get_transform()->get_childCount(); ++l_I)
                PPromoViewController_States.push_back(__Instance->get_transform()->GetChild(l_I)->get_gameObject()->get_activeSelf());

            /// Apply
            PPromoViewController::SetEnabled(l_Config->MainMenu->RemoveNewContentPromotional);
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches