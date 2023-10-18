#include "Patches/PPlayerSettingsPanelController.hpp"
#include "GTConfig.hpp"
#include "Logger.hpp"

#include <CP_SDK/UI/UISystem.hpp>
#include <CP_SDK/UI/ValueFormatters.hpp>
#include <CP_SDK/Unity/Extensions/ColorU.hpp>
#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/EnvironmentEffectsFilterPresetDropdown.hpp>
#include <GlobalNamespace/FormattedFloatListSettingsController.hpp>
#include <GlobalNamespace/PlayerHeightSettingsController.hpp>
#include <GlobalNamespace/PlayerSettingsPanelController.hpp>
#include <GlobalNamespace/PlayerSettingsPanelController_PlayerSettingsPanelLayout.hpp>
#include <GlobalNamespace/NoteJumpDurationTypeSettingsDropdown.hpp>
#include <GlobalNamespace/NoteJumpStartBeatOffsetDropdown.hpp>
#include <Polyglot/LocalizedTextMeshProUGUI.hpp>
#include <System/Action_2.hpp>
#include <TMPro/TextMeshProUGUI.hpp>
#include <UnityEngine/GameObject.hpp>
#include <UnityEngine/Transform.hpp>
#include <UnityEngine/UI/Toggle.hpp>

using namespace CP_SDK::Unity::Extensions;
using namespace GlobalNamespace;
using namespace Polyglot;
using namespace TMPro;
using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static CP_SDK::Utils::MonoPtr<Toggle>                                 PMainMenuViewController_LeftHandedToggle;
    static CP_SDK::Utils::MonoPtr<EnvironmentEffectsFilterPresetDropdown> PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown;
    static CP_SDK::Utils::MonoPtr<EnvironmentEffectsFilterPresetDropdown> PMainMenuViewController_EnvironmentEffectsFilterExpertPlusPresetDropdown;
    static CP_SDK::Utils::MonoPtr<Toggle>                                 PMainMenuViewController_ReduceDebrisToggle;
    static CP_SDK::Utils::MonoPtr<Toggle>                                 PMainMenuViewController_NoTextsAndHudsToggle;
    static CP_SDK::Utils::MonoPtr<Toggle>                                 PMainMenuViewController_AdvanceHudToggle;
    static CP_SDK::Utils::MonoPtr<PlayerHeightSettingsController>         PMainMenuViewController_PlayerHeightSettingsController;
    static CP_SDK::Utils::MonoPtr<Toggle>                                 PMainMenuViewController_AutomaticPlayerHeightToggle;
    static CP_SDK::Utils::MonoPtr<FormattedFloatListSettingsController>   PMainMenuViewController_SfxVolumeSettingsController;
    static CP_SDK::Utils::MonoPtr<FormattedFloatListSettingsController>   PMainMenuViewController_SaberTrailIntensitySettingsController;
    static CP_SDK::Utils::MonoPtr<Toggle>                                 PMainMenuViewController_HideNoteSpawnEffectToggle;
    static CP_SDK::Utils::MonoPtr<Toggle>                                 PMainMenuViewController_AdaptiveSfxToggle;
    static CP_SDK::Utils::MonoPtr<NoteJumpDurationTypeSettingsDropdown>   PMainMenuViewController_NoteJumpDurationTypeSettingsDropdown;
    static CP_SDK::Utils::MonoPtr<FormattedFloatListSettingsController>   PMainMenuViewController_NoteJumpFixedDurationSettingsController;
    static CP_SDK::Utils::MonoPtr<NoteJumpStartBeatOffsetDropdown>        PMainMenuViewController_NoteJumpStartBeatOffsetDropdown;

    static CP_SDK::Utils::MonoPtr<GameObject>                             PMainMenuViewController_OverrideLightsIntensitySetting;

    static CP_SDK::Utils::MonoPtr<CP_SDK::UI::Components::CSlider>        PMainMenuViewController_CustomReactionTime;

    using t_didSelectCellWithIdxEventDelegate = System::Action_2<int, EnvironmentEffectsFilterPreset>;
    static CP_SDK::Utils::MonoPtr<t_didSelectCellWithIdxEventDelegate>    PMainMenuViewController_EnvironmentEffectsDelegate;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief On light preset change, replicate to the hidden one
    /// @param p_CellIndex
    static void OnLightSettingChanged(int p_CellIndex, EnvironmentEffectsFilterPreset p_Setting)
    {
        if (!PMainMenuViewController_EnvironmentEffectsFilterExpertPlusPresetDropdown)
            return;

        PMainMenuViewController_EnvironmentEffectsFilterExpertPlusPresetDropdown->SelectCellWithValue(p_Setting);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set if the effect is enabled
    /// @param p_Enabled New state
    void PPlayerSettingsPanelController::SetReorderEnabled(bool p_Enabled, bool p_AddOverrideLightsIntensityOption)
    {
        if (!PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown || !PMainMenuViewController_NoteJumpStartBeatOffsetDropdown || !PMainMenuViewController_SfxVolumeSettingsController)
            return;

        PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown->get_transform()->get_parent()->get_parent()->GetComponent<VerticalLayoutGroup*>()->set_enabled(true);

        if (p_AddOverrideLightsIntensityOption && !PMainMenuViewController_OverrideLightsIntensitySetting)
        {
            PMainMenuViewController_OverrideLightsIntensitySetting = GameObject::Instantiate(
                PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown->get_transform()->get_parent()->get_gameObject(),
                PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown->get_transform()->get_parent()->get_parent()
            );

            GameObject::DestroyImmediate(PMainMenuViewController_OverrideLightsIntensitySetting->get_transform()->Find("SimpleTextDropDown")->get_gameObject());

            PMainMenuViewController_OverrideLightsIntensitySetting->GetComponentInChildren<LocalizedTextMeshProUGUI*>()->set_enabled(false);
            PMainMenuViewController_OverrideLightsIntensitySetting->GetComponentInChildren<TextMeshProUGUI*>()->set_text("Override lights intensity");

            auto l_Slider = CP_SDK::UI::UISystem::SliderFactory->Create(u"", PMainMenuViewController_OverrideLightsIntensitySetting->get_transform());
            l_Slider->RTransform()->set_anchorMin(Vector2(0.5f, 0.5f));
            l_Slider->RTransform()->set_anchorMax(Vector2(1.0f, 0.5f));
            l_Slider->RTransform()->set_sizeDelta(Vector2(0.0f, 5.0f));
            l_Slider->SetColor(ColorU::ToUnityColor("#404040"));
            l_Slider->SetMinValue(0.0f);
            l_Slider->SetMaxValue(10.0f);
            l_Slider->SetIncrements(0.01f);
            l_Slider->SetFormatter(CP_SDK::UI::ValueFormatters::Percentage);
            l_Slider->SetValue(GTConfig::Instance()->PlayerOptions->OverrideLightIntensity);
            l_Slider->OnValueChanged([](float x) -> void
            {
                GTConfig::Instance()->PlayerOptions->OverrideLightIntensity = (float)x;
                GTConfig::Instance()->Save();
            });
        }
        else if (!p_AddOverrideLightsIntensityOption && PMainMenuViewController_OverrideLightsIntensitySetting)
        {
            GameObject::DestroyImmediate(PMainMenuViewController_OverrideLightsIntensitySetting.Ptr());
            PMainMenuViewController_OverrideLightsIntensitySetting = nullptr;
        }

        if (p_Enabled)
        {
            PMainMenuViewController_SaberTrailIntensitySettingsController->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_HideNoteSpawnEffectToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_ReduceDebrisToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_AdaptiveSfxToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_SfxVolumeSettingsController->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_LeftHandedToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_AutomaticPlayerHeightToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_EnvironmentEffectsFilterExpertPlusPresetDropdown->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown->get_transform()->get_parent()->SetAsFirstSibling();
            if (PMainMenuViewController_OverrideLightsIntensitySetting) PMainMenuViewController_OverrideLightsIntensitySetting->get_transform()->SetAsFirstSibling();
            PMainMenuViewController_AdvanceHudToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_NoTextsAndHudsToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_NoteJumpFixedDurationSettingsController->get_transform()->SetAsFirstSibling();
            PMainMenuViewController_NoteJumpStartBeatOffsetDropdown->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_NoteJumpDurationTypeSettingsDropdown->get_transform()->SetAsFirstSibling();
            PMainMenuViewController_PlayerHeightSettingsController->get_transform()->SetAsFirstSibling();
        }
        else
        {
            PMainMenuViewController_HideNoteSpawnEffectToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_ReduceDebrisToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_AdvanceHudToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_NoTextsAndHudsToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_SaberTrailIntensitySettingsController->get_transform()->get_parent()->SetAsFirstSibling();
            if (PMainMenuViewController_OverrideLightsIntensitySetting) PMainMenuViewController_OverrideLightsIntensitySetting->get_transform()->SetAsFirstSibling();
            PMainMenuViewController_EnvironmentEffectsFilterExpertPlusPresetDropdown->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown->get_transform()->get_parent()->SetAsFirstSibling();

            PMainMenuViewController_NoteJumpFixedDurationSettingsController->get_transform()->SetAsFirstSibling();
            PMainMenuViewController_NoteJumpStartBeatOffsetDropdown->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_NoteJumpDurationTypeSettingsDropdown->get_transform()->SetAsFirstSibling();

            PMainMenuViewController_AdaptiveSfxToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_SfxVolumeSettingsController->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_LeftHandedToggle->get_transform()->get_parent()->SetAsFirstSibling();
            PMainMenuViewController_PlayerHeightSettingsController->get_transform()->SetAsFirstSibling();
            PMainMenuViewController_AutomaticPlayerHeightToggle->get_transform()->get_parent()->SetAsFirstSibling();
        }
    }
    /// @brief Should merge the two lights options
    /// @param p_Enabled New state
    void PPlayerSettingsPanelController::SetLightsOptionMerging(bool p_Enabled)
    {
        if (!PMainMenuViewController_EnvironmentEffectsDelegate)
            PMainMenuViewController_EnvironmentEffectsDelegate = custom_types::MakeDelegate<t_didSelectCellWithIdxEventDelegate*>(std::function(&OnLightSettingChanged));

        if (PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown)
        {
            PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown->remove_didSelectCellWithIdxEvent(PMainMenuViewController_EnvironmentEffectsDelegate.Ptr());

            if (p_Enabled)
                PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown->add_didSelectCellWithIdxEvent(PMainMenuViewController_EnvironmentEffectsDelegate.Ptr());
        }

        if (PMainMenuViewController_EnvironmentEffectsFilterExpertPlusPresetDropdown)
            PMainMenuViewController_EnvironmentEffectsFilterExpertPlusPresetDropdown->get_transform()->get_parent()->get_gameObject()->SetActive(!p_Enabled);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        PlayerSettingsPanelController_SetLayout, &PlayerSettingsPanelController::SetLayout,
        void, PlayerSettingsPanelController* __Instance,

        PlayerSettingsPanelController::PlayerSettingsPanelLayout __a)
    {
        PMainMenuViewController_LeftHandedToggle                                  = __Instance->leftHandedToggle;
        PMainMenuViewController_EnvironmentEffectsFilterDefaultPresetDropdown     = __Instance->environmentEffectsFilterDefaultPresetDropdown;
        PMainMenuViewController_EnvironmentEffectsFilterExpertPlusPresetDropdown  = __Instance->environmentEffectsFilterExpertPlusPresetDropdown;
        PMainMenuViewController_ReduceDebrisToggle                                = __Instance->reduceDebrisToggle;
        PMainMenuViewController_NoTextsAndHudsToggle                              = __Instance->noTextsAndHudsToggle;
        PMainMenuViewController_AdvanceHudToggle                                  = __Instance->advanceHudToggle;
        PMainMenuViewController_PlayerHeightSettingsController                    = __Instance->playerHeightSettingsController;
        PMainMenuViewController_AutomaticPlayerHeightToggle                       = __Instance->automaticPlayerHeightToggle;
        PMainMenuViewController_SfxVolumeSettingsController                       = __Instance->sfxVolumeSettingsController;
        PMainMenuViewController_SaberTrailIntensitySettingsController             = __Instance->saberTrailIntensitySettingsController;
        PMainMenuViewController_NoteJumpStartBeatOffsetDropdown                   = __Instance->noteJumpStartBeatOffsetDropdown;
        PMainMenuViewController_HideNoteSpawnEffectToggle                         = __Instance->hideNoteSpawnEffectToggle;
        PMainMenuViewController_AdaptiveSfxToggle                                 = __Instance->adaptiveSfxToggle;
        PMainMenuViewController_NoteJumpDurationTypeSettingsDropdown              = __Instance->noteJumpDurationTypeSettingsDropdown;
        PMainMenuViewController_NoteJumpFixedDurationSettingsController           = __Instance->noteJumpFixedDurationSettingsController;

        auto l_Config = GTConfig::Instance();

        try
        {
            if (!PMainMenuViewController_CustomReactionTime)
            {
                auto l_NewReactionTimeList = System::Collections::Generic::List_1<float>::New_ctor();
                for (float l_Value = 0.200f; l_Value <= 1.000f; l_Value += 0.001f)
                    l_NewReactionTimeList->Add(l_Value);

                if (PMainMenuViewController_NoteJumpFixedDurationSettingsController)
                {
                    PMainMenuViewController_NoteJumpFixedDurationSettingsController->set_values(l_NewReactionTimeList->ToArray());
                    int __ia, __ib;
                    PMainMenuViewController_NoteJumpFixedDurationSettingsController->GetInitValues(__ia, __ib);
                    PMainMenuViewController_NoteJumpFixedDurationSettingsController->get_transform()->GetChild(2)->get_transform()->set_localScale(Vector3::get_zero());

                    PMainMenuViewController_CustomReactionTime = CP_SDK::UI::UISystem::SliderFactory->Create(u"", PMainMenuViewController_NoteJumpFixedDurationSettingsController->get_transform());
                    PMainMenuViewController_CustomReactionTime->RTransform()->set_anchorMin(Vector2(0.5f, 0.5f));
                    PMainMenuViewController_CustomReactionTime->RTransform()->set_anchorMax(Vector2(1.0f, 0.5f));
                    PMainMenuViewController_CustomReactionTime->RTransform()->set_sizeDelta(Vector2(0.0f, 5.0f));
                    PMainMenuViewController_CustomReactionTime->SetColor(ColorU::ToUnityColor("#404040"));
                    PMainMenuViewController_CustomReactionTime->SetMinValue(200);
                    PMainMenuViewController_CustomReactionTime->SetMaxValue(1000.0f);
                    PMainMenuViewController_CustomReactionTime->SetIncrements(1.0f);
                    PMainMenuViewController_CustomReactionTime->SetInteger(true);
                    PMainMenuViewController_CustomReactionTime->SetFormatter(CP_SDK::UI::ValueFormatters::MillisecondsShort);
                    PMainMenuViewController_CustomReactionTime->OnValueChanged([](float x) -> void
                    {
                        PMainMenuViewController_NoteJumpFixedDurationSettingsController->SetValue(PMainMenuViewController_NoteJumpFixedDurationSettingsController->get_values()[((int)x) - 200], true);
                    });
                    PMainMenuViewController_CustomReactionTime->SetValue((int)(PMainMenuViewController_NoteJumpFixedDurationSettingsController->get_value() * 1000.0f), false);
                }
            }
        }
        catch (const std::exception& l_Exception)
        {
            Logger::Instance->Error(u"[Patches][PPlayerSettingsPanelController] Error:");
            Logger::Instance->Error(l_Exception);
        }

        try
        {
            /// Apply
            if (l_Config->Enabled)
                PPlayerSettingsPanelController::SetReorderEnabled(l_Config->PlayerOptions->ReorderPlayerSettings, l_Config->PlayerOptions->OverrideLightIntensityOption);

            if (l_Config->Enabled)
                PPlayerSettingsPanelController::SetLightsOptionMerging(l_Config->PlayerOptions->MergeLightPressetOptions);
        }
        catch (const std::exception& l_Exception)
        {
            Logger::Instance->Error(u"[Patches][PPlayerSettingsPanelController] Error:");
            Logger::Instance->Error(l_Exception);
        }

        PlayerSettingsPanelController_SetLayout(__Instance, __a);
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches