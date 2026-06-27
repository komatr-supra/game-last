#pragma once
#include <cstddef>
/**
 * @brief id for typesafety, its just size_t
 */
namespace game
{
template <typename Tag> struct TypeID
{
    size_t value;

    explicit constexpr TypeID(size_t v) : value(v) {}

    auto operator<=>(const TypeID&) const = default;
};
} // namespace game