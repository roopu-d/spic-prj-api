#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Component.hpp"
#include "Sprite.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace spic {

    /**
     * @brief A component which can play animated sequences of sprites.
     * @spicapi
     */
    class Animator : public Component {
    public:
        /**
         * @brief Constructor.
         * @param fps The amount of frames the animator will cycle though per second.
         * @param sprites An list of sprites to loop through.
         * @sharedapi
         */
        Animator(int fps, const std::vector <std::shared_ptr<Sprite>> &sprites);

        /**
         * @brief Constructor.
         * @param fps The amount of frames the animator will cycle though per second.
         * @param spritesMap map of the states with the respective sprites vector
         * @sharedapi
         */
        Animator(int fps, const std::map <std::string, std::vector<std::string>> &spritesMap);

        /**
         * @brief Start playing the image sequence.
         * @param looping If true, will automatically start again when done.
         * @spicapi
         */
        void Play(bool looping);

        /**
         * @brief Stop playing the image sequence. Whatever sprite was displayed
         *        last will remain shown.
         * @spicapi
         */
        void Stop();

        /**
         * @brief Get the state the animator is currently in
         * @return A string which defines the state the animator is currently in
         * @sharedapi
         */
        std::string CurrentState() const;

        /**
         * @brief Set the state the animator is currently in
         * @param newState the state the animator should be in
         * @sharedapi
         */
        void CurrentState(const std::string &newState);

        /**
         * @brief Animate the game object according to the sprites in the vector or sprites map
         * @sharedapi
         */
        void Animate();

        /**
         * @brief Set the direction the sprites will face
         * @sharedapi
         */
        void FlipX(bool newFlipX);

    private:
        /**
         * @brief frames per second (playing speed)
         * @spicapi
         */
        int fps;

        std::vector <std::shared_ptr<Sprite>> sprites;

        /**
         * @brief index of the current sprite in the current state
         */
        int spriteIndex;

        /**
         * @brief name of the current state. for example "idle" or "running"
         */
        std::string currentState;

        /**
         * @brief map of the states with the respective sprites vector
         */
        std::map <std::string, std::vector<std::string>> spritesMap;

        /**
         * @brief the time that has elapsed since the last frame
         */
        double elapsedTime;

        /**
         * @brief true if the animator is playing
         */
        bool isPlaying;

        /**
         * @brief true if the animator is playing
         */
        bool isLooping;

        /**
         * @brief true if the object is facing right
         */
        bool flipX;
    };

}

#endif // ANIMATOR_H_
