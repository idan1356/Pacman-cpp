#include "ghost.h"


stack<Position> Ghost::findPath(const Position& pacman, const Map& map) const {
	A_Node* arr[DEFAULT_MAP_LENGTH][DEFAULT_MAP_WIDTH]{};
	priority_queue<A_Node*, vector<A_Node*>, CustomCompare> open;
	A_Node* curNode = nullptr;
	Position curPos = getPosition();
	A_Node* curNeighbor = nullptr;

	arr[curPos.getY()][curPos.getX()] = new A_Node(curPos);
	curNode = arr[curPos.getY()][curPos.getX()];
	open.push(curNode);

	while (!open.empty()) {
		curNode = open.top();
		open.pop();
		curNode->setClose();
//		curNode->getPosition().draw('*', Color::RED);
		if (curNode->getPosition().isEqual(pacman))
			break;

		for (int i = 0; i < 4; i++) {
			curPos = curNode->getPosition();
			curPos.advance(Direction(i));

			curNeighbor = arr[curPos.getY()][curPos.getX()];

			if (map.isPassable(curPos) && map.isInBounds(curPos)) {
				if (curNeighbor == nullptr) {
					delete[] arr[curPos.getY()][curPos.getX()];
					arr[curPos.getY()][curPos.getX()] = new A_Node(*curNode, curPos, pacman);
					curNeighbor = arr[curPos.getY()][curPos.getX()];
				}
				else if (curNeighbor->getIsOpen())
					curNeighbor->update_Node(*curNode, pacman);
				else
					continue;

				if (!curNeighbor->getIsOpen()) {
					open.push(curNeighbor);
					curNeighbor->setOpen();
//					curNeighbor->getPosition().draw('*', Color::GREEN);
				}
			}
		}
	}

	stack<Position> stack;
	while (curNode != nullptr) {
//		curNode->getPosition().draw('*', getColor());
		stack.push(curNode->getPosition());
		curNode = curNode->getParent();
	}


	for (int i = 0; i < DEFAULT_MAP_LENGTH - 1; i++)
		for (int j = 0; j < DEFAULT_MAP_WIDTH - 1; j++) {
			delete arr[i][j];
		}

	return stack;
}

void Ghost::move(Map& map, int i, Difficulty& difficulty, const Position& pacman, Logger& log) {
	int sample;

	switch (difficulty) {
	case Difficulty::BEST:
		sample = 5;
		break;
	case Difficulty::GOOD:
		sample = 10;
		break;
	}

	if ((rand() % sample) == 0) {
		findPath(pacman, map);
	}

	if (!path.empty() && difficulty != Difficulty::NOVICE) {
		try {
			Direction dir = getDirectionFromStack(getPosition(), path.top());
			setDirection(dir);
			moveObject(map);
			log.logToStep("ghost " + to_string(i) + " moved " + dirToStr(dir));
			path.pop();
		}
		catch (exception) {
			path.empty();
			moveNovice(map, log, i);
		}
	}

	else
		moveNovice(map, log, i);
}


Direction Ghost::getDirectionFromStack(const Position& ghost, const Position& stack) {
	int x = ghost.getX() - stack.getX();
	int y = ghost.getY() - stack.getY();

	if (x == 1 && y == 0)
		return Direction::LEFT;
	else if (x == -1 && y == 0)
		return Direction::RIGHT;
	else if (x == 0 && y == 1)
		return Direction::UP;
	else if (x == 0 && y == -1)
		return Direction::DOWN;
	else
		throw exception("invalid stack position");
}