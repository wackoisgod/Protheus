/*************************************************************************
Protheus Source File.
Copyright (C), Protheus Studios, 2013-2014.
-------------------------------------------------------------------------

Description:
Creates all the global's which are accessible through Lua.
-------------------------------------------------------------------------
History:
- 20:05:2014: Waring J.
*************************************************************************/

#pragma once

#include "lib\lua.hpp"
#include "..\GameObjects.h"
#include "..\Math.h" 
#include "..\graphics\Renderer.h"
#include <BufferWriter.h> 
#include "..\ScriptGame.h" 
#include "..\graphics\Sprite.h"
#include "..\event\EventHandler.h"
#include "..\Components.h"
#include "..\gui\GUIContext.h"
#include "..\gameobject\Scene.h"

#include <vector>

using namespace std;

namespace Pro{
	using namespace Component;
	using namespace GameObject;
	using namespace Graphics; 
	using namespace GUI;
	using namespace Math; 
	using namespace Asset;

	namespace Lua{
		class LuaMetatableFactory{
			typedef std::vector<luaL_Reg> Metatable;

			template<typename T> inline void saveMetatable(lua_State* L, Metatable& fields){
				luaL_newmetatable(L, T::lGetMetatable());
				lua_CFunction gc = nullptr;
				for each(const auto field in fields){ 
					lua_pushcfunction(L, field.func);
					lua_setfield(L, -2, field.name); 
				} 
				lua_pushstring(L, "__index");
				lua_pushvalue(L, -2);
				lua_settable(L, -3);
				//// Allocate a __gc if one is present 
				//lua_pushstring(L, "__gc");
				//lua_pushcfunction(L, &LuaMetatableFactory::lDelete<T>);
				//lua_settable(L, -3);
				
				lua_pop(L, 1);
			}

			template<typename T> inline void defineMetatable(lua_State* L){
				Metatable fields;
				T::lGetFunctions<T>(fields); 
#ifdef DEBUG
				std::string functions = "";
				functions += string(T::lGetMetatable()) + "\n";
				for each(const auto f in fields)
					functions += "\t" + std::string(f.name) + "\n";
				error.reportMessage(functions);
#endif
				saveMetatable<T>(L, fields);
			}

		public:
			template<typename T>
			static int lDelete(lua_State* L){ 
				auto p = (T**)lua_touserdata(L, 1); 
				delete *p;
				*p = nullptr;
				return 0;
			}

			LuaMetatableFactory(lua_State* L){

				defineMetatable<ScriptGame>(L);

				// Components

				defineMetatable<ActiveState>(L);
				defineMetatable<Area>(L);
				defineMetatable<CGUID>(L);
				defineMetatable<CScriptable>(L);
				defineMetatable<LuaCallback>(L);
				defineMetatable<Name>(L);
				defineMetatable<Position>(L);

				// Game Objects

				defineMetatable<Scene>(L);
				defineMetatable<Entity>(L);
				defineMetatable<Map>(L);
				defineMetatable<MapSection>(L);
				defineMetatable<TileType>(L);

				// GUI

				defineMetatable<GUIButton>(L);
				defineMetatable<GUICollapsibleMenu>(L);
				defineMetatable<GUIContainer>(L);
				defineMetatable<GUIDropDownMenu>(L);
				defineMetatable<GUIEntity>(L);
				defineMetatable<GUILabel>(L);
				defineMetatable<GUIMenuBar>(L);
				defineMetatable<GUISlider>(L);
				defineMetatable<GUIText>(L);
				defineMetatable<GUIContext>(L);
				defineMetatable<GUIWindow>(L);
				 

				defineMetatable<EventHandler>(L);
				defineMetatable<MouseWheel>(L);
				defineMetatable<MouseMotion>(L);
				defineMetatable<MouseButton>(L);
				defineMetatable<KeyboardEvent>(L); 

				// IO

				// Graphics

				defineMetatable<Sprite>(L);
				defineMetatable<AnimatedSprite>(L);
				defineMetatable<SpriteManager>(L);
				defineMetatable<SpriteBatcher>(L);
				defineMetatable<Renderer>(L);

				// Containers
				 
				// Scene

				defineMetatable<StateStack>(L);
				defineMetatable<GameState>(L);

				// Font

				defineMetatable<TextRenderer>(L);
				   
			} 
		};
	}
}