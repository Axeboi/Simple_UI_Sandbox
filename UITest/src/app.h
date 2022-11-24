#pragma once

#define OLC_PGE_APPLICATION

#include "common.h"
#include "olcPixelGameEngine.h"
#include "UINode.h"
#include "Observer.h"

class App : public olc::PixelGameEngine
{
private:
	Dispatcher dispatcher;
	UINode root;
public:
	App()
	{
		sAppName = "UI and Event Playground";
	}

public:
	bool OnUserCreate() override
	{
		UINode& button_one = root["Button One"];
		button_one.pos = root.pos - olc::vf2d{100 ,0};
		button_one.halfsize = { 50, 50 };
		button_one.color = olc::GREEN;

		UINode& text_square_one = root["Button One"]["Text"];
		text_square_one.pos = button_one.pos;
		text_square_one.halfsize = { 10, 10 };
		text_square_one.color = olc::RED;
		text_square_one.draw_type = UINode::DRAW_TYPE::TEXT;

		UINode& button_two = root["Button Two"];
		button_two.pos = root.pos + olc::vf2d{ 100 ,0 };
		button_two.halfsize = { 50, 50 };
		button_two.color = olc::GREEN;

		UINode& text_square_two = root["Button Two"]["Text"];
		text_square_two.pos = button_two.pos;
		text_square_two.halfsize = { 10, 10 };
		text_square_two.color = olc::RED;
		text_square_two.draw_type = UINode::DRAW_TYPE::TEXT;

		dispatcher.attach(&root);
		dispatcher.attach(&root["Button One"]);
		dispatcher.attach(&root["Button Two"]);
		dispatcher.attach(&root["Button One"]["Text"]);
		dispatcher.attach(&root["Button Two"]["Text"]);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetMouse(0).bPressed)
		{
			olc::vf2d mouse_pos { (float)GetMouseX(), (float)GetMouseY() };
			root.collides(mouse_pos);
		}
			
		dispatcher.update();
		root.draw_self(*this);
		return true;
	}
};

int main()
{
	if (true)
	{
		App app;
		if (app.Construct(640, 400, 2, 2))
			app.Start();
	}

	return 0;
}
