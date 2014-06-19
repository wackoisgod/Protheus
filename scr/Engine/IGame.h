/*************************************************************************
Protheus Source File.
Copyright (C), Protheus Studios, 2013-2014.
-------------------------------------------------------------------------

Description:
	Provides a interface for the engine to have two classes, one for
	game mode and script mode
-------------------------------------------------------------------------
History:
- 19:06:2014 Waring J.

*************************************************************************/
#pragma once
 
namespace Pro{ 
	class IGame{ 
		// performs any specified updates
		virtual int update() = 0;
		// renders to the screen
		virtual int render() = 0;
		// performs any initialization required
		virtual int initialize() = 0;
		// cleans up the system
		virtual int cleanup() = 0;
	};
}