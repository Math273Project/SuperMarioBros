#include <Windows.h>


class Timer
{
public:
	Timer();
	~Timer();
	void reset();
	double operator () () const;
protected:
	LARGE_INTEGER startTime_;
};