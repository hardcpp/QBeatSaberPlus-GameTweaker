#include "Components/MusicBandLogoRemover.hpp"

#include <CP_SDK_BS/Game/Logic.hpp>

#include <UnityEngine/Resources.hpp>
#include <UnityEngine/SpriteRenderer.hpp>
#include <UnityEngine/Transform.hpp>

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace QBeatSaberPlus_GameTweaker::Components {

    CP_SDK_IL2CPP_INHERIT_INIT(MusicBandLogoRemover);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    CP_SDK_IL2CPP_DECLARE_CTOR_IMPL(MusicBandLogoRemover)
    {

    }
    CP_SDK_IL2CPP_DECLARE_DTOR_MONOBEHAVIOUR_IMPL(MusicBandLogoRemover)
    {

    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief On component first frame
    void MusicBandLogoRemover::Start()
    {
        m_AudioTimeSyncController = Resources::FindObjectsOfTypeAll<AudioTimeSyncController*>()->FirstOrDefault();
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /// @brief Called every frames
    void MusicBandLogoRemover::Update()
    {
        if (!m_AudioTimeSyncController)
            m_AudioTimeSyncController = Resources::FindObjectsOfTypeAll<AudioTimeSyncController*>()->FirstOrDefault();

        if (CP_SDK_BS::Game::Logic::ActiveScene() != CP_SDK_BS::Game::Logic::ESceneType::Playing
            || !m_AudioTimeSyncController)
        {
            GameObject::Destroy(get_gameObject());
            return;
        }

        if (m_AudioTimeSyncController->____songTime == 0.0f)
            return;

        GameObject* l_Object = nullptr;

        /// BTS
        l_Object = Resources::FindObjectsOfTypeAll<GameObject*>()->FirstOrDefault([](GameObject* x) { return x->get_name() == "MagicDoorSprite"; });
        if (l_Object != nullptr)
        {
            l_Object->GetComponent<SpriteRenderer*>()->set_enabled(false);
            GameObject::Destroy(get_gameObject());
            return;
        }

        /// LinkinPark
        l_Object = Resources::FindObjectsOfTypeAll<GameObject*>()->FirstOrDefault([](GameObject* x) { return x->get_name() == "LinkinParkTextLogoL"; });
        if (l_Object != nullptr)
        {
            l_Object->GetComponent<SpriteRenderer*>()->set_enabled(false);

            l_Object = Resources::FindObjectsOfTypeAll<GameObject*>()->FirstOrDefault([](GameObject* x) { return x->get_name() == "LinkinParkTextLogoR"; });
            if (l_Object != nullptr)
                l_Object->GetComponent<SpriteRenderer*>()->set_enabled(false);

            l_Object = Resources::FindObjectsOfTypeAll<GameObject*>()->FirstOrDefault([](GameObject* x) { return x->get_name() == "Logo" && x->get_transform()->get_parent()->get_name() == "Environment"; });
            if (l_Object != nullptr)
                l_Object->GetComponent<SpriteRenderer*>()->set_enabled(false);

            GameObject::Destroy(get_gameObject());
            return;
        }

        GameObject::Destroy(get_gameObject());
    }

}   ///< namespace QBeatSaberPlus_GameTweaker::Components