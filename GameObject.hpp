#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Component.hpp"
#include "Transform.hpp"
#include <string>
#include <vector>
#include <memory>

#if __has_include("GameObject_includes.hpp")
#include "GameObject_includes.hpp"
#endif

namespace spic {

    /**
     * @brief Any object which should be represented on screen.
     * @spicapi
     */
    class GameObject {
        public:
            virtual ~GameObject() = default;

            /**
             * @brief Finds a GameObject by name and returns it.
             * @param name The name of the GameObject you want to find.
             * @return Pointer to GameObject, or nullptr if not found.
             * @spicapi
             */
            static std::shared_ptr<GameObject> Find(const std::string& name);

            /**
             * @brief Returns a vector of active GameObjects tagged tag. Returns empty
             *        vector if no GameObject was found.
             * @param tag The tag to find.
             * @return std::vector of GameObject pointers. No ownership.
             * @spicapi
             */
            static std::vector<std::shared_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);

            /**
             * @brief Returns one active GameObject tagged tag. Returns nullptr if no GameObject was found.
             * @param tag The tag to find.
             * @return Pointer to GameObject, or nullptr if not found.
             * @spicapi
             */
            static std::shared_ptr<GameObject> FindWithTag(const std::string& tag);

            /**
             * @brief Returns the first active loaded object of Type type.
             * @spicapi
             */
            template<class T>
            static std::shared_ptr<T> FindObjectOfType(bool includeInactive = false);

            /**
             * @brief Gets a list of all loaded objects of Type type.
             * @spicapi
             */
            template<class T>
            static std::vector<std::shared_ptr<T>> FindObjectsOfType(bool includeInactive = false);

            /**
             * @brief Removes a GameObject from the administration.
             * @details TODO What happens if this GameObject is a parent to others? What happens
             *          to the Components it possesses?
             * @param obj The GameObject to be destroyed. Must be a valid pointer to existing Game Object.
             * @exception A std::runtime_exception is thrown when the pointer is not valid.
             * @spicapi
             */
            static void Destroy(std::shared_ptr<GameObject> obj);

            /**
             * @brief Removes a Component.
             * @details Will search for the Component among the GameObjects.
             * @param obj The Component to be removed.
             * @spicapi
             */
            static void Destroy(Component* obj);

            /**
             * @brief Constructor.
             * @details The new GameObject will also be added to a statically
             *          available collection, the administration.  This makes the
             *          Find()-functions possible.
             * @param name The name for the game object.
             * @param tag The tag for the game object.
             * @param layer The layer for the game object.
             * @spicapi
             */
            GameObject(const std::string& name, const std::string& tag, int layer);

            /**
             * @brief Does the object exist?
             * @spicapi
             */
            operator bool() const;

            /**
             * @brief Compare two GameObjects.
             * @param other The other object to compare this one with.
             * @return true if not equal, false otherwise.
             * @spicapi
             */
            bool operator!=(const GameObject& other) const;

            /**
             * @brief Compare two GameObjects
             * @param other The other object to compare this one with.
             * @return true if equal, false otherwise.
             * @spicapi
             */
            bool operator==(const GameObject& other) const;

            /**
             * @brief Add a Component of the specified type. Must be a valid
             *        subclass of Component. The GameObject assumes ownership of
             *        the Component.
             * @details This function places a pointer to the component in
             *          a suitable container.
             * @param component Reference to the component.
             * @spicapi
             */
            template<class T>
            void AddComponent(std::shared_ptr<T> component);

            /**
             * @brief Removes a component from a game object.
             * @param component Reference to the component.
             * @sharedapi
             */
            void RemoveComponent(std::shared_ptr<Component> component);

            /**
             * @brief Get the first component of the specified type. Must be
             *        a valid subclass of Component.
             * @return Pointer to Component instance.
             * @spicapi
             */
            template<class T>
            std::shared_ptr<T> GetComponent() const;

            /**
             * @brief Get the first component of the specified type from
             *        contained game objects. Must be
             *        a valid subclass of Component.
             * @return Pointer to Component instance.
             * @spicapi
             */
            template<class T>
            std::shared_ptr<T> GetComponentInChildren() const;

            /**
             * @brief Get the first component of the specified type from
             *        the parent game object. Must be
             *        a valid subclass of Component.
             * @return Pointer to Component instance.
             * @spicapi
             */
            template<class T>
            std::shared_ptr<T> GetComponentInParent() const;

            /**
             * @brief Get all components of the specified type. Must be
             *        a valid subclass of Component.
             * @return Vector with pointers to Component instances.
             * @spicapi
             */
            template<class T>
            std::vector<std::shared_ptr<T>> GetComponents() const;

            /**
             * @brief Get all components of the specified type from
             *        contained game objects. Must be
             *        a valid subclass of Component.
             * @return Vector with pointers to Component instances.
             * @spicapi
             */
            template<class T>
            std::vector<std::shared_ptr<T>> GetComponentsInChildren() const;

            /**
             * @brief Get all components op the specified type from
             *        the parent game object. Must be
             *        a valid subclass of Component.
             * @return Vector with pointers to Component instances.
             * @spicapi
             */
            template<class T>
            std::vector<std::shared_ptr<T>> GetComponentsInParent() const;

            /**
             * @brief Activates/Deactivates the GameObject, depending on the given true or false value.
             * @param active Desired value.
             * @spicapi
             */
            void Active(bool flag);

            /**
             * @brief Returns whether this game object is itself active.
             * @return true if active, false if not.
             * @spicapi
             */
            bool Active() const;

            /**
             * @brief Returns whether this game component is active, taking its parents
             *        into consideration as well.
             * @return true if game object and all of its parents are active,
             *        false otherwise.
             * @spicapi
             */
            bool IsActiveInWorld() const;

            /**
             * @brief Returns the transform of this GameObject
             * @return A reference to the transform
             * @sharedapi
             */
            spic::Transform& Transform();

            /**
             * @brief Returns a const reference to the transform of this GameObject
             * @return A const reference to the transform
             * @sharedapi
             */
            const spic::Transform& Transform() const;

            /**
             * The parent of this GameObject.
             * @return A weak pointer to the parent.
             * @sharedapi
             */
            std::weak_ptr<GameObject> Parent();

            /**
             * The parent of this GameObject.
             * @param parent A weak pointer to the new parent
             * @sharedapi
             */
            void Parent(std::weak_ptr<GameObject> parent);

            /**
             * Returns a list of children in this GameObject.
             * @return A list of shared pointers to the children.
             * @sharedapi
             */
            const std::vector<std::shared_ptr<GameObject>>& Children() const;

            /**
             * Add a child to the children of this GameObject.
             * @param child the child to add.
             * @sharedapi
             */
            void AddChild(std::shared_ptr<GameObject> child);

            /**
             * Remove a child from the children of this GameObject.
             * @param child the child to remove.
             * @sharedapi
             */
            void RemoveChild(std::shared_ptr<GameObject> child);

            /**
             * Retrieve the name of this GameObject.
             * @return the name of this GameObject.
             * @sharedapi
             */
            const std::string& Name() const;

            /**
             * Retrieve the tag of this GameObject.
             * @return the tag of this GameObject.
             * @sharedapi
             */
            const std::string& Tag() const;

            /**
             * Retrieve the layer of this GameObject.
             * @return the layer of this GameObject.
             * @sharedapi
             */
            int Layer() const;

            // Include "package private" methods
#if __has_include("GameObject_public.hpp")
#include "GameObject_public.hpp"
#endif

        private:
            std::string name;
            std::string tag;
            bool active;
            int layer;

#if __has_include("GameObject_private.hpp")
#include "GameObject_private.hpp"
#endif
    };

}

#if __has_include("GameObject_templates.hpp")
#include "GameObject_templates.hpp"
#endif

#endif // GAMEOBJECT_H_
