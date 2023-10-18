#include "UI/SettingsMainView.hpp"
#include "Managers/CustomMenuLightManager.hpp"
#include "GameTweaker.hpp"
#include "GTConfig.hpp"
#include "Logger.hpp"

#include <CP_SDK/UI/ValueFormatters.hpp>
#include <CP_SDK/Unity/Extensions/ColorU.hpp>

using namespace CP_SDK::Unity::Extensions;
using namespace CP_SDK::XUI;
using namespace UnityEngine;

namespace QBeatSaberPlus_GameTweaker::UI {

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_INHERIT_INIT(SettingsMainView);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Constructor
    CP_SDK_IL2CPP_DECLARE_CTOR_CHAIN_IMPL(SettingsMainView, CP_SDK::UI::ViewController)
    {
        m_PreventChanges = false;

        OnViewCreation      = {this, &SettingsMainView::OnViewCreation_Impl};
        OnViewDeactivation  = {this, &SettingsMainView::OnViewDeactivation_Impl};
    }
    /// @brief Destructor
    CP_SDK_IL2CPP_DECLARE_DTOR_MONOBEHAVIOUR_CHAIN_IMPL(SettingsMainView, CP_SDK::UI::ViewController)
    {

    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief On view creation
    void SettingsMainView::OnViewCreation_Impl()
    {
        Templates::FullRectLayoutMainView({
            Templates::TitleBar(u"Game Tweaker | Settings"),

            XUITabControl::Make({
                {u"Particles",       BuildParticlesTab()},
                {u"Environment",     BuildEnvironmentTab()},
                {u"LevelSelection",  BuildLevelSelectionTab()},
                {u"PlayerOptions",   BuildPlayerOptionsTab()},
                {u"MainMenu",        BuildMainMenuTab()}
            })
            ->Bind(&m_TabControl)
            ->AsShared()
        })
        ->SetBackground(true, std::nullopt, true)
        ->BuildUI(get_transform());

        /// Refresh UI
        OnSettingChanged();
    }
    /// @brief On view deactivation
    void SettingsMainView::OnViewDeactivation_Impl()
    {
        GTConfig::Instance()->Save();
        Managers::CustomMenuLightManager::SwitchToBase();
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Build particles tab
    std::shared_ptr<IXUIElement> SettingsMainView::BuildParticlesTab()
    {
        auto l_Config = GTConfig::Instance();

        return XUIVLayout::Make({
            XUIText::Make(u"Remove all debris spawn")->AsShared(),
            XUIToggle::Make()->SetValue(l_Config->RemoveDebris)->Bind(&m_ParticlesTab_RemoveDebris)->OnValueChanged([this](bool) { OnSettingChanged(); })->AsShared(),

            XUIHLayout::Make({
                XUIVLayout::Make({
                    XUIText::Make(u"Remove world particles")->AsShared(),
                    XUIToggle::Make()->SetValue(l_Config->RemoveWorldParticles)->Bind(&m_ParticlesTab_RemoveWorldParticles)->AsShared(),
                    XUIText::Make(u"Remove floor burn particles")->AsShared(),
                    XUIToggle::Make()->SetValue(l_Config->RemoveSaberBurnMarkSparkles)->Bind(&m_ParticlesTab_RemoveFloorBurnMarkParticles)->AsShared()
                })
                ->SetPadding(0)
                ->SetWidth(40.0f)
                ->ForEachDirect<XUIToggle>([this](XUIToggle* x) { x->OnValueChanged([this](bool) { OnSettingChanged(); }); })
                ->AsShared(),

                XUIVLayout::Make({
                    XUIText::Make(u"Remove cut particles")->AsShared(),
                    XUIToggle::Make()->SetValue(l_Config->RemoveAllCutParticles)->Bind(&m_ParticlesTab_RemoveCutParticles)->AsShared(),
                    XUIText::Make(u"Remove floor burn marks")->AsShared(),
                    XUIToggle::Make()->SetValue(l_Config->RemoveSaberBurnMarks)->Bind(&m_ParticlesTab_RemoveFloorBurnMarkEffects)->AsShared()
                })
                ->SetPadding(0)
                ->SetWidth(40.0f)
                ->ForEachDirect<XUIToggle>([this](XUIToggle* x) { x->OnValueChanged([this](bool) { OnSettingChanged(); }); })
                ->AsShared(),

                XUIVLayout::Make({
                    XUIText::Make(u"Remove obstacle particles")->AsShared(),
                    XUIToggle::Make()->SetValue(l_Config->RemoveObstacleParticles)->Bind(&m_ParticlesTab_RemoveObstacleParticles)->AsShared(),
                    XUIText::Make(u"Remove saber clash effect")->AsShared(),
                    XUIToggle::Make()->SetValue(l_Config->RemoveSaberClashEffects)->Bind(&m_ParticlesTab_RemoveSaberClashEffects)->AsShared()
                })
                ->SetPadding(0)
                ->SetWidth(40.0f)
                ->ForEachDirect<XUIToggle>([this](XUIToggle* x) { x->OnValueChanged([this](bool) { OnSettingChanged(); }); })
                ->AsShared()
            })
            ->SetPadding(0)
            ->AsShared()
        })->AsShared();
    }
    /// @brief Build environment tab
    std::shared_ptr<IXUIElement> SettingsMainView::BuildEnvironmentTab()
    {
        auto& l_Config = GTConfig::Instance()->Environment;
        return XUIVLayout::Make({
            XUIText::Make(u"Remove music group logos (BTS, LinkinPark...) in environments")->AsShared(),
            XUIToggle::Make()->SetValue(l_Config->RemoveMusicBandLogo)->Bind(&m_EnvironmentTab_RemoveMusicBandLogo)->AsShared(),

            XUIText::Make(u"Remove full combo loss animation")->AsShared(),
            XUIToggle::Make()->SetValue(l_Config->RemoveFullComboLossAnimation)->Bind(&m_EnvironmentTab_RemoveFullComboLossAnimation)->AsShared()
        })
        ->ForEachDirect<XUIToggle>([this](XUIToggle* x) -> void {
            x->OnValueChanged([this](bool) -> void { OnSettingChanged(); });
        })
        ->AsShared();
    }
    /// @brief Build level selection tab
    std::shared_ptr<IXUIElement> SettingsMainView::BuildLevelSelectionTab()
    {
        auto& l_Config = GTConfig::Instance()->LevelSelection;

        return XUIVLayout::Make({
            XUIHLayout::Make({
                XUIVLayout::Make({
                    XUIText::Make(u"Played color")->AsShared(),
                    XUIColorInput::Make()->SetValue(ColorU::Convert(l_Config->HighlightPlayed))->Bind(&m_LevelSelectionTab_HighlightPlayedSongColor)->AsShared()
                })
                ->SetPadding(0)
                ->SetWidth(40.0f)
                ->ForEachDirect<XUIColorInput>([this](XUIColorInput* x) { x->OnValueChanged([this](Color) { OnSettingChanged(); }); })
                ->AsShared(),

                XUIVLayout::Make({
                    XUIText::Make(u"Highlight played song")->AsShared(),
                    XUIToggle::Make()->SetValue(l_Config->HighlightEnabled)->Bind(&m_LevelSelectionTab_HighlightPlayedSong)->AsShared()
                })
                ->SetPadding(0)
                ->SetWidth(40.0f)
                ->ForEachDirect<XUIToggle>([this](XUIToggle* x) { x->OnValueChanged([this](bool) { OnSettingChanged(); }); })
                ->AsShared(),

                XUIVLayout::Make({
                    XUIText::Make(u"All played color")->AsShared(),
                    XUIColorInput::Make()->SetValue(ColorU::Convert(l_Config->HighlightAllPlayed))->Bind(&m_LevelSelectionTab_HighlightPlayedSongAllColor)->AsShared()
                })
                ->SetPadding(0)
                ->SetWidth(40.0f)
                ->ForEachDirect<XUIColorInput>([this](XUIColorInput* x) { x->OnValueChanged([this](Color) { OnSettingChanged(); }); })
                ->AsShared()
            })
            ->SetPadding(0)
            ->AsShared(),

            XUIText::Make(u"Remove base game filter")->AsShared(),
            XUIToggle::Make()->SetValue(l_Config->RemoveBaseGameFilterButton)->Bind(&m_LevelSelectionTab_RemoveBaseGameFilterButton)->AsShared()
        })
        ->ForEachDirect<XUIToggle>([this](XUIToggle* x) { x->OnValueChanged([this](bool) { OnSettingChanged(); }); })
        ->ForEachDirect<XUIColorInput>([this](XUIColorInput* x) { x->OnValueChanged([this](Color) { OnSettingChanged(); }); })
        ->AsShared();
    }
    /// @brief Build player options tab
    std::shared_ptr<IXUIElement> SettingsMainView::BuildPlayerOptionsTab()
    {
        auto& l_Config = GTConfig::Instance()->PlayerOptions;
        return XUIVLayout::Make({
            XUIText::Make(u"Better player options menu")->AsShared(),
            XUIToggle::Make()->SetValue(l_Config->ReorderPlayerSettings)->Bind(&m_PlayerOptionsTab_ReorderPlayerSettings)->AsShared(),

            XUIText::Make(u"Add override lights intensity option")->AsShared(),
            XUIToggle::Make()->SetValue(l_Config->OverrideLightIntensityOption)->Bind(&m_PlayerOptionsTab_AddOverrideLightIntensityOption)->AsShared(),

            XUIText::Make(u"Merge light effect filter options")->AsShared(),
            XUIToggle::Make()->SetValue(l_Config->MergeLightPressetOptions)->Bind(&m_PlayerOptionsTab_MergeLightEffectFilterOptions)->AsShared()

        })
        ->ForEachDirect<XUIToggle>([this](XUIToggle* x) -> void {
            x->OnValueChanged([this](bool) -> void { OnSettingChanged(); });
        })
        ->AsShared();
    }
    /// @brief Build main menu tab
    std::shared_ptr<IXUIElement> SettingsMainView::BuildMainMenuTab()
    {
        auto& l_Config = GTConfig::Instance()->MainMenu;

        return XUIVLayout::Make({
            XUIText::Make(u"Override menu environment colors")->AsShared(),
            XUIToggle::Make()->SetValue(l_Config->OverrideMenuEnvColors)->Bind(&m_MainMenuTab_OverrideMenuEnvColors)->OnValueChanged([this](bool) { OnSettingChangedOverrideMenuColor(); })->AsShared(),

            XUIHLayout::Make({
                XUIVLayout::Make({
                    XUIText::Make(u"Base color")->AsShared(),
                    XUIColorInput::Make()->SetValue(l_Config->BaseColor)->Bind(&m_MainMenuTab_BaseColor)->AsShared(),

                    XUIText::Make(u"Remove new content promo")->SetAlign(TMPro::TextAlignmentOptions::CenterGeoAligned)->AsShared(),
                    XUIToggle::Make()->SetValue(l_Config->RemoveNewContentPromotional)->Bind(&m_MainMenuTab_RemoveNewContentPromotional)->OnValueChanged([this](bool) { OnSettingChanged(); })->AsShared()
                })
                ->SetPadding(0)
                ->SetWidth(40.0f)
                ->ForEachDirect<XUIColorInput>([this](XUIColorInput* x) { x->OnValueChanged([this](Color) { OnSettingChangedOverrideMenuColor(); }); })
                ->AsShared(),

                XUIVLayout::Make({
                    XUIText::Make(u"Level cleared color")->AsShared(),
                    XUIColorInput::Make()->SetValue(l_Config->LevelClearedColor)->Bind(&m_MainMenuTab_LevelClearedColor)->AsShared(),

                    XUIText::Make(u" ")->AsShared(),
                    XUIText::Make(u" ")->AsShared()
                })
                ->SetPadding(0)
                ->SetWidth(40.0f)
                ->ForEachDirect<XUIColorInput>([this](XUIColorInput* x) { x->OnValueChanged([this](Color) { OnSettingChangedLevelClearedColor(); }); })
                ->AsShared(),

                XUIVLayout::Make({
                    XUIText::Make(u"Level failed color")->AsShared(),
                    XUIColorInput::Make()->SetValue(l_Config->LevelFailedColor)->Bind(&m_MainMenuTab_LevelFailedColor)->AsShared(),

                    XUIText::Make(u"Disable fireworks")->AsShared(),
                    XUIToggle::Make()->SetValue(l_Config->DisableFireworks)->Bind(&m_MainMenuTab_DisableFireworks)->OnValueChanged([this](bool) { OnSettingChanged(); })->AsShared()
                })
                ->SetPadding(0)
                ->SetWidth(40.0f)
                ->ForEachDirect<XUIColorInput>([this](XUIColorInput* x) { x->OnValueChanged([this](Color)  { OnSettingChangedLevelFailedColor(); }); })
                ->AsShared()
            })
            ->SetPadding(0)
            ->AsShared()
        })->AsShared();
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief When settings are changed
    void SettingsMainView::OnSettingChanged()
    {
        if (m_PreventChanges)
            return;

        #pragma region Particles_tab
        auto l_ParticlesConfig = GTConfig::Instance();
        l_ParticlesConfig->RemoveDebris                     = m_ParticlesTab_RemoveDebris->Element()->GetValue();
        l_ParticlesConfig->RemoveAllCutParticles            = m_ParticlesTab_RemoveCutParticles->Element()->GetValue();
        l_ParticlesConfig->RemoveObstacleParticles          = m_ParticlesTab_RemoveObstacleParticles->Element()->GetValue();
        l_ParticlesConfig->RemoveSaberBurnMarkSparkles      = m_ParticlesTab_RemoveFloorBurnMarkParticles->Element()->GetValue();
        l_ParticlesConfig->RemoveSaberBurnMarks             = m_ParticlesTab_RemoveFloorBurnMarkEffects->Element()->GetValue();
        l_ParticlesConfig->RemoveSaberClashEffects          = m_ParticlesTab_RemoveSaberClashEffects->Element()->GetValue();
        l_ParticlesConfig->RemoveWorldParticles             = m_ParticlesTab_RemoveWorldParticles->Element()->GetValue();
        #pragma endregion Particles_tab

        #pragma region Environment_Tab
        auto& l_EnvironmentConfig = GTConfig::Instance()->Environment;
        l_EnvironmentConfig->RemoveMusicBandLogo           = m_EnvironmentTab_RemoveMusicBandLogo->Element()->GetValue();
        l_EnvironmentConfig->RemoveFullComboLossAnimation  = m_EnvironmentTab_RemoveFullComboLossAnimation->Element()->GetValue();
        #pragma endregion Environment_Tab

        #pragma region LevelSelection_Tab
        auto& l_LevelSelectionConfig = GTConfig::Instance()->LevelSelection;
        l_LevelSelectionConfig->RemoveBaseGameFilterButton = m_LevelSelectionTab_RemoveBaseGameFilterButton->Element()->GetValue();
        l_LevelSelectionConfig->HighlightEnabled           = m_LevelSelectionTab_HighlightPlayedSong->Element()->GetValue();
        l_LevelSelectionConfig->HighlightPlayed            = ColorU::Convert(m_LevelSelectionTab_HighlightPlayedSongColor->Element()->GetValue());
        l_LevelSelectionConfig->HighlightAllPlayed         = ColorU::Convert(m_LevelSelectionTab_HighlightPlayedSongAllColor->Element()->GetValue());
        #pragma endregion LevelSelection_Tab

        #pragma region PlayerOptions_Tab
        auto& l_PlayerOptionConfig = GTConfig::Instance()->PlayerOptions;
        l_PlayerOptionConfig->ReorderPlayerSettings        = m_PlayerOptionsTab_ReorderPlayerSettings->Element()->GetValue();
        l_PlayerOptionConfig->OverrideLightIntensityOption = m_PlayerOptionsTab_AddOverrideLightIntensityOption->Element()->GetValue();
        l_PlayerOptionConfig->MergeLightPressetOptions     = m_PlayerOptionsTab_MergeLightEffectFilterOptions->Element()->GetValue();
        #pragma endregion PlayerOptions_Tab

        #pragma region MainMenu_Tab
        auto& l_MainMenuConfig = GTConfig::Instance()->MainMenu;
        l_MainMenuConfig->OverrideMenuEnvColors            = m_MainMenuTab_OverrideMenuEnvColors->Element()->GetValue();
        l_MainMenuConfig->BaseColor                        = m_MainMenuTab_BaseColor->Element()->GetValue();
        l_MainMenuConfig->LevelClearedColor                = m_MainMenuTab_LevelClearedColor->Element()->GetValue();
        l_MainMenuConfig->LevelFailedColor                 = m_MainMenuTab_LevelFailedColor->Element()->GetValue();
        l_MainMenuConfig->RemoveNewContentPromotional      = m_MainMenuTab_RemoveNewContentPromotional->Element()->GetValue();
        l_MainMenuConfig->DisableFireworks                 = m_MainMenuTab_DisableFireworks->Element()->GetValue();

        m_MainMenuTab_BaseColor         ->SetInteractable(l_MainMenuConfig->OverrideMenuEnvColors);
        m_MainMenuTab_LevelClearedColor ->SetInteractable(l_MainMenuConfig->OverrideMenuEnvColors);
        m_MainMenuTab_LevelFailedColor  ->SetInteractable(l_MainMenuConfig->OverrideMenuEnvColors);
        #pragma endregion MainMenu_Tab

        /// Update patches
        GameTweaker::Instance()->UpdatePatches(false);
    }
    /// @brief When settings are changed
    void SettingsMainView::OnSettingChangedOverrideMenuColor()
    {
        OnSettingChanged();
        Managers::CustomMenuLightManager::UpdateFromConfig();
        Managers::CustomMenuLightManager::SwitchToBase();
    }
    /// @brief When settings are changed
    void SettingsMainView::OnSettingChangedLevelClearedColor()
    {
        OnSettingChanged();
        Managers::CustomMenuLightManager::UpdateFromConfig();
        Managers::CustomMenuLightManager::SwitchToLevelCleared();
    }
    /// @brief When settings are changed
    void SettingsMainView::OnSettingChangedLevelFailedColor()
    {
        OnSettingChanged();
        Managers::CustomMenuLightManager::UpdateFromConfig();
        Managers::CustomMenuLightManager::SwitchToLevelFailed();
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// Reset settings
    void SettingsMainView::RefreshSettings()
    {
        m_PreventChanges = true;

        auto l_Config = GTConfig::Instance();
        #pragma region Particles_tab
        m_ParticlesTab_RemoveDebris                 ->SetValue(l_Config->RemoveDebris);
        m_ParticlesTab_RemoveCutParticles           ->SetValue(l_Config->RemoveAllCutParticles);
        m_ParticlesTab_RemoveObstacleParticles      ->SetValue(l_Config->RemoveObstacleParticles);
        m_ParticlesTab_RemoveFloorBurnMarkParticles ->SetValue(l_Config->RemoveSaberBurnMarkSparkles);
        m_ParticlesTab_RemoveFloorBurnMarkEffects   ->SetValue(l_Config->RemoveSaberBurnMarks);
        m_ParticlesTab_RemoveSaberClashEffects      ->SetValue(l_Config->RemoveSaberClashEffects);
        m_ParticlesTab_RemoveWorldParticles         ->SetValue(l_Config->RemoveWorldParticles);
        #pragma endregion Particles_tab

        #pragma region Environment_Tab
        m_EnvironmentTab_RemoveMusicBandLogo            ->SetValue(l_Config->Environment->RemoveMusicBandLogo);
        m_EnvironmentTab_RemoveFullComboLossAnimation   ->SetValue(l_Config->Environment->RemoveFullComboLossAnimation);
        #pragma endregion Environment_Tab

        #pragma region LevelSelection_Tab
        m_LevelSelectionTab_RemoveBaseGameFilterButton  ->SetValue(l_Config->LevelSelection->RemoveBaseGameFilterButton);
        m_LevelSelectionTab_HighlightPlayedSong         ->SetValue(l_Config->LevelSelection->HighlightEnabled);
        m_LevelSelectionTab_HighlightPlayedSongColor    ->SetValue(ColorU::Convert(l_Config->LevelSelection->HighlightPlayed));
        m_LevelSelectionTab_HighlightPlayedSongAllColor ->SetValue(ColorU::Convert(l_Config->LevelSelection->HighlightAllPlayed));
        #pragma endregion LevelSelection_Tab

        #pragma region PlayerOptions_Tab
        m_PlayerOptionsTab_ReorderPlayerSettings            ->SetValue(l_Config->PlayerOptions->ReorderPlayerSettings);
        m_PlayerOptionsTab_AddOverrideLightIntensityOption  ->SetValue(l_Config->PlayerOptions->OverrideLightIntensityOption);
        m_PlayerOptionsTab_MergeLightEffectFilterOptions    ->SetValue(l_Config->PlayerOptions->MergeLightPressetOptions);
        #pragma endregion PlayerOptions_Tab

        #pragma region MainMenu_Tab
        m_MainMenuTab_OverrideMenuEnvColors         ->SetValue(l_Config->MainMenu->OverrideMenuEnvColors);
        m_MainMenuTab_BaseColor                     ->SetValue(l_Config->MainMenu->BaseColor);
        m_MainMenuTab_LevelClearedColor             ->SetValue(l_Config->MainMenu->LevelClearedColor);
        m_MainMenuTab_LevelFailedColor              ->SetValue(l_Config->MainMenu->LevelFailedColor);
        m_MainMenuTab_RemoveNewContentPromotional   ->SetValue(l_Config->MainMenu->RemoveNewContentPromotional);
        m_MainMenuTab_DisableFireworks              ->SetValue(l_Config->MainMenu->DisableFireworks);
        #pragma endregion MainMenu_Tab

        m_PreventChanges = false;

        /// Refresh UI
        OnSettingChanged();
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::UI