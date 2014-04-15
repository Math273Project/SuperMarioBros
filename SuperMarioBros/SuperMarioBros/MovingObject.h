#include "Object.h"

class MovingObject : public Object
{
public:
	MovingObject(int id, int x, int y, int vx, int vy);
	double getvx() const;
	double getvy() const;
	Direction getFacingDirection() const;
	void setvx(double vx); // will callsetFacingDirection if the direction of velocity changes;
	void setvy(double vy);
	bool moveable() const override;
	void setFacingDirection(Direction facingDirection);
	void move(int time);
protected:
	double vx_; // unit: pixel / second
	double vy_;
	Direction facingDirection_;
};