#pragma once

#include "UI/SettingsMainView.hpp"
#include "UI/SettingsLeftView.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/ModuleBase.hpp>
#include <CP_SDK/ChatPlexSDK.hpp>
#include <CP_SDK_BS/Game/Logic.hpp>

namespace QBeatSaberPlus_GameTweaker {

    /// @brief Game Tweaker instance
    class GameTweaker : public CP_SDK::ModuleBase<GameTweaker>
    {
        CP_SDK_MODULE_BASE_INSTANCE_DECL(GameTweaker);

        public:
            CP_SDK::EIModuleBaseType            Type()                      const override { return CP_SDK::EIModuleBaseType::Integrated;                               }
            std::u16string_view                 Name()                      const override { return u"Game Tweaker";                                                    }
            std::u16string_view                 FancyName()                 const override { return u"Game Tweaker";                                                    }
            std::u16string_view                 Description()               const override { return u"Customize your game play & menu experience!";                     }
            std::u16string_view                 DocumentationURL()          const override { return u"https://github.com/hardcpp/BeatSaberPlus/wiki#game-tweaker";      }
            bool                                UseChatFeatures()           const override { return false;                                                              }
            bool                                IsEnabled()                 const override { return GTConfig::Instance()->Enabled;                                      }
            void                                IsEnabled(bool p_Enabled)         override { GTConfig::Instance()->Enabled = p_Enabled; GTConfig::Instance()->Save();   }
            CP_SDK::EIModuleBaseActivationType  ActivationType()            const override { return CP_SDK::EIModuleBaseActivationType::OnMenuSceneLoaded;              }

        private:
            CP_SDK::Utils::MonoPtr<UI::SettingsMainView>                        m_SettingsMainView;
            CP_SDK::Utils::MonoPtr<UI::SettingsLeftView>                        m_SettingsLeftView;

        public:
            /// @brief Constructor
            GameTweaker();

        protected:
            /// @brief Enable the Module
            void OnEnable() override;
            /// @brief Disable the Module
            void OnDisable() override;

        public:
            /// @brief Get Module settings UI
            t_InitialViews GetSettingsViewControllers() override;

        public:
            /// @brief Update patches
            /// @param p_ForceDisable Force disable
            void UpdatePatches(bool p_ForceDisable);
            /// @brief Update world particles
            /// @param p_ForceDisable Force disable
            void UpdateWorldParticles(bool p_ForceDisable = false);

        private:
            /// @brief On game scene change
            /// @param p_Scene New scene
            void Game_OnSceneChange(CP_SDK_BS::Game::Logic::ESceneType p_Scene);
            /// @brief On level started
            /// @param p_LevelData Level data
            void Game_OnLevelStarted(const CP_SDK_BS::Game::LevelData::Ptr& p_LevelData);


    };

}   ///< namespace QBeatSaberPlus_GameTweaker