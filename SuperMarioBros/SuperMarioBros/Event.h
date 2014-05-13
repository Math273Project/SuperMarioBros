#pragma once
#include "Object.h"

enum EventType
{
	KEEP_MOVING_Y,
	START_MOVING_X,
	KEEP_NOT_PASSABLE,
	DESTROY,
	KEEP_LOSE_CONTROL,
};

class Event
{
public:
	Event(EventType type, Object* pObject, long long startTime, int time, double param)
	{	
		type_ = type;
		pObject_ = pObject;
		startTime_ = startTime;
		time_ = time;
		param_ = param;
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
	long long getTime() const
	{
		return time_;
	}
	int getParam() const
	{
		return param_;
	}
	void setStartTime(long long startTime)
	{
		startTime_ = startTime;
	}
	void setTime(int time)
	{
		time_ = time;
	}
	void setParam(int param)
	{
		param_ = param;
	}
protected:
	EventType type_;
	Object* pObject_;
	long long startTime_;
	int time_;
	double param_;
};