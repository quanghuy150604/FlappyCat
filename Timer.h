#pragma once

class Timer
{
public:
	
	Timer();
	
	void start();
	
	void stop();
	
	void pause();
	
	void unpause();
	
	int get_ticks();
	
	bool is_started();
	
	bool is_paused();

private:
	
	int start_tick_;
	int paused_ticks;
	bool is_paused_;
	bool is_started_;
};
