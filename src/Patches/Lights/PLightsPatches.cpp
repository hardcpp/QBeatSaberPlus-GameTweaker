#include "Patches/Lights/PLightsPatches.hpp"
#include "GTConfig.hpp"

#include <CP_SDK/Utils/MonoPtr.hpp>

#include <UnityEngine/Color.hpp>

#include <GlobalNamespace/BloomPrePassBackgroundColorsGradientTintColorWithLightIds.hpp>
#include <GlobalNamespace/BloomPrePassBackgroundColorsGradientElementWithLightId.hpp>
#include <GlobalNamespace/BloomPrePassBackgroundLightWithId.hpp>
#include <GlobalNamespace/DirectionalLightWithId.hpp>
#include <GlobalNamespace/InstancedMaterialLightWithId.hpp>
#include <GlobalNamespace/MaterialLightWithId.hpp>
#include <GlobalNamespace/ParticleSystemLightWithId.hpp>
#include <GlobalNamespace/SpriteLightWithId.hpp>
#include <GlobalNamespace/TubeBloomPrePassLightWithId.hpp>
#include <GlobalNamespace/UnityLightWithId.hpp>
#include <GlobalNamespace/LightWithIds.hpp>
#include <GlobalNamespace/LightWithIds_LightWithId.hpp>
#include <GlobalNamespace/LightmapLightWithIds.hpp>

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace QBeatSaberPlus_GameTweaker::Patches { namespace Lights {

    static float    PLightsPatches_Intensity    = 1.0f;
    static bool     PLightsPatches_SceneIsValid = false;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set from configuration
    void PLightsPatches::SetFromConfig()
    {
        auto l_Config = GTConfig::Instance();
        if (l_Config->Enabled && l_Config->PlayerOptions->OverrideLightIntensityOption)
            PLightsPatches_Intensity = l_Config->PlayerOptions->OverrideLightIntensity;
        else
            PLightsPatches_Intensity = 1.0f;
    }
    /// @brief Set temp config
    /// @param p_Intensity New intensity
    void PLightsPatches::SetTempLightIntensity(float p_Intensity)
    {
        PLightsPatches_Intensity = p_Intensity;
    }

    void PLightsPatches::SetIsValidScene(bool p_IsValid)
    {
        PLightsPatches_SceneIsValid = p_IsValid;
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    static void ImplSetColor(Color& color)
    {
        if (!PLightsPatches_SceneIsValid || PLightsPatches_Intensity == 1.0f)
            return;

        float l_Alpha = color.a;

        float l_H, l_S, l_V;
        Color::RGBToHSV(color, l_H, l_S, l_V);
        l_V *= PLightsPatches_Intensity;

        color = Color::HSVToRGB(l_H, l_S, l_V);

        color.a = l_Alpha;
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    #define HOOK_AUTO_COLOR_WAS_SET(__Type)                                                                                         \
        CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(__Type##_ColorWasSet, &__Type::ColorWasSet, void, __Type* __Instance, Color __a)    \
        {                                                                                                                           \
            ImplSetColor(__a);                                                                                                      \
            __Type##_ColorWasSet(__Instance, __a);                                                                                  \
        }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    HOOK_AUTO_COLOR_WAS_SET(BloomPrePassBackgroundColorsGradientTintColorWithLightIds);
    HOOK_AUTO_COLOR_WAS_SET(BloomPrePassBackgroundColorsGradientElementWithLightId);
    HOOK_AUTO_COLOR_WAS_SET(BloomPrePassBackgroundLightWithId);
    HOOK_AUTO_COLOR_WAS_SET(DirectionalLightWithId);

    /// EnableRendererWithLightId

    HOOK_AUTO_COLOR_WAS_SET(InstancedMaterialLightWithId);
    HOOK_AUTO_COLOR_WAS_SET(MaterialLightWithId);
    HOOK_AUTO_COLOR_WAS_SET(ParticleSystemLightWithId);
    HOOK_AUTO_COLOR_WAS_SET(SpriteLightWithId);
    HOOK_AUTO_COLOR_WAS_SET(TubeBloomPrePassLightWithId);
    HOOK_AUTO_COLOR_WAS_SET(UnityLightWithId);
    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(LightWithIds_LightWithId_ColorWasSet, &LightWithIds::LightWithId::ColorWasSet,
                                            void, LightWithIds::LightWithId* __Instance,
                                            Color __a)
    {
        ImplSetColor(__a);
        LightWithIds_LightWithId_ColorWasSet(__Instance, __a);
    }
    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(LightmapLightWithIds_SetDataToShaders, &LightmapLightWithIds::SetDataToShaders,
                                            void, LightmapLightWithIds* __Instance,
                                            Color __a, Color __b)
    {
        ImplSetColor(__a);
        ImplSetColor(__b);
        LightmapLightWithIds_SetDataToShaders(__Instance, __a, __b);
    }

}   ///< namespace Lights
}   ///< namespace QBeatSaberPlus_GameTweaker::Patches