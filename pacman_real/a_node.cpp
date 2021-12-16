#include "a_node.h"


A_Node::A_Node(A_Node& adjNode, Position nodePos, Position targetPos) :parent(&adjNode), pos(nodePos) {
	gCost = adjNode.getgCost() + 1;
	hCost = abs(targetPos.getX() - pos.getX()) + abs(targetPos.getY() - pos.getY());
	fCost = gCost + hCost;
}

void A_Node::update_Node(A_Node& adjNode, Position targetPos) {
	A_Node temp(adjNode, pos, targetPos);
	if (temp.getfCost() < fCost) {
		gCost = temp.getgCost();
		hCost = temp.gethCost();
		fCost = temp.getfCost();
		parent = &adjNode;
	}
}