#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <algorithm>
using namespace std;

constexpr unsigned int window_width = 800;
constexpr unsigned int window_height = 600;
constexpr unsigned int data_point_count = 100;

constexpr int height_multiplier = window_height / data_point_count;
int last_moved_index = -1;

enum Sort_Result
{
	INORDER,
	NOTINORDER
};

void populate_data(vector<int> &data, int amount=data_point_count)
{
	for (int i = 0; i < amount; i++)
	{
		data.push_back(i);
	}
	random_shuffle(data.begin(), data.end());
}

Sort_Result sort_one(vector<int> &data)
{
	for (int i = 0; i < data.size(); i++) 
	{
		if (i == data.size() - 1)
		{
			return INORDER;
		}
		int val = data[i];
		if (data[i + 1] < val)
		{
			last_moved_index = i;
			iter_swap(data.begin() + i, data.begin() + i + 1);
			return NOTINORDER;
		}
	}
}

void draw(sf::RenderWindow &window, vector<int> data, Sort_Result solved)
{
	float individual_width = window_width / data.size(); //800 = 800 / 100 = 8px per line

	for (int i = 0; i < data.size(); i++)
	{
		int value = data[i];

		sf::RectangleShape rs(sf::Vector2f(individual_width, -(value * height_multiplier)));
		rs.setPosition(sf::Vector2f(i * individual_width, window_height));
		if(solved == INORDER)
			rs.setFillColor(sf::Color::Green);
		else
			rs.setFillColor((last_moved_index == i) ? sf::Color::Red : sf::Color::White);
		window.draw(rs);
	}

}

int main(int argc, char **argv)
{
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Hello SFML!");

	vector<int> data;

	populate_data(data);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		draw(window, data, sort_one(data));

		window.display();
	}

	return 0;
}