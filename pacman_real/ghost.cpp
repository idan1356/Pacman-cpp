#include "ghost.h"


stack<Position> Ghost::findPath(Position pacman, Map& map) {
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
		curNode->getPosition().draw('*', RED);
		if (curNode->getPosition().isEqual(pacman))
			break;

		for (int i = 0; i < 4; i++) {
			curPos = curNode->getPosition();
			curPos.advance(Direction(i));
			curNeighbor = arr[curPos.getY()][curPos.getX()];
			if (map.isPassable(curPos) && map.isInBounds(curPos)) {
				if (curNeighbor == nullptr) {
					curNeighbor = new A_Node(*curNode, curPos, pacman);
				}
				else if (curNeighbor->getIsOpen())
					curNeighbor->update_Node(*curNode, pacman);
				else
					continue;

				if (!curNeighbor->getIsOpen()) {
					open.push(curNeighbor);
					curNeighbor->setOpen();
					curNeighbor->getPosition().draw('*', GREEN);
				}
			}
		}
	}

	stack<Position> stack;
	while (curNode != nullptr) {
		curNode->getPosition().draw('*', WHITE);
		stack.push(curNode->getPosition());
		curNode = curNode->getParent();
	}


	for (int i = 0; i < DEFAULT_MAP_LENGTH - 1; i++)
		for (int j = 0; j < DEFAULT_MAP_WIDTH - 1; j++) {
				delete[] arr[i][j];
		}

	return stack;
}


void Ghost::moveBest(Map& map, Position pacman, int counter) {
	static stack<Position> stack;

	if (counter % 50 == 0) 
		stack = findPath(pacman, map);

	if (!stack.empty()) {
		teleportObject(stack.top(), map);
		stack.pop();
	}
	else
		moveNovice(map);

}

stack<Position> Ghost::findPathV2(Position pacman, Map& map) {
	A_Node arr[DEFAULT_MAP_LENGTH][DEFAULT_MAP_WIDTH];
	priority_queue<A_Node, vector<A_Node>, CustomCompare> open;
	A_Node curNode;
	Position curPos = getPosition();
	A_Node curNeighbor;

	arr[curPos.getY()][curPos.getX()] = A_Node(curPos);
	curNode = arr[curPos.getY()][curPos.getX()];
	open.push(curNode);

	while (!open.empty()) {
		curNode = open.top();
		open.pop();
		curNode.setClose();
		curNode.getPosition().draw('*', RED);
		if (curNode.getPosition().isEqual(pacman))
			break;

		for (int i = 0; i < 4; i++) {
			curPos = curNode.getPosition();
			curPos.advance(Direction(i));
			curNeighbor = arr[curPos.getY()][curPos.getX()];
			if (map.isPassable(curPos) && map.isInBounds(curPos)) {
				if (curNeighbor == nullptr) {
					curNeighbor = A_Node(curNode, curPos, pacman);
				}
				else if (curNeighbor.getIsOpen())
					curNeighbor.update_Node(curNode, pacman);
				else
					continue;

				if (!curNeighbor.getIsOpen()) {
					open.push(curNeighbor);
					curNeighbor.setOpen();
					curNeighbor.getPosition().draw('*', GREEN);
				}
			}
		}
	}

	stack<Position> stack;
	while (curNode.getParent() != nullptr) {
		curNode.getPosition().draw('*', WHITE);
		stack.push(curNode.getPosition());
		curNode = *curNode.getParent();
	}

	return stack;
}