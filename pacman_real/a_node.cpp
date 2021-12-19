#include "a_node.h"

// gCost- distancec of node from parent, hCost- distance of node from target position
A_Node::A_Node(A_Node& adjNode, const Position& nodePos, const Position& targetPos) : parent(&adjNode), pos(nodePos) {
	gCost = adjNode.getgCost() + 1;
	hCost = abs(targetPos.getX() - pos.getX()) + abs(targetPos.getY() - pos.getY());
	fCost = gCost + hCost;
}

//updates node according to adjacent node, when required
void A_Node::update_Node(A_Node& adjNode, const Position& targetPos) {
	A_Node temp(adjNode, pos, targetPos);
	if (temp.getfCost() < fCost) {
		gCost = temp.getgCost();
		hCost = temp.gethCost();
		fCost = temp.getfCost();
		parent = &adjNode;
	}
}