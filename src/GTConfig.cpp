#include "GTConfig.hpp"

#include <CP_SDK/ChatPlexSDK.hpp>

namespace QBeatSaberPlus_GameTweaker {

    CP_SDK_CONFIG_JSONCONFIG_INSTANCE_IMPL(GTConfig);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Reset config to default
    void GTConfig::Reset_Impl()
    {
        RemoveDebris                   = false;
        RemoveAllCutParticles          = false;
        RemoveObstacleParticles        = false;
        RemoveSaberBurnMarks           = false;
        RemoveSaberBurnMarkSparkles    = false;
        RemoveSaberClashEffects        = false;
        RemoveWorldParticles           = false;

        Environment     = std::make_shared<_Environment>();
        LevelSelection  = std::make_shared<_LevelSelection>();
        PlayerOptions   = std::make_shared<_PlayerOptions>();
        MainMenu        = std::make_shared<_MainMenu>();
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Write the document
    /// @param p_Document Target
    CP_SDK_JSON_SERIALIZE_IMPL(GTConfig)
    {
        CP_SDK_JSON_SERIALIZE_BOOL(Enabled);

        CP_SDK_JSON_SERIALIZE_BOOL(RemoveDebris);
        CP_SDK_JSON_SERIALIZE_BOOL(RemoveAllCutParticles);
        CP_SDK_JSON_SERIALIZE_BOOL(RemoveObstacleParticles);
        CP_SDK_JSON_SERIALIZE_BOOL(RemoveSaberBurnMarks);
        CP_SDK_JSON_SERIALIZE_BOOL(RemoveSaberBurnMarkSparkles);
        CP_SDK_JSON_SERIALIZE_BOOL(RemoveSaberClashEffects);
        CP_SDK_JSON_SERIALIZE_BOOL(RemoveWorldParticles);

        CP_SDK_JSON_SERIALIZE_OBJECT(Environment);
        CP_SDK_JSON_SERIALIZE_OBJECT(LevelSelection);
        CP_SDK_JSON_SERIALIZE_OBJECT(PlayerOptions);
        CP_SDK_JSON_SERIALIZE_OBJECT(MainMenu);
    }
    /// @brief Read the document
    /// @param p_Document Source
    CP_SDK_JSON_UNSERIALIZE_IMPL(GTConfig)
    {
        CP_SDK_JSON_UNSERIALIZE_BOOL(Enabled);

        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveDebris);
        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveAllCutParticles);
        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveObstacleParticles);
        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveSaberBurnMarks);
        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveSaberBurnMarkSparkles);
        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveSaberClashEffects);
        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveWorldParticles);

        CP_SDK_JSON_UNSERIALIZE_OBJECT(Environment);
        CP_SDK_JSON_UNSERIALIZE_OBJECT(LevelSelection);
        CP_SDK_JSON_UNSERIALIZE_OBJECT(PlayerOptions);
        CP_SDK_JSON_UNSERIALIZE_OBJECT(MainMenu);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_JSON_SERIALIZE_IMPL(GTConfig::_Environment)
    {
        CP_SDK_JSON_SERIALIZE_BOOL(RemoveMusicBandLogo);
        CP_SDK_JSON_SERIALIZE_BOOL(RemoveFullComboLossAnimation);
    }
    CP_SDK_JSON_UNSERIALIZE_IMPL(GTConfig::_Environment)
    {
        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveMusicBandLogo);
        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveFullComboLossAnimation);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_JSON_SERIALIZE_IMPL(GTConfig::_LevelSelection)
    {
        CP_SDK_JSON_SERIALIZE_BOOL(RemoveBaseGameFilterButton);
        CP_SDK_JSON_SERIALIZE_BOOL(HighlightEnabled);

        CP_SDK_JSON_SERIALIZE_COLOR32(HighlightPlayed);
        CP_SDK_JSON_SERIALIZE_COLOR32(HighlightAllPlayed);
    }
    CP_SDK_JSON_UNSERIALIZE_IMPL(GTConfig::_LevelSelection)
    {
        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveBaseGameFilterButton);
        CP_SDK_JSON_UNSERIALIZE_BOOL(HighlightEnabled);

        CP_SDK_JSON_UNSERIALIZE_COLOR32(HighlightPlayed);
        CP_SDK_JSON_UNSERIALIZE_COLOR32(HighlightAllPlayed);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_JSON_SERIALIZE_IMPL(GTConfig::_PlayerOptions)
    {
        CP_SDK_JSON_SERIALIZE_BOOL(ReorderPlayerSettings);
        CP_SDK_JSON_SERIALIZE_BOOL(MergeLightPressetOptions);
        CP_SDK_JSON_SERIALIZE_BOOL(OverrideLightIntensityOption);

        CP_SDK_JSON_SERIALIZE_FLOAT(OverrideLightIntensity);
    }
    CP_SDK_JSON_UNSERIALIZE_IMPL(GTConfig::_PlayerOptions)
    {
        CP_SDK_JSON_UNSERIALIZE_BOOL(ReorderPlayerSettings);
        CP_SDK_JSON_UNSERIALIZE_BOOL(MergeLightPressetOptions);
        CP_SDK_JSON_UNSERIALIZE_BOOL(OverrideLightIntensityOption);

        CP_SDK_JSON_UNSERIALIZE_FLOAT(OverrideLightIntensity);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_JSON_SERIALIZE_IMPL(GTConfig::_MainMenu)
    {
        CP_SDK_JSON_SERIALIZE_BOOL(OverrideMenuEnvColors);

        CP_SDK_JSON_SERIALIZE_COLOR(BaseColor);
        CP_SDK_JSON_SERIALIZE_COLOR(LevelClearedColor);
        CP_SDK_JSON_SERIALIZE_COLOR(LevelFailedColor);

        CP_SDK_JSON_SERIALIZE_BOOL(RemoveNewContentPromotional);
        CP_SDK_JSON_SERIALIZE_BOOL(DisableFireworks);
    }
    CP_SDK_JSON_UNSERIALIZE_IMPL(GTConfig::_MainMenu)
    {
        CP_SDK_JSON_UNSERIALIZE_BOOL(OverrideMenuEnvColors);

        CP_SDK_JSON_UNSERIALIZE_COLOR(BaseColor);
        CP_SDK_JSON_UNSERIALIZE_COLOR(LevelClearedColor);
        CP_SDK_JSON_UNSERIALIZE_COLOR(LevelFailedColor);

        CP_SDK_JSON_UNSERIALIZE_BOOL(RemoveNewContentPromotional);
        CP_SDK_JSON_UNSERIALIZE_BOOL(DisableFireworks);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Get relative config path
    std::filesystem::path GTConfig::GetRelativePath()
    {
        return std::filesystem::path("QBeatSaberPlus") / "GameTweaker" / "Config";
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief On config init
    /// @param p_OnCreation On creation
    void GTConfig::OnInit(bool p_OnCreation)
    {

    }

}   ///< namespace QBeatSaberPlus_GameTweaker