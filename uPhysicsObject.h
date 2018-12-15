#pragma once
#include <memory>
#include "uTarget.h"
#include "uMath.h"
#include "SDL.h"
namespace utl
{

	class uPhysicsObject
	{
	public:

		inline uTarget *getTarget() { return _box; }
		inline void setXY(int x, int y) { _box->x = x; _box->y = y; }
		inline void setWH(int w, int h) { _box->w = w; _box->h = h; }
		inline void setCenter(int x, int y) { _box->x = x + _box->w / 2;  _box->y = y + _box->h / 2; }
		inline void setTarget(uTarget rect) { *_box = rect; }
		inline void setNewTarget(uTarget* rectToBind) { _box = rectToBind; }

		bool active=true; // inactive objects don't move but are still solid
		float mass=1;
		uVec2D velocity = { 0,0 };
		uVec2D acceleration = { 0,0 };
		uTarget* _box = nullptr; 

		uint8_t _id=0;
		uint8_t _groupId=0;
	private:
		

	};
}