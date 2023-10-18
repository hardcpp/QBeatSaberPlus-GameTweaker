#pragma once

#include <CP_SDK/Config/JsonConfig.hpp>

#include <UnityEngine/Color.hpp>
#include <UnityEngine/Color32.hpp>

namespace QBeatSaberPlus_GameTweaker {

    using namespace UnityEngine;

    class GTConfig : public CP_SDK::Config::JsonConfig
    {
        CP_SDK_CONFIG_JSONCONFIG_INSTANCE_DECL(GTConfig);

        public:
            struct _Environment
            {
                bool RemoveMusicBandLogo            = false;
                bool RemoveFullComboLossAnimation   = false;

                CP_SDK_JSON_SERIALIZE_DECL();
                CP_SDK_JSON_UNSERIALIZE_DECL();
            };
            struct _LevelSelection
            {
                bool    RemoveBaseGameFilterButton  = false;
                bool    HighlightEnabled            = true;
                Color32 HighlightPlayed             = Color32(248, 230, 0, 255);
                Color32 HighlightAllPlayed          = Color32( 82, 247, 0, 255);

                CP_SDK_JSON_SERIALIZE_DECL();
                CP_SDK_JSON_UNSERIALIZE_DECL();
            };
            struct _PlayerOptions
            {
                bool    ReorderPlayerSettings           = true;
                bool    MergeLightPressetOptions        = true;
                bool    OverrideLightIntensityOption    = true;
                float   OverrideLightIntensity          = 1.0f;

                CP_SDK_JSON_SERIALIZE_DECL();
                CP_SDK_JSON_UNSERIALIZE_DECL();
            };
            struct _MainMenu
            {
                bool    OverrideMenuEnvColors           = false;
                Color   BaseColor                       = Color(0.421376616f, 0.201642916f, 0.67450980f, 1.0f);
                Color   LevelClearedColor               = Color(0.203647852f, 0.479708000f, 0.07326582f, 1.0f);
                Color   LevelFailedColor                = Color(0.796078444f, 0.137425855f, 0.00000000f, 1.0f);
                bool    RemoveNewContentPromotional     = true;
                bool    DisableFireworks                = false;

                CP_SDK_JSON_SERIALIZE_DECL();
                CP_SDK_JSON_UNSERIALIZE_DECL();
            };

            bool Enabled = false;

            bool RemoveDebris                   = false;
            bool RemoveAllCutParticles          = false;
            bool RemoveObstacleParticles        = false;
            bool RemoveSaberBurnMarks           = false;
            bool RemoveSaberBurnMarkSparkles    = false;
            bool RemoveSaberClashEffects        = false;
            bool RemoveWorldParticles           = false;

            std::shared_ptr<_Environment>      Environment     = std::make_shared<_Environment>();
            std::shared_ptr<_LevelSelection>   LevelSelection  = std::make_shared<_LevelSelection>();
            std::shared_ptr<_PlayerOptions>    PlayerOptions   = std::make_shared<_PlayerOptions>();
            std::shared_ptr<_MainMenu>         MainMenu        = std::make_shared<_MainMenu>();

        protected:
            /// @brief Reset config to default
            void Reset_Impl() override;

        protected:
            /// @brief Write the document
            /// @param p_Document Target
            CP_SDK_JSON_SERIALIZE_DECL() override;
            /// @brief Read the document
            /// @param p_Document Source
            CP_SDK_JSON_UNSERIALIZE_DECL() override;

        protected:
            /// @brief Get relative config path
            std::filesystem::path GetRelativePath() override;

        protected:
            /// @brief On config init
            /// @param p_OnCreation On creation
            void OnInit(bool p_OnCreation) override;

    };

}   ///< namespace QBeatSaberPlus_GameTweaker