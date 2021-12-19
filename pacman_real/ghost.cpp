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
//		curNode->getPosition().draw('*', RED);
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
//					curNeighbor->getPosition().draw('*', GREEN);
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