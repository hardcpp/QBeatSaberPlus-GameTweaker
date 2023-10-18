#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>
#include <CP_SDK/Utils/MonoPtr.hpp>

#include <custom-types/shared/coroutine.hpp>
#include <GlobalNamespace/ColorSO.hpp>
#include <GlobalNamespace/MenuLightsManager.hpp>
#include <GlobalNamespace/MenuLightsPresetSO.hpp>
#include <UnityEngine/Color.hpp>

namespace QBeatSaberPlus_GameTweaker::Managers {

    namespace _u
    {
        using namespace CP_SDK::Utils;
        using namespace GlobalNamespace;
        using namespace UnityEngine;
    }

    /// @brief Custom SerializedObject color for BeatGame serialized object
    class CustomColorSO : public _u::ColorSO
    {
        CP_SDK_IL2CPP_INHERIT("QBeatSaberPlus_GameTweaker.Managers", CustomColorSO, _u::ColorSO);

        public:
            _u::Color _color;

            CP_SDK_IL2CPP_OVERRIDE_METHOD2(_u, ColorSO, _u::Color, get_color);

    };

    /// @brief Custom menu light manager replacement
    class CustomMenuLightManager
    {
        DISABLE_CONSTRUCTORS(CustomMenuLightManager);

        private:
            static _u::MonoPtr<_u::MenuLightsManager>                       m_MenuLightsManager;
            static _u::MonoPtr<_u::MenuLightsPresetSO>                      m_DefaultPreset;
            static _u::MonoPtr<_u::MenuLightsPresetSO>                      m_LevelClearedPreset;
            static _u::MonoPtr<_u::MenuLightsPresetSO>                      m_LevelFailedPreset;
            static std::vector<std::tuple<float, _u::MonoPtr<_u::ColorSO>>> m_DefaultPresetBackup;
            static std::vector<std::tuple<float, _u::MonoPtr<_u::ColorSO>>> m_LevelClearedPresetBackup;
            static std::vector<std::tuple<float, _u::MonoPtr<_u::ColorSO>>> m_LevelFailedPresetBackup;
            static _u::MonoPtr<CustomColorSO>                               m_Custom_Default;
            static _u::MonoPtr<CustomColorSO>                               m_Custom_Cleared;
            static _u::MonoPtr<CustomColorSO>                               m_Custom_Failed;

        public:
            /// @brief Init and start reflection fetching
            static void Init();

        public:
            /// @brief Apply current config
            static void UpdateFromConfig();
            /// @brief Switch to base preset
            static void SwitchToBase();
            /// @brief Switch to level cleared preset
            static void SwitchToLevelCleared();
            /// @brief Switch to level failed preset
            static void SwitchToLevelFailed();

        private:
            /// @brief Init coroutine that fetch object by reflection
            static custom_types::Helpers::Coroutine Coroutine_InitLate();

        public:
            /// @brief Preset replacer for PMenuLightsManager harmony patch
            /// @param preset Input preset
            static _u::MenuLightsPresetSO* GetPresetForPatch(_u::MenuLightsPresetSO* preset);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Managers

CP_SDK_IL2CPP_INHERIT_HELPERS(QBeatSaberPlus_GameTweaker::Managers::CustomColorSO);