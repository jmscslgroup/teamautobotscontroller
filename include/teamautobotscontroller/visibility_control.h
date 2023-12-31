#ifndef TEAMAUTOBOTSCONTROLLER__VISIBILITY_CONTROL_H_
#define TEAMAUTOBOTSCONTROLLER__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define TEAMAUTOBOTSCONTROLLER_EXPORT __attribute__ ((dllexport))
    #define TEAMAUTOBOTSCONTROLLER_IMPORT __attribute__ ((dllimport))
  #else
    #define TEAMAUTOBOTSCONTROLLER_EXPORT __declspec(dllexport)
    #define TEAMAUTOBOTSCONTROLLER_IMPORT __declspec(dllimport)
  #endif
  #ifdef TEAMAUTOBOTSCONTROLLER_BUILDING_LIBRARY
    #define TEAMAUTOBOTSCONTROLLER_PUBLIC TEAMAUTOBOTSCONTROLLER_EXPORT
  #else
    #define TEAMAUTOBOTSCONTROLLER_PUBLIC TEAMAUTOBOTSCONTROLLER_IMPORT
  #endif
  #define TEAMAUTOBOTSCONTROLLER_PUBLIC_TYPE TEAMAUTOBOTSCONTROLLER_PUBLIC
  #define TEAMAUTOBOTSCONTROLLER_LOCAL
#else
  #define TEAMAUTOBOTSCONTROLLER_EXPORT __attribute__ ((visibility("default")))
  #define TEAMAUTOBOTSCONTROLLER_IMPORT
  #if __GNUC__ >= 4
    #define TEAMAUTOBOTSCONTROLLER_PUBLIC __attribute__ ((visibility("default")))
    #define TEAMAUTOBOTSCONTROLLER_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define TEAMAUTOBOTSCONTROLLER_PUBLIC
    #define TEAMAUTOBOTSCONTROLLER_LOCAL
  #endif
  #define TEAMAUTOBOTSCONTROLLER_PUBLIC_TYPE
#endif
#endif  // TEAMAUTOBOTSCONTROLLER__VISIBILITY_CONTROL_H_
// Generated 30-Nov-2023 11:50:46
// Copyright 2019-2020 The MathWorks, Inc.
