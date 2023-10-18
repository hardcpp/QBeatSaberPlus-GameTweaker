#pragma once

#include <CP_SDK/UI/ViewController.hpp>
#include <CP_SDK/XUI/XUI.hpp>

namespace QBeatSaberPlus_GameTweaker::UI {

    /// @brief Settings left view controller
    class SettingsLeftView : public CP_SDK::UI::ViewController
    {
        CP_SDK_IL2CPP_INHERIT_CUSTOM("QBeatSaberPlus_GameTweaker.UI", SettingsLeftView, CP_SDK::UI::ViewController);
        CP_SDK_IL2CPP_DECLARE_CTOR_CHAIN(SettingsLeftView, CP_SDK::UI::ViewController);
        CP_SDK_IL2CPP_DECLARE_DTOR_MONOBEHAVIOUR_CHAIN(SettingsLeftView, CP_SDK::UI::ViewController);
        CP_SDK_UI_VIEW_CONTROLLER_INSTANCE();

        private:
            /// @brief On view creation
            void OnViewCreation_Impl();

        private:
            /// @brief Reset button
            void OnResetButton();

        private:
            /// @brief Documentation button
            void OnDocumentationButton();

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::UI

CP_SDK_IL2CPP_INHERIT_HELPERS(QBeatSaberPlus_GameTweaker::UI::SettingsLeftView);