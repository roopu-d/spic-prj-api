#ifndef BEHAVIOURSCRIPT_H_
#define BEHAVIOURSCRIPT_H_

#include "Collider.hpp"
#include "Component.hpp"
#include <memory>

namespace spic {
    class BehaviourScript : public Component {
        public:
            BehaviourScript();

            /**
             * @brief Called only once, often used to initialize values used by the script.
             *        Only called if gameobject is active
             * @spicapi
             */
            virtual void OnStart();

            /**
             * @brief called every tick
             *        Only called if gameobject is active
             * @spicapi
             */
            virtual void OnUpdate();

            /**
            * @brief Called when this scene is pushed on top of the stack, or when the scene directly above this
             * one is popped from the stack, thus revealing this one.(Via Scene::OnActivate )
            *      Always called, even if not active
            * @sharedapi
            */
            virtual void OnActivate();

            /**
             * @brief called when the scene is popped from the stack. (Via Scene::OnDeactivate)
             *      Always called, even if not active
             * @sharedapi
             */
            virtual void OnDeactivate();

            /**
             * @brief Sent when another object enters a trigger collider
             *        attached to this object (2D physics only).
             * @spicapi
             */
            virtual void OnTriggerEnter2D(std::shared_ptr<Collider> collider);

            /**
             * @brief Sent when another object leaves a trigger collider
             *        attached to this object (2D physics only).
             * @spicapi
             */
            virtual void OnTriggerExit2D(std::shared_ptr<spic::Collider> collider);

            /**
             * @brief Sent each frame where another object is within a trigger
             *        collider attached to this object (2D physics only).
             * @spicapi
             */
            virtual void OnTriggerStay2D(std::shared_ptr<spic::Collider> collider);

            /**
             * @brief Whether the script has been started.
             * @param started desired value
             * @sharedapi
             */
            void Started(bool started);

            /**
             * @brief Whether the script has been started.
             * @return current value
             * @sharedapi
             */
            bool Started() const;

        private:
            bool started;
    };

}

#endif // BEHAVIOURSCRIPT_H_
