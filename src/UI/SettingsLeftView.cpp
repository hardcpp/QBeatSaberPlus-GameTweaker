#include "UI/SettingsLeftView.hpp"
#include "UI/SettingsMainView.hpp"
#include "GameTweaker.hpp"

#include <UnityEngine/Application.hpp>

using namespace CP_SDK::XUI;
using namespace UnityEngine;

namespace QBeatSaberPlus_GameTweaker::UI {

    constexpr const std::u16string_view s_InformationStr =
               u"<line-height=125%><b>Game Tweaker</b>"
         u"\n" u"<i><color=#CCCCCCFF>This module allow you to customize your game experience, remove some boring base game features, and add new cool features/tweaks</color></i>";

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_INHERIT_INIT(SettingsLeftView);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Constructor
    CP_SDK_IL2CPP_DECLARE_CTOR_IMPL(SettingsLeftView)
    {
        OnViewCreation = {this, &SettingsLeftView::OnViewCreation_Impl};
    }
    /// @brief Destructor
    CP_SDK_IL2CPP_DECLARE_DTOR_MONOBEHAVIOUR_IMPL(SettingsLeftView)
    {

    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief On view creation
    void SettingsLeftView::OnViewCreation_Impl()
    {
        Templates::FullRectLayout({
            Templates::TitleBar(u"Information / Credits"),

            Templates::ScrollableInfos(50.0f, {
                XUIText::Make(s_InformationStr)
                    ->SetAlign(TMPro::TextAlignmentOptions::Left)
                    ->AsShared()
            }),

            Templates::ExpandedButtonsLine({
                XUIPrimaryButton::Make(u"Reset", {this, &SettingsLeftView::OnResetButton})->AsShared(),
            }),
            Templates::ExpandedButtonsLine({
                XUISecondaryButton::Make(u"Documentation", {this, &SettingsLeftView::OnDocumentationButton})->AsShared()
            })
        })
        ->SetBackground(true, std::nullopt, true)
        ->BuildUI(get_transform());
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Reset button
    void SettingsLeftView::OnResetButton()
    {
        ShowConfirmationModal(
            u"<color=yellow><b>Do you really want to reset\ngame tweaker configuration?",
            [this](bool p_Confirm) -> void
            {
                if (!p_Confirm)
                    return;

                GTConfig::Instance()->Reset();
                GTConfig::Instance()->Enabled = true;
                GTConfig::Instance()->Save();

                /// Refresh values
                SettingsMainView::Instance()->RefreshSettings();
            }
        );
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Documentation button
    void SettingsLeftView::OnDocumentationButton()
    {
        ShowMessageModal(u"URL opened in your web browser.");
        Application::OpenURL(GameTweaker::Instance()->DocumentationURL());
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::UI