#include "GTConfig.hpp"
#include "Logger.hpp"

#include <CP_SDK/Utils/Il2cpp.hpp>
#include <CP_SDK/Unity/Extensions/ColorU.hpp>
#include <CP_SDK_BS/Game/Levels.hpp>

#include <stdio.h>
#include <string.h>

#include <GlobalNamespace/LevelListTableCell.hpp>
#include <GlobalNamespace/BeatmapLevel.hpp>
#include <TMPro/TextMeshProUGUI.hpp>

using namespace CP_SDK::Unity::Extensions;
using namespace GlobalNamespace;

namespace QBeatSaberPlus_GameTweaker::Patches {

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        LevelListTableCell_SetDataFromLevelAsync, &LevelListTableCell::SetDataFromLevelAsync,
        void, LevelListTableCell* __Instance,

        BeatmapLevel* __a, bool __b, bool __c, bool __d, bool __e)
    {
        LevelListTableCell_SetDataFromLevelAsync(__Instance, __a, __b, __c, __d, __e);

        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled && l_Config->LevelSelection->HighlightEnabled)
        {
            try
            {
                auto l_HaveAnyScore     = false;
                auto l_HaveAllScores    = false;
                CP_SDK_BS::Game::Levels::GetScoresByLevelID(__a->___levelID, &l_HaveAnyScore, &l_HaveAllScores);

                StringW l_ColorPrefix;
                if (l_HaveAllScores)
                    l_ColorPrefix = "<" + ColorU::ToHexRGB(ColorU::Convert(l_Config->LevelSelection->HighlightAllPlayed)) + ">";
                else if (l_HaveAnyScore)
                    l_ColorPrefix = "<" + ColorU::ToHexRGB(ColorU::Convert(l_Config->LevelSelection->HighlightPlayed)) + ">";

                __Instance->____songNameText->set_text(l_ColorPrefix + __Instance->____songNameText->get_text());
            }
            catch (const std::exception& l_Exception)
            {
                 Logger::Instance->Error(u"[Patches][PLevelListTableCell] Error:");
                 Logger::Instance->Error(l_Exception);
            }
        }
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches