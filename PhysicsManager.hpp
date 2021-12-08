#ifndef BANJO_GAME_PHYSICSMANAGER_HPP
#define BANJO_GAME_PHYSICSMANAGER_HPP

#include <memory>

namespace spic {
    class GameObject;

    class PhysicsManager {
    public:
        PhysicsManager();
        ~PhysicsManager();

        // No move or copy
        PhysicsManager(const PhysicsManager&) = delete;
        PhysicsManager(PhysicsManager&&) = delete;
        PhysicsManager& operator=(const PhysicsManager&) = delete;
        PhysicsManager& operator=(PhysicsManager&&) = delete;

        void Update();
        void ResetWorld();

        void DestroyObject(const std::shared_ptr<GameObject>& gameObject);

    private:
        class PhysicsManagerImpl;

        std::unique_ptr<PhysicsManagerImpl> impl;
    };
}

#endif
