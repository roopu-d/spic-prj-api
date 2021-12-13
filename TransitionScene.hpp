#ifndef SPIC_PRJ_API_CD_TRANSITIONSCENE_HPP
#define SPIC_PRJ_API_CD_TRANSITIONSCENE_HPP

#include <Camera.hpp>
#include <Scene.hpp>

namespace spic {
    class TransitionScene : public Scene {
    public:
        explicit TransitionScene(size_t transitionTime, std::shared_ptr<spic::Scene> next);

        void OnCreate() override;
        void OnActivate() override;

        virtual void Tick(double progress);
        void Done();

    protected:
        size_t transitionTime;

        std::shared_ptr<spic::Scene> next;

        std::shared_ptr<spic::Camera> camera;
    };
}

#endif
