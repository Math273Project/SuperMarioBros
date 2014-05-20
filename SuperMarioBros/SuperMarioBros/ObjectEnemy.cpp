#include "ObjectEnemy.h"

ObjectEnemy::ObjectEnemy(int x, int y, int vx, int vy) : MovingObject(x, y, vx, vy)
{
	width_ = ENEMY_WIDTH;
	height_ = ENEMY_HEIGHT;
}

void ObjectEnemy::collide(const Object& object, Direction collideDirection)
{
	if (collideDirection == NONE)
		return;
	
	switch (object.getType())
	{
	case BLOCK:
	case QUESTION_BLOCK:
	case FLOOR:
	case BRICK:
	case PIPE_BIG:
	case PIPE_MIDDLE:
	case PIPE_SMALL:
	case MUSHROOM_DYING:
	case ENEMY_DYING:
		adjustPosition(object, collideDirection);
		switch (collideDirection)
		{
		case UP:
			setvy(0);
			break;
		case DOWN:
			setvy(0);
			break;
		case LEFT:
			setvx(-vx_);
			break;
		case RIGHT:
			setvx(-vx_);
			break;
		}
		break;
		
	case MARIO_SMALL:
	case MARIO_BIG:
	case MARIO_SUPER:
		switch (collideDirection)
		{
		case DOWN:
			if (!dying_)
			{
				destroy(ENEMY_DYING_DURATION);
				changeType();			
			}
			break;
		}
		break;
	
	case TURTLE_SPIN:
		destroy();
		break;
	}
	
}

ObjectType ObjectEnemy::getType() const
{
	if (dying_)
		return ENEMY_DYING;
	return ENEMY;
}

int ObjectEnemy::getPriority() const
{
	return ENEMY_PRIORITY;
}

void ObjectEnemy::changeType()
{
	dying_ = true;
	width_ = ENEMY_DYING_WIDTH;
	height_ = ENEMY_DYING_HEIGHT;
	vx_ = 0;
	y_ += ENEMY_HEIGHT - ENEMY_DYING_HEIGHT;
}