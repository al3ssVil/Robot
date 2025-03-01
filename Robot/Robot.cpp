#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stack>

class Robot
{
private:
	int m_rows, m_columns, ** m_matrix;
public:
	void ReadMatrix()
	{
		std::ifstream f("map.txt");
		f >> m_rows >> m_columns;
		m_matrix = new int* [m_rows];
		for (int i = 0; i < m_rows; i++)
			m_matrix[i] = new int[m_columns];
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_columns; j++)
				f >> m_matrix[i][j];
		f.close();
	}
	int Random()
	{
		uint8_t x = rand() % 4;
		return x;
	}
	void Move_left(int& points, int& k, std::stack<std::pair<int, int>>& stack, std::pair<int, int>& robot)
	{
		while (robot.second - 1 > 0 && m_matrix[robot.first][robot.second - 1] != -1 && k != 0)
		{
			robot.second--;
			stack.push(robot);
			k--;
			points++;
		}
		if (m_matrix[robot.first + 1][robot.second] != -1 && k != 0)
			Move_down(points, k, stack, robot);
		else
			if (m_matrix[robot.first - 1][robot.second] != -1 && k != 0)
				Move_up(points, k, stack, robot);
	}
	void Move_down(int& points, int& k, std::stack<std::pair<int, int>>& stack, std::pair<int, int>& robot)
	{
		while (robot.first + 1 < m_rows - 1 && m_matrix[robot.first + 1][robot.second] != -1 && k != 0)
		{
			robot.first++;
			stack.push(robot);
			k--;
			points++;
		}
		if (m_matrix[robot.first][robot.second + 1] != -1 && k != 0)
			Move_right(points, k, stack, robot);
		else
			if (m_matrix[robot.first][robot.second - 1] != -1 && k != 0)
				Move_up(points, k, stack, robot);
	}
	void Move_right(int& points, int& k, std::stack<std::pair<int, int>>& stack, std::pair<int, int>& robot)
	{
		while (robot.second + 1 < m_columns - 1 && m_matrix[robot.first][robot.second + 1] != -1 && k != 0)
		{
			robot.second++;
			stack.push(robot);
			k--;
			points++;
		}
		if (m_matrix[robot.first - 1][robot.second] != -1 && k != 0)
			Move_down(points, k, stack, robot);
		else
			if (m_matrix[robot.first + 1][robot.second] != -1 && k != 0)
				Move_up(points, k, stack, robot);
	}
	void Move_up(int& puncte, int& k, std::stack<std::pair<int, int>>& stiva, std::pair<int, int>& robot)
	{
		while (robot.first - 1 > 0 && m_matrix[robot.first - 1][robot.second] != -1 && k != 0)
		{
			robot.first--;
			stiva.push(robot);
			k--;
			puncte++;
		}
		if (m_matrix[robot.first][robot.second - 1] != -1 && k != 0)
			Move_down(puncte, k, stiva, robot);
		else
			if (m_matrix[robot.first][robot.second + 1] != -1 && k != 0)
				Move_up(puncte, k, stiva, robot);

	}
	void Path(std::stack<std::pair<int, int>>& stack, int fuel)
	{
		std::pair<int, int> robot = { m_rows / 2, m_columns / 2 };
		std::cout << "The robot is at the positions: " << robot.first << ' ' << robot.second << std::endl;
		int points = 0, half_fuel = fuel / 2;
		stack.push({ m_rows / 2, m_columns / 2 });
		uint8_t direction = Random();
		if (direction == 0)
		{
			std::cout << "It goes to the left\n";
			Move_left(points, half_fuel, stack, robot);
		}
		else
			if (direction == 1)
			{
				std::cout << "It goes down\n";
				Move_down(points, half_fuel, stack, robot);
			}
			else
				if (direction == 2)
				{
					std::cout << "It goes right\n";
					Move_right(points, half_fuel, stack, robot);
				}
				else
				{
					std::cout << "It goes up\n";
					Move_up(points, half_fuel, stack, robot);
				}
		std::cout << "Points: " << points << '\n';
		std::cout << "The path is: " << std::endl;
		while (!stack.empty())
		{
			std::cout << stack.top().first << ' ' << stack.top().second << '\n';
			stack.pop();
		}
		std::cout << std::endl;
	}
};

int main()
{
	srand(time(NULL));
	Robot  robot;
	int fuel;
	std::stack<std::pair<int, int>> stack;
	robot.ReadMatrix();
	std::cout << "It will make 3 demonstrations, as the robot chooses a random direction initially. This way, you can visualize multiple possible paths." << std::endl;
	std::cout << "Enter the fuel amount for simulation: ";
	std::cin >> fuel;
	for (int i = 0; i < 3; i++)
	{
		robot.Path(stack, fuel);
	}
	return 0;
}