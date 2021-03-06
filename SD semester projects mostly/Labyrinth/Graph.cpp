#include "Graph.h"

Graph::Node::Node(Cell * cell)
{
	this->cell = cell;
	visited = false;
	parent = NULL;
}

Graph::~Graph()
{
	clear();
}

/// Inserts Edge between two cells in the graph.
/// Checks if the source cell is already in the graph and get it`s pointer to that NODE, if it`s not in the graph, adds it in the list of nodes.
/// Also for the dest cell.
/// Adds dest cell and path in the 'sons' of source NODE.

void Graph::insertEdge(Cell* source, Cell* dest, DLList<Cell*>& path)
{
	// Get the nodes, which contains the needed cells..
	Node * sourceNode = getNode(source);
	Node * destNode = getNode(dest);

	// Make the connection between the source and dest node, e.g. push the destNode (and it`s path to the cell) to the sons of source node.
	sourceNode->sons.push_back(Pair<Node*, DLList<Cell*>>(destNode, path));
}

// Prints all edges between cells and the paths...

void Graph::print(std::ostream& out)
{
	for (DLList<Node*>::Iterator iter = allNodes.begin(); iter != allNodes.end(); ++iter)
	{
		printNode(out, *iter);
		out << "\n";
	}
}

/// Prints the cell info and it`s sons, so the edge between the given cell(node*) and the sons of that node...

void Graph::printNode(std::ostream& out, Node* node)
{
	for (DLList<Pair<Node*, DLList<Cell*>>>::Iterator iter = node->sons.begin(); iter != node->sons.end(); ++iter)
	{
		out << node->cell->getSymbol() << " -> " << (*iter).first->cell->getSymbol() << " path: ";
		for (DLList<Cell*>::Iterator pathIter = (*iter).second.begin(); pathIter != (*iter).second.end(); ++pathIter)
		{
			out << "(" << (*pathIter)->getIndexRow() << ", " << (*pathIter)->getIndexCol() << ") ";
		}
		out << "\n";
	}
}

// If there is no node, representing the given cell, creates the node and pushes it to the list of allNodes, returns the new node, otherwise (if there is- returns the found one).

Graph::Node * Graph::getNode(Cell* cell)
{
	Node * node = findNode(cell);

	if (!node)
	{
		node = new Node(cell);
		allNodes.push_back(node);
	}

	return node;
}

/// Search for a node with the given cell(first one if ever there are more than one...). If no matches, returns NULL; Check if the pointer addresses are the same...
/// O(n) n- number of nodes... 

Graph::Node * Graph::findNode(const Cell * cell)
{
	for (DLList<Node*>::Iterator iter = allNodes.begin(); iter != allNodes.end(); ++iter)
	{
		if ((*iter)->cell == cell)
			return (*iter);
	}

	return NULL;
}

/// Goes through every node and deletes it. Removes it from the list of nodes.

void Graph::clear()
{
	while (!allNodes.isEmpty())
	{
		delete allNodes.pop_back();
	}
}

/// PATH FINDING.


/// Makes DFS search through nodes. auto-clears the visited field, so no need for reset. Makes empty list of banned cells, so it has no banned cells, makes two more checks , one more reference every function call, but for not it`s maybe good.

DLList<DLList<Cell*>> Graph::AllPathsBetweenCells(Cell* start, Cell* end)
{
	DLList<DLList<Cell*>> allPaths;

	DFSPathsBetweenCells(findNode(start), findNode(end), DLList<Cell*>(), DLList<Cell*>(), allPaths, Map_Char_pCell());

	return allPaths;
}

/// Makes DFS search through nodes. auto-clears the visited field, so no need for reset. Don`t goes to the cells, if they are banned.

DLList<DLList<Cell*>> Graph::AllPathsBetweenCellsWithBannedCells(Cell* start, Cell* end, Map_Char_pCell & bannedCells)
{
	DLList<DLList<Cell*>> allPaths;

	DFSPathsBetweenCells(findNode(start), findNode(end), DLList<Cell*>(), DLList<Cell*>(), allPaths, bannedCells);

	return allPaths;
}

void Graph::DFSPathsBetweenCells(Node* startNode, Node* endNode, DLList<Cell*> & pathToThatCell, DLList<Cell*> currPath, DLList<DLList<Cell*>>& allPaths, Map_Char_pCell & bannedCells)
{
	// If the start node is NULL, or its visited or its in the list of banned cells, returns;
	if (!startNode || !endNode || startNode->visited == true || bannedCells.getCellAt(startNode->cell->getSymbol()) != NULL)
		return;

	// Add the path to that cell to the current path.
	// currPath += pathToThatCell;
	currPath.push_back(startNode->cell);

	// If we are at the needed one(node), adds the path to the all paths and returns.
	if (startNode->cell == endNode->cell)
	{
	//	currPath.push_back(endNode->cell); // Adds the last cell, because the path has the start cell, inbetween cells and not the last one.
		allPaths.push_back(currPath);
		return;
	}

	// Otherwise we search for the end node in the childrens of that node. Sets the current node to visited, so it don`t go to it (or the paths to that node...)

	startNode->visited = true;

	for (DLList<Pair<Node*, DLList<Cell*>>>::Iterator iter = startNode->sons.begin(); iter != startNode->sons.end(); ++iter)
	{
		// If the child is not visited and it`s not in the banned cells.
		if ((*iter).first->visited == false && bannedCells.getCellAt((*iter).first->cell->getSymbol()) == NULL)
			DFSPathsBetweenCells((*iter).first, endNode, (*iter).second, currPath, allPaths, bannedCells);
	}

	startNode->visited = false;
}
















/// Gets the path between the 2 nodes(direct one!). (if not found, returns empty one).

DLList<Cell*> Graph::getDirectPathBetweenTwoNodes(Node * parent, Node * child)
{
	if (!parent || !child)
		return DLList<Cell*>();

	// Goes through every son to find the needed one...
	for (DLList<Pair<Node*, DLList<Cell*>>>::Iterator iter = parent->sons.begin(); iter != parent->sons.end(); ++iter)
	{
		if ((*iter).first == child)
			return (*iter).second;
	}

	return DLList<Cell*>();
}

/// Returns the full path by given path of special cells.

DLList<Cell*> Graph::getFullPathFromSpecialCells(DLList<Cell*> & pathOfSpecialCells)
{
	DLList<Cell*> fullPath;

	Node * root = findNode(pathOfSpecialCells.peek_front()); // Searches the start node, O(broq na nodovete, losho malko) pops the first element of the path.

	// ++first one, so I can skip the starting cell.
	for (DLList<Cell*>::Iterator iter = ++pathOfSpecialCells.begin(); iter != pathOfSpecialCells.end(); ++iter)
	{
		bool nextNode = false;

		for (DLList<Pair<Node*, DLList<Cell*>>>::Iterator child = root->sons.begin(); child != root->sons.end(); ++child)
		{
			// Searches the correct child.
			if ((*child).first->cell == (*iter))
			{
				root = (*child).first;
				fullPath += (*child).second;
				nextNode = true;
				break;
			}
		}

		if (!nextNode)
			throw "Can`t regenerate the full path, sorry!";
	}

	// Adds the last cell. Because the direct path contains the start cell, the inbetween path and NO end cell.
	fullPath.push_back(pathOfSpecialCells.peek_back());

	return fullPath;
}












///
/// CEMETERY
///



//
//
///// Returns the path between the two cells (if there is no DIRECT path, returns empty list).
//
//DLList<Cell*> Graph::getDirectPathBetweenTwoCells(Cell * parent, Cell * child)
//{
//	return getDirectPathBetweenTwoNodes(findNode(parent), findNode(child));
//}


//
///// TO DO: DELETE THIS SHITS
//

/// BFS but can`t find all paths...

/// Returns all paths (NOT ALL)from start cell, to the end cell, when it walks only on doors. Returns a list of all the paths, which are cells (doors). NOTE: Dont goest through already taken nodes.
//
//DLList<DLList<Cell*>> Graph::BFSAllPathsBetweenCells(Cell* start, Cell* end)
//{
//	DLList<DLList<Cell*>> allPaths;
//
//	Board* board = start->getOwner();
//
//	Node * startNode = findNode(start);
//	Node * endNode = findNode(end);
//
//	// Start or end cell is not in the graph... or the owners of the two cells are diferent.
//	if (!startNode || !endNode || board != end->getOwner())
//		return allPaths;
//
//	Queue<Node*> queue;
//
//	queue.enqueue(startNode);
//	startNode->visited = true;
//
//	while (!queue.isEmpty())
//	{
//		Node* currentNode = queue.dequeue();
//
//		for (DLList<Pair<Node*, DLList<Cell*>>>::Iterator iter = currentNode->sons.begin(); iter != currentNode->sons.end(); ++iter)
//		{
//			BFSAddNeighbour(board, startNode, endNode, currentNode, (*iter).first, queue, allPaths);
//		}
//	}
//
//	BFSResetNodesNeededInfo();
//
//	return allPaths;
//}
//
///// 
//
//void Graph::BFSAddNeighbour(Board * board, Node* startNode, Node * endNode, Node* currentNode, Node* neighbourNode, Queue<Node*>& queue, DLList<DLList<Cell*>> & allPaths)
//{
//	// If the neighbour node is not valid one or it`s not a door cell returns... (unless the end node is the neighbour node).
//	//if (!neighbourNode || (board->doors.getCellAt(neighbourNode->cell->getSymbol()) == NULL && neighbourNode != endNode))
//	if (!neighbourNode)
//		return;
//
//	// If the neighbour is not visited. 
//	if (neighbourNode->visited == false)
//	{
//		// If the neighbour node is searched one (endNode) adds the path to that node to the list of paths...
//		if (neighbourNode == endNode)
//		{
//			DLList<Cell*> path;
//
//			BFSResolveThaPath(currentNode, neighbourNode, startNode, path);
//
//			allPaths.push_back(path);
//		}
//		else
//		{
//			queue.enqueue(neighbourNode);
//			neighbourNode->parent = currentNode;
//			neighbourNode->visited = true; // dont mark it if there is path to there, so it can found more paths...
//		}
//	}
//}
//
///// Goes through every cell and fints its parent, and when it finds it, takse tha path from the parent to him
//
//void Graph::BFSResolveThaPath(Node* currentNode, Node* neighbourNode, Node* startNode, DLList<Cell*> & path)
//{
//	// Push front because it`s in reverce order...
//
//	// Adds the ending cell.
//	path.push_front(neighbourNode->cell);
//
//	while (currentNode && currentNode->parent && currentNode != startNode)
//	{
//		path.push_front(currentNode->cell);
//		currentNode = currentNode->parent;
//	}
//
//	// Adds the starting cell.
//	path.push_front(startNode->cell);
//}
//
///// Sets all nodes visited and parent valus to default ones..
//
//void Graph::BFSResetNodesNeededInfo()
//{
//	for (DLList<Node*>::Iterator iter = allNodes.begin(); iter != allNodes.end(); ++iter)
//	{
//		(*iter)->visited = false;
//		(*iter)->parent = NULL;
//	}
//}
