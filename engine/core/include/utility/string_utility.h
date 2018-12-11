#pragma once

#ifndef SHIROIENGINE_STRING_UTILITY_H
#define SHIROIENGINE_STRING_UTILITY_H

#include <sstream>
#include <iomanip>
#include <types.h>
#include <vector>

template<typename TInputIter>
std::string hex(TInputIter first, TInputIter last, bool use_uppercase = true, bool insert_spaces = false);

std::vector<std::string> split(std::string strToSplit, int8 delimeter);

#endif