// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	Font font;
	font.loadFromFile("ARIAL.ttf");
	Text shape("Pick a number between 3-9 for the number of sides you want for the shape", font, 20);
	Text pick_points("Press Y if you want a reguler shape then left click one time for its center and another for the distance between center and vertices and once more for the start of the fractal \n If you want a non regular shape left click where you want all the vertices and click once more for the start of the fractal", font, 20);
	Text Points_gen("Choose how you want points generated \n 0) All possible generated points are generated \n 1) points are generated by random vertices", font, 20);
	vector<Vector2f> vertices;
	vector<Vector2f> points;
	int count = 1;
	int iter = 0;
	double MultFactor;
	int Shape_num = 0;
	double angle;
	vector<Vector2f> RegularShape;
	bool Y = false;
	int Fractal_gen = -1;

	while (window.isOpen())
	{
		window.setFramerateLimit(10);
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Y) && Shape_num != 0)
			{
				Y = true;
			}
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Num3))
			{
				Shape_num = 3;
				MultFactor = 0.5;
				angle = 2.0944;
			}
			if (Keyboard::isKeyPressed(Keyboard::Num4))
			{
				Shape_num = 4;
				MultFactor = 0.66666667;
				angle = 1.5708;
			}
			if (Keyboard::isKeyPressed(Keyboard::Num5))
			{
				Shape_num = 5;
				MultFactor = 0.618;
				angle = 1.25664;
			}
			if (Keyboard::isKeyPressed(Keyboard::Num6))
			{
				Shape_num = 6;
				MultFactor = 0.6666666667;
				angle = 1.0472;
			}
			if (Keyboard::isKeyPressed(Keyboard::Num7))
			{
				Shape_num = 7;
				MultFactor = 0.692;
				cout << Shape_num << endl;
				angle = 0.8975979;
			}
			if (Keyboard::isKeyPressed(Keyboard::Num8))
			{
				Shape_num = 8;
				MultFactor = 0.70710678;
				angle = 0.785398;
			}
			if (Keyboard::isKeyPressed(Keyboard::Num9))
			{
				Shape_num = 9;
				MultFactor = 0.742;
				angle = 0.698132;
			}
			if (Keyboard::isKeyPressed(Keyboard::Num0) && points.size() == 1)
			{
				Fractal_gen = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Num1) && points.size() == 1)
			{
				Fractal_gen = 1;
			}
			if (event.type == sf::Event::MouseButtonPressed && Shape_num != 0)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					if (RegularShape.size() < 2 && Y)
					{
						RegularShape.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						if (RegularShape.size() == 2)
						{
							double magnitude = sqrt(pow(RegularShape[0].x - RegularShape[1].x, 2) + pow(RegularShape[0].y - RegularShape[1].y, 2));
							for (int i = 0; i < Shape_num; i++)
							{
								vertices.push_back(Vector2f(RegularShape[0].x + (magnitude * cos(angle * (i + 1))), RegularShape[0].y + (magnitude * sin(angle * (i + 1)))));
								cout << vertices[i].x << " " << vertices[i].y << endl;
							}
						}
					}
					else if (vertices.size() < Shape_num)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (points.size() == 0)
					{
						///fourth click
						///push back to points vector
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						cout << "First point added!" << endl;
					}
				}
			}
		}
		

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (Fractal_gen == 0 && points.size() > 0 && points.size() < 10000)
		{
			///generate more point(s)
			///select random vertex
			///calculate midpoint between random vertex and the last point in the vector
			///push back the newly generated coord.
			for (int i = (count - pow(3, iter)); i <= count; i++)
			{
				for (int j = 0; j < vertices.size(); j++)
				{
					points.push_back(Vector2f(points[i].x + (vertices[j].x - points[i].x) * MultFactor, points[i].y + (vertices[j].y - points[i].y) * MultFactor));
				}
				

			}
			iter++;
			count += pow(3, iter);
		}
		if (Fractal_gen == 1 && points.size() > 0 && points.size() < 10000)
		{
			int start_point = points.size();
			srand(count);
			for (int i = 0; i < 100; i++)
			{
				int vert_rand = rand() % Shape_num;
				points.push_back(Vector2f(points[start_point - 1 + i].x + (vertices[vert_rand].x - points[start_point - 1 + i].x) * MultFactor, points[start_point - 1 + i].y + (vertices[vert_rand].y - points[start_point - 1 + i].y) * MultFactor));
				
			}
			count++;
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		if(Shape_num == 0)
		{ 
			window.draw(shape);
		}
		if(Shape_num != 0 && points.size() == 0)
		{
			window.draw(pick_points);
		}
		if (Shape_num != 0 && points.size() == 1)
		{
			window.draw(Points_gen);
		}
		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(1, 1));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}
		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape rect(Vector2f(1, 1));
			rect.setPosition(Vector2f(points[i].x, points[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}
		window.display();
	}
}