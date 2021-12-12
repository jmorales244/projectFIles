#include "Collision.hpp"
#include "ECS.hpp"
#include "ColliderComponent.hpp"
//The AABB Collision method
//The method creates a box that represents the location and size of the boxes that surround each item/player
//If the location of one player are equal or greater than it will detect that it is colliding or not 
bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		return true;
	}

	return false;
}

//Adjusting collision 
bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		std::cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}
