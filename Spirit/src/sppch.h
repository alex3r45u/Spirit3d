#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Spirit/Log.h"

#define PROJECT Spirit::Application::Get().GetProject()

#ifdef HZ_PLATFORM_WINDOWS
#include <Windows.h>
#endif