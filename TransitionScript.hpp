#ifndef BANJO_GAME_TRANSITIONSCRIPT_HPP
#define BANJO_GAME_TRANSITIONSCRIPT_HPP

#include <BehaviourScript.hpp>
#include <functional>

namespace spic {
    class TransitionScript : public BehaviourScript {
    public:
        TransitionScript(double maxTime,
                         const std::function<void(double progress)>& tickFn,
                         const std::function<void(void)>& doneFn);

        void OnUpdate() override;

    private:
        double time;
        double maxTime;

        std::function<void(double progress)> tickFn;
        std::function<void(void)> doneFn;
    };
}

#endif
