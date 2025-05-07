#include "GameTweaker.hpp"
#include "Components/MusicBandLogoRemover.hpp"
#include "Managers/CustomMenuLightManager.hpp"
#include "Patches/Lights/PLightsPatches.hpp"
#include "Patches/PLevelSearchViewController.hpp"
#include "Patches/PMainMenuViewController.hpp"
#include "Patches/PMusicPackPromoBanner.hpp"
#include "Patches/PNoteCutCoreEffectsSpawner.hpp"
#include "Patches/PNoteDebrisSpawner.hpp"
#include "Patches/PObstacleSaberSparkleEffectManager.hpp"
#include "Patches/PPlayerSettingsPanelController.hpp"
#include "Patches/PSaberBurnMarkArea.hpp"
#include "Patches/PSaberBurnMarkSparkles.hpp"
#include "Patches/PSaberClashEffect.hpp"
#include "Logger.hpp"

#include <GlobalNamespace/EnvironmentInfoSO.hpp>
#include <UnityEngine/Resources.hpp>
#include <UnityEngine/GameObject.hpp>

using namespace UnityEngine;

namespace QBeatSaberPlus_GameTweaker {

    CP_SDK_MODULE_BASE_INSTANCE_IMPL(GameTweaker);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// Constructor
    GameTweaker::GameTweaker()
    {

    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Enable the Module
    void GameTweaker::OnEnable()
    {
        /// Bind event
        CP_SDK_BS::Game::Logic::OnSceneChange  += {this, &GameTweaker::Game_OnSceneChange};
        CP_SDK_BS::Game::Logic::OnLevelStarted += {this, &GameTweaker::Game_OnLevelStarted};

        Managers::CustomMenuLightManager::Init();

        /// Update patches
        UpdatePatches(false);
    }
    /// @brief Disable the Module
    void GameTweaker::OnDisable()
    {
        /// Update patches
        UpdatePatches(true);

        CP_SDK::UI::UISystem::DestroyUI(&m_SettingsLeftView);
        CP_SDK::UI::UISystem::DestroyUI(&m_SettingsMainView);

        /// Unbind event
        CP_SDK_BS::Game::Logic::OnSceneChange  -= {this, &GameTweaker::Game_OnSceneChange};
        CP_SDK_BS::Game::Logic::OnLevelStarted -= {this, &GameTweaker::Game_OnLevelStarted};
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Get Module settings UI
    GameTweaker::t_InitialViews GameTweaker::GetSettingsViewControllers()
    {
        if (!m_SettingsMainView) m_SettingsMainView = CP_SDK::UI::UISystem::CreateViewController<UI::SettingsMainView*>();
        if (!m_SettingsLeftView) m_SettingsLeftView = CP_SDK::UI::UISystem::CreateViewController<UI::SettingsLeftView*>();

        return { m_SettingsMainView.Ptr(), m_SettingsLeftView.Ptr(), nullptr};
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Update patches
    /// @param p_ForceDisable Force disable
    void GameTweaker::UpdatePatches(bool p_ForceDisable)
    {
        ////////////////////////////////////////////////////////////////////////////
        /// GamePlay
        ////////////////////////////////////////////////////////////////////////////

        /// Apply cut particles
        try {
            Patches::PNoteCutCoreEffectsSpawner::SetRemoveCutParticles(!p_ForceDisable && GTConfig::Instance()->RemoveAllCutParticles);
        } catch (const std::exception& p_PatchException) { Logger::Instance->Error(u"[GameTweaker] Error on updating PNoteCutCoreEffectsSpawner"); Logger::Instance->Error(p_PatchException); }
        /// Apply obstacle particles
        try {
            Patches::PObstacleSaberSparkleEffectManager::SetRemoveObstacleParticles(!p_ForceDisable && GTConfig::Instance()->RemoveObstacleParticles);
        } catch (const std::exception& p_PatchException) { Logger::Instance->Error(u"[GameTweaker] Error on updating PObstacleSaberSparkleEffectManager"); Logger::Instance->Error(p_PatchException); }
        /// Apply burn mark particles
        try {
            Patches::PSaberBurnMarkSparkles::SetRemoveSaberBurnMarkSparkles(!p_ForceDisable && GTConfig::Instance()->RemoveSaberBurnMarkSparkles);
        } catch (const std::exception& p_PatchException) { Logger::Instance->Error(u"[GameTweaker] Error on updating PSaberBurnMarkSparkles"); Logger::Instance->Error(p_PatchException); }
        /// Apply burn mark effect
        try {
            Patches::PSaberBurnMarkArea::SetRemoveSaberBurnMarks(!p_ForceDisable && GTConfig::Instance()->RemoveSaberBurnMarks);
        } catch (const std::exception& p_PatchException) { Logger::Instance->Error(u"[GameTweaker] Error on updating PSaberBurnMarkArea"); Logger::Instance->Error(p_PatchException); }
        /// Apply saber clash effects
        try {
            Patches::PSaberClashEffect::SetRemoveClashEffects(!p_ForceDisable && GTConfig::Instance()->RemoveSaberClashEffects);
        } catch (const std::exception& p_PatchException) { Logger::Instance->Error(u"[GameTweaker] Error on updating PSaberClashEffect"); Logger::Instance->Error(p_PatchException); }
        /// World particles
        try {
            UpdateWorldParticles(p_ForceDisable);
        } catch (const std::exception& p_PatchException) { Logger::Instance->Error(u"[GameTweaker] Error on updating UpdateWorldParticles"); Logger::Instance->Error(p_PatchException); }

        ////////////////////////////////////////////////////////////////////////////
        /// Menu
        ////////////////////////////////////////////////////////////////////////////

        /// Apply show player statistics in main menu
        try {
            Patches::PMainMenuViewController::SetRemovePackMusicPromoBanner(!p_ForceDisable && GTConfig::Instance()->MainMenu->RemoveNewContentPromotional);
        } catch (const std::exception& p_PatchException) { Logger::Instance->Error(u"[GameTweaker] Error on updating PMainMenuViewController"); Logger::Instance->Error(p_PatchException); }
        /// Apply new content promotional settings
        try {
            Patches::PMusicPackPromoBanner::SetEnabled(!p_ForceDisable && GTConfig::Instance()->MainMenu->RemoveNewContentPromotional);
        } catch (const std::exception& p_PatchException) { Logger::Instance->Error(u"[GameTweaker] Error on updating PPromoViewController"); Logger::Instance->Error(p_PatchException); }
        /// Apply player settings
        try {
            Patches::PPlayerSettingsPanelController::SetReorderEnabled(!p_ForceDisable && GTConfig::Instance()->PlayerOptions->ReorderPlayerSettings, !p_ForceDisable && GTConfig::Instance()->PlayerOptions->OverrideLightIntensityOption);
            Patches::PPlayerSettingsPanelController::SetLightsOptionMerging(!p_ForceDisable && GTConfig::Instance()->PlayerOptions->MergeLightPressetOptions);
        } catch (const std::exception& p_PatchException) { Logger::Instance->Error(u"[GameTweaker] Error on updating PlayerSettingsPanelController"); Logger::Instance->Error(p_PatchException); }
        /// Apply remove base game filter button settings
        try {
            Patches::PLevelSearchViewController::SetRemoveBaseGameFilter(!p_ForceDisable && GTConfig::Instance()->LevelSelection->RemoveBaseGameFilterButton);
        } catch (const std::exception& p_PatchException) { Logger::Instance->Error(u"[GameTweaker] Error on updating PLevelSearchViewController"); Logger::Instance->Error(p_PatchException); }
    }
    /// @brief Update world particles
    /// @param p_ForceDisable Force disable
    void GameTweaker::UpdateWorldParticles(bool p_ForceDisable)
    {
        auto l_Objects = Resources::FindObjectsOfTypeAll<GameObject*>();
        for (auto& l_Current : l_Objects)
        {
            if (l_Current->get_name() != "DustPS")
                continue;

            l_Current->SetActive(p_ForceDisable ? true : !GTConfig::Instance()->RemoveWorldParticles);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief On game scene change
    /// @param p_Scene New scene
    void GameTweaker::Game_OnSceneChange(CP_SDK_BS::Game::Logic::ESceneType p_Scene)
    {
        Patches::Lights::PLightsPatches::SetIsValidScene(p_Scene == CP_SDK_BS::Game::Logic::ESceneType::Playing);
        UpdateWorldParticles();
    }
    /// @brief On level started
    /// @param p_LevelData Level data
    void GameTweaker::Game_OnLevelStarted(const CP_SDK_BS::Game::LevelData::Ptr& p_LevelData)
    {
        Patches::Lights::PLightsPatches::SetFromConfig();
        Patches::PNoteDebrisSpawner::SetFromConfig();

        if (GTConfig::Instance()->Environment->RemoveMusicBandLogo && p_LevelData && p_LevelData->Data && p_LevelData->Data->targetEnvironmentInfo)
        {
            if (   p_LevelData->Data->targetEnvironmentInfo->____serializedName == "BTSEnvironment"
                || p_LevelData->Data->targetEnvironmentInfo->____serializedName == "LinkinParkEnvironment")
            {
                GameObject::New_ctor("BeatSaberPlus_MusicBandLogoRemover")->AddComponent<Components::MusicBandLogoRemover*>();
            }
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker