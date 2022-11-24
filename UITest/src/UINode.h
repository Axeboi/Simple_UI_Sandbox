#pragma once

#include "common.h"
#include "Observer.h"

static int id_generator = 1;

class UINode : public Observer
{	

	std::unordered_map<std::string, size_t> item_pointers;
	std::vector<UINode> items;

public:
	enum class DRAW_TYPE
	{
		RECT,
		TEXT
	};

	int id;
	std::string name;
	olc::vf2d pos;
	olc::vf2d halfsize;
	olc::Pixel color;
	DRAW_TYPE draw_type = DRAW_TYPE::RECT;

	UINode();
	UINode(const std::string& name);
	UINode& operator[] (const std::string& name);

	bool collides(const olc::vf2d&);
	void draw_self(olc::PixelGameEngine&);
	std::string to_string();
};

UINode::UINode()
{
	name		= "root";
	pos			= { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	halfsize	= { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	color		= olc::WHITE;
	id			= id_generator++;
}

UINode::UINode(const std::string& name)
{
	this->name = name;
	this->id = id_generator++;
}

UINode&
UINode::operator[] (const std::string& name)
{
	if (item_pointers.count(name) == 0)
	{
		item_pointers[name] = items.size();
		items.push_back(UINode(name));
	}
	
	return items[item_pointers[name]];
}

bool
UINode::collides(const olc::vf2d& other_pos)
{
	bool found_collision = false;
	for (auto& node : items)
	{
		if (node.draw_type == DRAW_TYPE::TEXT)
			continue;

		found_collision = node.collides(other_pos);
		if (found_collision == true)
			break;
	}
	
	if (found_collision == true)
		return true;

	if (abs(pos.x - other_pos.x) > (halfsize.x + 1)) return false;
	if (abs(pos.y - other_pos.y) > (halfsize.y + 1)) return false;

	std::ostringstream ss;
	ss << id;
	set_state(ss.str());

	return true;
}

void
UINode::draw_self(olc::PixelGameEngine& pge)
{
	if (draw_type == DRAW_TYPE::TEXT)
	{
		//pge.DrawString(pos, "1", olc::BLACK);
		pge.DrawString(pos, current_event, olc::BLACK);
	}
	else
	{
		pge.FillRect(pos - halfsize, halfsize * 2, color);
	}
		
	for (auto& node : items)
		node.draw_self(pge);
}

std::string
UINode::to_string()
{
	return name;
}
