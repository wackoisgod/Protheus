#include "GUIContainer.h"
namespace Pro{
	namespace GUI{ 
		GUIContainer::GUIContainer(const std::string& name) : GUIEntity(name){}
		GUIContainer::GUIContainer(){}
		GUIContainer::~GUIContainer(){}
		 
		void GUIContainer::addComponent(GUIEntity* e){ 
			window_entities.push_back(e);
		}

		void GUIContainer::update(SDL_Event mouse_event){
			for each(auto entities in window_entities){
				if (entities->isActive()){
					switch (entities->type){
					case GUI_ENTITY_TYPE::COLLAPSIBLE_MENU:
						if (static_cast<GUIContainer*>(entities)->isClickWithin(mouse_event.button))
							static_cast<GUIContainer*>(entities)->update(mouse_event);
						break;
					default:
						if (entities->isClickWithin(mouse_event.button))
							entities->callback();
						break;
					}
				}
			}
			// Call the containers callback
			callback();
		}


		int GUIContainer::lAddComponent(lua_State* L){
			GUIContainer* p = *static_cast<GUIContainer**>(lua_touserdata(L, 1));
			p->addComponent(*static_cast<GUIEntity**>(lua_touserdata(L, 2)));
			return 0;
		}
	}
}