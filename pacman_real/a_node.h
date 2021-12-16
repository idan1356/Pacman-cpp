#ifndef _A_NODE_H_
#define _A_NODE_H

#include "position.h"

class A_Node {
private:
	Position	pos;
	short int	gCost;
	short int	hCost;
	short int	fCost;
	bool		isOpen = false;
	A_Node*		parent = nullptr;

public:
	short int getgCost() const { return gCost; };
	short int gethCost() const { return hCost; };
	short int getfCost() const { return fCost; };

	bool getIsOpen() const { return isOpen; };
	Position getPosition() const { return pos; };
	A_Node* getParent() const { return parent; };

	void setClose() { isOpen = false; };
	void setOpen() { isOpen = true; };
	A_Node(A_Node& adjNode, Position nodePos, Position targetPos);
	A_Node(Position pos) : pos(pos), gCost(0), hCost(0), fCost(0) {};
	A_Node() : pos(Position(0,0)), gCost(0), hCost(0), fCost(0) {};

	bool operator > (const A_Node& node) const { return fCost > node.getfCost(); };


	void update_Node(A_Node& adjNode, Position targetPos);
};

struct CustomCompare {
	bool operator()(const A_Node* nodel, const A_Node* noder) {
		short int node1 = nodel->getfCost();
		short int node2 = noder->getfCost();
		if (nodel == noder)
			return nodel->gethCost() > noder->gethCost();
		else
			return nodel < noder;
	}
};

#endif