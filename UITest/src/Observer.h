#pragma once

#include "common.h"
#include "olcPixelGameEngine.h"

//static int counter = 0;

//struct Event
//{
//	int id;
//	olc::vf2d event_pos;
//	std::string str;
//
//	void operator= (const Event& e)
//	{
//		id = e.id;
//		event_pos = e.event_pos;
//		str = e.str;
//	}
//};

struct Dispatcher;

struct Observer
{
	std::string current_event;
	Dispatcher* dispatcher = nullptr;

	Observer() 
	{
		current_event = "";
	}

	void set_state(std::string);
};

struct Dispatcher
{
	std::vector<Observer*> observers;
	std::string event;

	Dispatcher()
	{
		event = "";
	}
	void attach(Observer*);
	void update();
};

void
Observer::set_state(std::string event)
{
	dispatcher->event = event;
}

void
Dispatcher::attach(Observer* observer)
{
	observer->dispatcher = this;
	observers.push_back(observer);
}

void
Dispatcher::update()
{
	for (int i = 0; i < observers.size(); i++)
	{
		observers[i]->current_event = event;
	}
}
