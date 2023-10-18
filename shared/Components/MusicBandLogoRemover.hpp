#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>
#include <CP_SDK/Utils/MonoPtr.hpp>

#include <GlobalNamespace/AudioTimeSyncController.hpp>
#include <UnityEngine/MonoBehaviour.hpp>

namespace QBeatSaberPlus_GameTweaker::Components {

    namespace _u
    {
        using namespace GlobalNamespace;
        using namespace UnityEngine;
    }

    /// @brief MusicBandLogoRemover component
    class MusicBandLogoRemover : public _u::MonoBehaviour
    {
        CP_SDK_IL2CPP_INHERIT("QBeatSaberPlus_GameTweaker.Components", MusicBandLogoRemover, _u::MonoBehaviour);
        CP_SDK_IL2CPP_DECLARE_CTOR(MusicBandLogoRemover);
        CP_SDK_IL2CPP_DECLARE_DTOR_MONOBEHAVIOUR(MusicBandLogoRemover);

        private:
            CP_SDK::Utils::MonoPtr<_u::AudioTimeSyncController> m_AudioTimeSyncController;

        public:
            /// @brief On component first frame
            DECLARE_INSTANCE_METHOD(void, Start);

        public:
            /// @brief Called every frames
            DECLARE_INSTANCE_METHOD(void, Update);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Components

CP_SDK_IL2CPP_INHERIT_HELPERS(QBeatSaberPlus_GameTweaker::Components::MusicBandLogoRemover);