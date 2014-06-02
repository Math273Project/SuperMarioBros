#pragma once
#include "Object.h"

enum EventType
{
	KEEP_MOVING_Y,
	START_MOVING_X,
	START_MOVING_Y,
	KEEP_NOT_PASSABLE,
	DESTROY,
	KEEP_LOSE_CONTROL,
	START_MOVING_X_CENTERX,
	KEEP_MARIO_INVISIBLE,
};

class Event
{
public:
	Event(EventType type, Object* pObject, long long startTime, double wParam, double lParam)
	{	
		type_ = type;
		pObject_ = pObject;
		startTime_ = startTime;
		wParam_ = wParam;
		lParam_ = lParam;
	}
	Object* getObject() const
	{
		return pObject_;
	}
	EventType getType() const
	{
		return type_;
	}
	long long getStartTime() const
	{
		return startTime_;
	}
	long long getwParam() const
	{
		return wParam_;
	}
	int getlParam() const
	{
		return lParam_;
	}
	void setStartTime(long long startTime)
	{
		startTime_ = startTime;
	}
	void setwParam(int wParam)
	{
		wParam_ = wParam;
	}
	void setlParam(int lParam)
	{
		lParam_ = lParam;
	}
protected:
	EventType type_;
	Object* pObject_;
	long long startTime_;
	double wParam_;
	double lParam_;
};
