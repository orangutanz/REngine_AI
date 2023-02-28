#pragma once

#include <array>
#include <assert.h>
#include <functional>
#include <iostream>
#include <list>
#include <vector>
#include <string>

#define AIAssert(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (false)