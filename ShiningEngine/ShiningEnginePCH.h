#pragma once

#if _DEBUG
#include <vld.h>
#endif

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
//engine
#include "ShiningEngine.h"
//input
#include "InputContext.h"
#include <SDL_Keycode.h>
#include "ControllerInput.h"
//components & game object
#include "GameObject.h"
#include "RenderComponent.h"
#include "StateComponent.h"
#include "PhysicsComponent.h"
#include "TextComponent.h"
#include "CollisionComponent.h"
#include "SpawnComponent.h"
//patterns
#include "Command.h"
#include "State.h"
#include "Observer.h"
//scene
#include "Scene.h"
#include "SceneManager.h"
//collision
#include "CollisionBehavior.h"
//audio
#include "AudioPlayer.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
