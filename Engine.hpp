#ifndef SPIC_PRJ_API_CD_ENGINE_HPP
#define SPIC_PRJ_API_CD_ENGINE_HPP

#include "EngineConfig.hpp"
#include "EventBus.hpp"
#include "PhysicsManager.hpp"
#include "Scene.hpp"
#include <AudioManager.hpp>
#include <memory>
#include <stack>

namespace spic {

    class Renderer;

    namespace Input {
        class InputHandler;
    }

    /**
     * @brief The engine class responsible for the game loop.
     * @sharedapi
     */
    class Engine {
    private:
        static Engine instance;

        Engine();
        ~Engine();

        EngineConfig config;

        std::stack<std::shared_ptr<Scene>> scenes;
        std::unique_ptr<spic::Renderer> renderer;
        std::unique_ptr<spic::Input::InputHandler> inputHandler;
        std::unique_ptr<spic::EventBus> eventBus;
        std::unique_ptr<spic::PhysicsManager> physicsManager;
        std::unique_ptr<spic::AudioManager> audioManager;

        bool isRunning;
        int fps;
        bool showFps;
        bool showColliders;

        void UpdateBehaviourScripts() const;
        void UpdateAnimators() const;
        void Render();

    public:
        static Engine& Instance();
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        Engine(const Engine&&) = delete;
        Engine& operator=(Engine&&) = delete;

        /**
         * @brief Initialize the engine with the given configuration.
         * @param config The engine configuration struct.
         */
        void Init(const spic::EngineConfig& config);

        /**
         * @brief Get a modifiable reference to the engine configuration.
         * @return A reference to the engine configuration that you can modify.
         */
        spic::EngineConfig& Config();

        void Start();
        void PushScene(const std::shared_ptr<Scene>& scene);
        std::shared_ptr<Scene> PeekScene() const;
        void PopScene();
        void Shutdown();

        /**
         * Retrieve the EventBus with which to send events or listen to them.
         * @return The event bus.
         * @sharedapi
         */
        std::unique_ptr<spic::EventBus>& EventBus();

        /**
         * Retrieve the PhysicsManager with which you can clear the physics world.
         * @return The physics manager.
         * @sharedapi
         */
        const std::unique_ptr<spic::PhysicsManager>& PhysicsManager() const;

        /**
         * @note May NOT be used in the game, but since there is no package private it is public here.
         * @return The renderer.
         * @sharedapi
         */
        const std::unique_ptr<spic::Renderer>& Renderer() const;

        /**
         * @note May NOT be used in the game, but since there is no package private it is public here.
         * @return The input handler.
         * @sharedapi
         */
        const std::unique_ptr<spic::Input::InputHandler>& InputHandler() const;

        /**
         * @note May NOT be used in the game, but since there is no package private it is public here.
         * @return The audio manager.
         * @sharedapi
         */
        const std::unique_ptr<spic::AudioManager>& AudioManager() const;

        /**
         * Transition to a new scene with a transition scene in between.
         *
         * You could for example make a LevelTransitionScene which you'd give some data like the floor you'll go to.
         * Then in the LevelTransitionScene you can just add game objects like you would normally do and show it.
         *
         * @tparam Transition The transition scene type.
         * @tparam TransitionData The type of data for the transition scene.
         * @tparam TransitionTimeMs How long the transition scene will be shown in milliseconds.
         * @param data The data for the transition scene.
         * @param scene The scene the user will go to after the transition scene.
         */
        template <typename Transition, typename TransitionData, size_t TransitionTimeMs = 1000>
        void TransitionToScene(TransitionData data, std::shared_ptr<spic::Scene> scene) {
            auto transition = std::make_shared<Transition>(data, TransitionTimeMs, scene);
            PushScene(transition);
        }

        void ToggleFps();
        void ToggleColliders();
    };
}

#endif // SPIC_PRJ_API_CD_ENGINE_HPP
