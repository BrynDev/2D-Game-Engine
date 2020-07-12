#pragma once

#if _DEBUG
#include <vld.h>
#endif

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <vector>
#include <SDL_Keycode.h>
#include "ControllerInput.h"
#include "Command.h"
#include "ShiningEngine.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "Scene.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
