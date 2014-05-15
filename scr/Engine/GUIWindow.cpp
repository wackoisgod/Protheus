#include "GUIWindow.h"


using namespace Pro;
using namespace GUI;

GUIWindow::GUIWindow()
{
}


GUIWindow::~GUIWindow()
{
}


GUIEvent* GUIWindow::update(SDL_Event mouse_event){ 
	for each(auto entities in window_entities){
		if (entities->enabled()){ 
			switch (entities->type){
			case GUI_ENTITY_TYPE::COLLAPSIBLE_MENU:
				if ((GUICollapsibleMenu*)entities->isClickWithin(mouse_event.button)){
					return ((GUICollapsibleMenu*)entities)->update(mouse_event);
				}
				break;
			 default:
				 if (entities->isClickWithin(mouse_event.button)){
					 entities->callback();
					 return entities->generateEvent(); 
				 }
				break;
			}
		}
	} 
	return nullptr;
}