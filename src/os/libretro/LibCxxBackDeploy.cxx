//============================================================================
//
// Back-deployment shim for 32-bit iOS.
//
// std::bad_optional_access and std::bad_variant_access are thrown by the cold
// side of std::optional and std::variant. Their out-of-line members live in
// Apple's libc++ dylib, which grew them in iOS 12 - and 32-bit iOS ended at
// iOS 10, so the armv7 slice of every SDK since has never had them. The core
// compiles and then fails to link:
//
//     Undefined symbols for architecture armv7:
//       "std::bad_optional_access::~bad_optional_access()"
//       "vtable for std::bad_variant_access"
//       "vtable for std::bad_optional_access"
//
// They are provided here instead, from the same definitions libc++ ships in
// src/optional.cpp and src/variant.cpp, so the throwing path exists at all
// rather than being linked against a library that cannot have it. Nothing else
// changes: on every other target this file compiles to nothing.
//============================================================================

#if defined(__APPLE__) && defined(__arm__)

#include <optional>
#include <variant>

_LIBCPP_BEGIN_NAMESPACE_STD

bad_optional_access::~bad_optional_access() noexcept = default;

const char* bad_optional_access::what() const noexcept
{
  return "bad_optional_access";
}

bad_variant_access::~bad_variant_access() noexcept = default;

const char* bad_variant_access::what() const noexcept
{
  return "bad_variant_access";
}

_LIBCPP_END_NAMESPACE_STD

#endif
