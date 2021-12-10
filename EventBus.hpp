#ifndef BANJO_GAME_EVENTBUS_HPP
#define BANJO_GAME_EVENTBUS_HPP

#include <any>
#include <atomic>
#include <functional>
#include <iostream>
#include <map>
#include <thread>
#include <typeindex>
#include <unordered_map>
#include <utility>

namespace spic {
    struct HandlerRegistration {
        const void* handle{nullptr};
    };

    class EventBus {
    public:
        EventBus();

        template <typename T> unsigned long Listen(std::function<void(const T&)> fn) {
            registrations.try_emplace(++registrationId, RegisterHandler<T>(fn));
            return registrationId;
        }

        template <typename T, typename... Args> void Publish(Args&&... args) {
            FireEvent(T{std::forward<Args>(args)...});
        }

        void Unregister(unsigned long);

        void UnregisterAll();

    private:
        std::unordered_multimap<std::type_index, std::function<void(std::any)>> handlers;

        unsigned long registrationId;
        std::map<unsigned long, HandlerRegistration> registrations;

        template <typename EventType, typename EventHandler>
        HandlerRegistration RegisterHandler(EventHandler&& handler) {
            auto it = handlers.emplace(
                std::type_index(typeid(EventType)),
                [func = std::forward<EventHandler>(handler)](auto value) { func(std::any_cast<EventType>(value)); });

            return {static_cast<const void*>(&(it->second))};
        }

        template <typename EventType, typename = std::enable_if_t<!std::is_pointer_v<EventType>>>
        void FireEvent(EventType&& evt) noexcept {
            auto [begin, end] = handlers.equal_range(std::type_index(typeid(EventType)));
            for (; begin != end; ++begin) {
                begin->second(evt);
            }
        }

        bool RemoveHandler(const HandlerRegistration& registration);
    };
}

#endif
