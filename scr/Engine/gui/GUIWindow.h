/*************************************************************************
Protheus Source File.
Copyright (C), Protheus Studios, 2013-2014.
-------------------------------------------------------------------------

Description:

-------------------------------------------------------------------------
History:
- 20:05:2014: Waring J.
*************************************************************************/

#pragma once
#include <SDL_rect.h>
#include <SDL_events.h>
#include <vector> 
#include "GUIButton.h"
#include "GUISlider.h" 
#include "GUIText.h"  
#include "GUIContainer.h"
#include "GUICollapsibleMenu.h"
#include "GUIMenuBar.h"

namespace Pro{
	namespace GUI{
		class GUIWindow : 
			public GUIContainer
		{
		private: 
			// Titles bar for drop down menus
			bool hasMenuBar;
			GUIMenuBar* menu_bar;

		public:
			GUIWindow(const std::string& name);
			GUIWindow();
			~GUIWindow();
			 
			void attachMenuBar(GUIMenuBar* component);


			// returns the Metatable's name assosiated with this object
			static string lGetMetatable(){
				return "gui_window_metatable";
			}
		};
	}
}