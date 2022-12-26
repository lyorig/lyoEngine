#pragma once

/* macros.h:
   Convenience macros. */

/* A flag for conditional block compilation. */
#define SETTING constexpr

/* For clarification of conditionally compiled blocks. */
#define COMPILE_IF if constexpr

/* Since the Debug setting is going to be used a lot,
   there might as well be a specific macro for it. */
#define IF_DEBUG COMPILE_IF (lyo::Settings::Debug)

/* Namespace macros for more readable code. */
#define BEGIN_LYO_NAMESPACE namespace lyo {
#define END_LYO_NAMESPACE }

/* Declare something that's in a namespace. */
#define NAMESPACE_DECL(namespace_name, object) namespace namespace_name { object; }

/* Bool enumeration for clearer code. */
#define BOOL_ENUM(name) enum class name : bool {off, on}

/* Disable (delete) copy constructors, which would otherwise be
   generated automatically by the compiler. */
#define DELETE_COPY_CTORS(class_name) class_name(const class_name&) = delete; \
									  class_name& operator=(const class_name&) = delete;

/* For "shorter" casts. */
#define SC static_cast
#define CC const_cast
#define DC dynamic_cast
#define RC reinterpret_cast

/* Convert a type into the type of another variable. */
#define TO_VAR_TYPE(variable) SC<decltype(variable)>

/* Class member function property shorteners. */
#define SAFE const noexcept