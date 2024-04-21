#include "Logger.hpp"
#include "GameTweaker.hpp"

#include <CP_SDK/ChatPlexSDK.hpp>
#include <CP_SDK/Logging/PaperLogger.hpp>

#include <beatsaber-hook/shared/utils/il2cpp-functions.hpp>
#include <custom-types/shared/register.hpp>

static modloader::ModInfo s_ModInfo{"QBeatSaberPlus-GameTweaker", VERSION, GIT_COMMIT};

// Called at the early stages of game loading
extern "C" void setup(CModInfo* p_ModInfo)
{
    p_ModInfo->id           = s_ModInfo.id.c_str();
    p_ModInfo->version      = s_ModInfo.version.c_str();
    p_ModInfo->version_long = s_ModInfo.versionLong;

    auto l_Logger = new CP_SDK::Logging::PaperLogger(p_ModInfo->id);

    l_Logger->Error(u"QBeatSaberPlus-GameTweaker Setuping!");

    QBeatSaberPlus_GameTweaker::Logger::Instance = l_Logger;
    CP_SDK::ChatPlexSDK::RegisterModule(new QBeatSaberPlus_GameTweaker::GameTweaker());

    l_Logger->Error(u"QBeatSaberPlus-GameTweaker Completed setup!");
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// Called later on in the game loading - a good time to install function hooks
extern "C" void late_load()
{
    il2cpp_functions::Init();

    QBeatSaberPlus_GameTweaker::Logger::Instance->Error(u"Registering custom types.");
    custom_types::Register::AutoRegister();
}