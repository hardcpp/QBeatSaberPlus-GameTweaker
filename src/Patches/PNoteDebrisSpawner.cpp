#include "Patches/PNoteDebrisSpawner.hpp"
#include "GTConfig.hpp"

#include <GlobalNamespace/NoteData.hpp>
#include <GlobalNamespace/ColorType.hpp>
#include <GlobalNamespace/NoteDebrisSpawner.hpp>
#include <UnityEngine/Quaternion.hpp>
#include <UnityEngine/Vector3.hpp>

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace QBeatSaberPlus_GameTweaker::Patches {

    static bool PNoteDebrisSpawner_RemoveDebris = false;

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Set from configuration
    void PNoteDebrisSpawner::SetFromConfig()
    {
        PNoteDebrisSpawner_RemoveDebris = GTConfig::Instance()->Enabled && GTConfig::Instance()->RemoveDebris;
    }
    /// @brief Set temp config
    /// @param p_RemoveDebris Should remove debris
    void PNoteDebrisSpawner::SetTemp(bool p_RemoveDebris)
    {
        PNoteDebrisSpawner_RemoveDebris = p_RemoveDebris;
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_HOOK_MAKE_AUTO_HOOK_MATCH(
        NoteDebrisSpawner_SpawnDebris, &NoteDebrisSpawner::SpawnDebris,
        void, NoteDebrisSpawner* __Instance,

        NoteData::GameplayType  __a, Vector3    __b, Vector3     __c, float __d,
        Vector3                 __e, Vector3    __f, Quaternion  __g, Vector3 __h,
        ColorType               __i, float      __j, Vector3     __k)
    {
        if (PNoteDebrisSpawner_RemoveDebris)
            return;

        NoteDebrisSpawner_SpawnDebris(__Instance, __a, __b, __c, __d, __e, __f, __g, __h, __i, __j, __k);
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches