#pragma once

#include <CP_SDK/UI/ViewController.hpp>
#include <CP_SDK/XUI/XUI.hpp>

namespace QBeatSaberPlus_GameTweaker::UI {

    namespace _u
    {
        using namespace CP_SDK::XUI;
        using namespace UnityEngine;
    }

    /// @brief Settings main view controller
    class SettingsMainView : public CP_SDK::UI::ViewController
    {
        CP_SDK_IL2CPP_INHERIT("QBeatSaberPlus_GameTweaker.UI", SettingsMainView, CP_SDK::UI::ViewController);
        CP_SDK_IL2CPP_DECLARE_CTOR_CHILD(SettingsMainView);
        CP_SDK_IL2CPP_DECLARE_DTOR_MONOBEHAVIOUR_CHILD(SettingsMainView);
        CP_SDK_UI_VIEW_CONTROLLER_INSTANCE();

        private:
            _u::XUITabControl::Ptr   m_TabControl;

            _u::XUIToggle::Ptr       m_ParticlesTab_RemoveDebris;
            _u::XUIToggle::Ptr       m_ParticlesTab_RemoveWorldParticles;
            _u::XUIToggle::Ptr       m_ParticlesTab_RemoveCutParticles;
            _u::XUIToggle::Ptr       m_ParticlesTab_RemoveObstacleParticles;
            _u::XUIToggle::Ptr       m_ParticlesTab_RemoveFloorBurnMarkParticles;
            _u::XUIToggle::Ptr       m_ParticlesTab_RemoveFloorBurnMarkEffects;
            _u::XUIToggle::Ptr       m_ParticlesTab_RemoveSaberClashEffects;

            _u::XUIToggle::Ptr       m_EnvironmentTab_RemoveMusicBandLogo;
            _u::XUIToggle::Ptr       m_EnvironmentTab_RemoveFullComboLossAnimation;

            _u::XUIColorInput::Ptr   m_LevelSelectionTab_HighlightPlayedSongColor;
            _u::XUIToggle::Ptr       m_LevelSelectionTab_HighlightPlayedSong;
            _u::XUIColorInput::Ptr   m_LevelSelectionTab_HighlightPlayedSongAllColor;
            _u::XUIToggle::Ptr       m_LevelSelectionTab_RemoveBaseGameFilterButton;

            _u::XUIToggle::Ptr       m_PlayerOptionsTab_ReorderPlayerSettings;
            _u::XUIToggle::Ptr       m_PlayerOptionsTab_AddOverrideLightIntensityOption;
            _u::XUIToggle::Ptr       m_PlayerOptionsTab_MergeLightEffectFilterOptions;

            _u::XUIToggle::Ptr       m_MainMenuTab_OverrideMenuEnvColors;
            _u::XUIColorInput::Ptr   m_MainMenuTab_BaseColor;
            _u::XUIColorInput::Ptr   m_MainMenuTab_LevelClearedColor;
            _u::XUIColorInput::Ptr   m_MainMenuTab_LevelFailedColor;
            _u::XUIToggle::Ptr       m_MainMenuTab_RemoveNewContentPromotional;
            _u::XUIToggle::Ptr       m_MainMenuTab_DisableFireworks;

        private:
            bool m_PreventChanges;

        private:
            /// @brief On view creation
            void OnViewCreation_Impl();
            /// @brief On view deactivation
            void OnViewDeactivation_Impl();

        private:
            /// @brief Build particles tab
            std::shared_ptr<_u::IXUIElement> BuildParticlesTab();
            /// @brief Build environment tab
            std::shared_ptr<_u::IXUIElement> BuildEnvironmentTab();
            /// @brief Build level selection tab
            std::shared_ptr<_u::IXUIElement> BuildLevelSelectionTab();
            /// @brief Build player options tab
            std::shared_ptr<_u::IXUIElement> BuildPlayerOptionsTab();
            /// @brief Build main menu tab
            std::shared_ptr<_u::IXUIElement> BuildMainMenuTab();

        private:
            /// @brief When settings are changed
            void OnSettingChanged();
            /// @brief When settings are changed
            void OnSettingChangedOverrideMenuColor();
            /// @brief When settings are changed
            void OnSettingChangedLevelClearedColor();
            /// @brief When settings are changed
            void OnSettingChangedLevelFailedColor();

        public:
            /// Reset settings
            void RefreshSettings();

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::UI

CP_SDK_IL2CPP_INHERIT_HELPERS(QBeatSaberPlus_GameTweaker::UI::SettingsMainView);