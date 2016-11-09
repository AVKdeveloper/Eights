#ifndef POSITION
#define POSITION

#include <array>
#include <set>
#include <queue>
#include <string>
#include <list>

#define FieldSize 3

class Position
{
public:
	std::array<int, FieldSize*FieldSize> numerics;
public:
	Position* previous;
	char wayOfCreating;
public:
	Position(const std::array<int, FieldSize*FieldSize>& Numerics);
	bool is_solvable() const;
	bool is_solved() const;
	int nullPos() const;
	std::string bfs();
	bool operator<(const Position& otherPosition) const;
};

Position::Position(const std::array<int, 9>& Numerics)
{
	for (int i = 0; i < FieldSize*FieldSize; ++i)
	{
		numerics[i] = Numerics[i];
	}
	previous = nullptr;
}

std::string Position::bfs()
{
	previous = nullptr;
	std::queue<Position*> queue_of_ptr_to_positions;
	std::list<Position> list_of_generated_positions; // список для хранения генерированных позиций
	list_of_generated_positions.push_back(*this);
	queue_of_ptr_to_positions.push(&(*list_of_generated_positions.begin()));
	std::set<Position> set_of_visited_positions;
	set_of_visited_positions.insert(*this);
	std::string str = "";
	while (!queue_of_ptr_to_positions.empty())
	{
		Position & currentPos = *queue_of_ptr_to_positions.front();
		queue_of_ptr_to_positions.pop();
		if (currentPos.is_solved())
		{
			Position tempPos(currentPos);
			while (tempPos.previous != nullptr)
			{
				str = str + tempPos.wayOfCreating;
				tempPos = (*tempPos.previous);
			}
			std::reverse(str.begin(), str.end());
			break;
		}
		else
		{
			if (currentPos.nullPos() % FieldSize > 0) // можем ли пойти влево
			{
				Position newPosition(currentPos);
				newPosition.previous = &currentPos;
				newPosition.wayOfCreating = 'L';

				auto nullPosition = currentPos.nullPos();
				auto tmp = newPosition.numerics[nullPosition];
				newPosition.numerics[nullPosition] = newPosition.numerics[nullPosition - 1];
				newPosition.numerics[nullPosition - 1] = tmp;

				if (set_of_visited_positions.find(newPosition) == set_of_visited_positions.end())
				{
					list_of_generated_positions.push_back(newPosition);
					set_of_visited_positions.insert(newPosition);
					queue_of_ptr_to_positions.push(&(*(list_of_generated_positions.rbegin())));
				}
			}
			if (currentPos.nullPos() % FieldSize < FieldSize-1) // можем ли пойти направо
			{
				Position newPosition(currentPos);
				newPosition.previous = &currentPos;
				newPosition.wayOfCreating = 'R';

				auto nullPosition = currentPos.nullPos();
				auto tmp = newPosition.numerics[nullPosition];
				newPosition.numerics[nullPosition] = newPosition.numerics[nullPosition + 1];
				newPosition.numerics[nullPosition + 1] = tmp;

				if (set_of_visited_positions.find(newPosition) == set_of_visited_positions.end())
				{
					list_of_generated_positions.push_back(newPosition);
					set_of_visited_positions.insert(newPosition);
					queue_of_ptr_to_positions.push(&(*(list_of_generated_positions.rbegin())));
				}
			}
			if (currentPos.nullPos() / FieldSize > 0) // можем ли пойти вверх
			{
				Position newPosition(currentPos);
				newPosition.previous = &currentPos;
				newPosition.wayOfCreating = 'U';

				auto nullPosition = currentPos.nullPos();
				auto tmp = newPosition.numerics[nullPosition];
				newPosition.numerics[nullPosition] = newPosition.numerics[nullPosition - FieldSize];
				newPosition.numerics[nullPosition - FieldSize] = tmp;

				if (set_of_visited_positions.find(newPosition) == set_of_visited_positions.end())
				{
					list_of_generated_positions.push_back(newPosition);
					set_of_visited_positions.insert(newPosition);
					queue_of_ptr_to_positions.push(&(*(list_of_generated_positions.rbegin())));
				}
			}
			if (currentPos.nullPos() / FieldSize < FieldSize-1) // можем ли мы пойти вниз
			{
				Position newPosition(currentPos);
				newPosition.previous = &currentPos;
				newPosition.wayOfCreating = 'D';

				auto nullPosition = currentPos.nullPos();
				auto tmp = newPosition.numerics[nullPosition];
				newPosition.numerics[nullPosition] = newPosition.numerics[nullPosition + FieldSize];
				newPosition.numerics[nullPosition + FieldSize] = tmp;

				if (set_of_visited_positions.find(newPosition) == set_of_visited_positions.end())
				{
					list_of_generated_positions.push_back(newPosition);
					set_of_visited_positions.insert(newPosition);
					queue_of_ptr_to_positions.push(&(*(list_of_generated_positions.rbegin())));
				}
			}
		}
	}
	return str;
}

bool Position::is_solvable() const
{
	int quantityReplaces = 0;
	for(int i = 0; i < FieldSize*FieldSize; ++i)
		for (int j = i+1; j < FieldSize*FieldSize; ++j)
				if (numerics[i] > numerics[j])
					quantityReplaces++;
	quantityReplaces = quantityReplaces + (8 - this->nullPos());
	if (quantityReplaces % 2 == 0)
		return true;
	else
		return false;
}

bool Position::is_solved() const
{
	bool solved = true;
	if (numerics[FieldSize*FieldSize-1] != 0)
	{
		solved = false;
	}
	else
	{
		for (int i = 0; i < FieldSize*FieldSize-2; ++i)
		{
			if (numerics[i] != i+1)
			{
				solved = false;
				break;
			}
		}
	}
	return solved;
}

int Position::nullPos() const
{
	int position = 0;
	for (int i = 0; i < FieldSize*FieldSize; ++i)
	{
		if (numerics[i] == 0)
			position = i;
	}
	return position;
}

bool Position::operator<(const Position& otherPosition) const
{
	bool less = false;
	for (int i = 0; i < FieldSize*FieldSize; ++i)
	{
		if (numerics[i] < otherPosition.numerics[i])
		{
			less = true;
			break;
		}
		else
		{
			if (numerics[i] > otherPosition.numerics[i])
			{
				break;
			}
		}
	}
	return less;
}

#endif