#pragma once

#include <CP_SDK/Utils/Il2cpp.hpp>

namespace QBeatSaberPlus_GameTweaker::Patches {

    /// @brief Base game filter removing
    class PLevelSearchViewController
    {
        CP_SDK_NO_DEF_CTORS(PLevelSearchViewController);

        public:
            /// @brief Set if we remove base game filter
            /// @param p_Enabled New state
            static void SetRemoveBaseGameFilter(bool p_Enabled);

    };

}   ///< namespace QBeatSaberPlus_GameTweaker::Patches