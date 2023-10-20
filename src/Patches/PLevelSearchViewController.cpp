#include "Patches/PLevelSearchViewController.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/LevelSearchViewController.hpp>
#include <GlobalNamespace/IBeatmapLevelPack.hpp>
#include <TMPro/TextMeshProUGUI.hpp>
#include <UnityEngine/GameObject.hpp>
#include <UnityEngine/Transform.hpp>

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static CP_SDK::Utils::MonoPtr<GameObject> PLevelSearchViewController_FilterButton;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set if we remove base game filter
    /// @param p_Enabled New state
    void PLevelSearchViewController::SetRemoveBaseGameFilter(bool p_Enabled)
    {
        if (!PLevelSearchViewController_FilterButton)
            return;

        PLevelSearchViewController_FilterButton->set_active(!p_Enabled);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        LevelSearchViewController_Setup, &LevelSearchViewController::DidActivate,
        void, LevelSearchViewController* __Instance,

        bool __a, bool __b, bool __c)
    {
        LevelSearchViewController_Setup(__Instance, __a, __b, __c);

        if (__Instance->filterParamsText)
            PLevelSearchViewController_FilterButton = __Instance->filterParamsText->get_transform()->get_parent()->get_gameObject();
        else
            PLevelSearchViewController_FilterButton = nullptr;

        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled)
        {
            /// Apply
            PLevelSearchViewController::SetRemoveBaseGameFilter(l_Config->LevelSelection->RemoveBaseGameFilterButton);
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches