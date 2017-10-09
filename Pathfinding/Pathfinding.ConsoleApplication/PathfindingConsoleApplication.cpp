#include "pch.h"
#include <GridHelper.h>
#include "BreadthFirstSearch.h"
#include "GreedyBestFirstSearch.h"
#include <IPathFinder.h>
#include "IPathHelper.h"

using namespace std;
using namespace Library;

int main(int argc, char* argv[])
{
	// Pathfinding.ConsoleApplication.exe Grid.grid
	string filename = (argc == 2 ? argv[1] : "Content\\Grid.grid");

	int32_t graphWidth;
	int32_t graphHeight;
	Graph graph = GridHelper::LoadGridFromFile(filename, graphWidth, graphHeight);

	Library::Point start = Library::Point(0, 0);
	std::shared_ptr<Library::Node> startNode = graph.At(start);
	Library::Point end = Library::Point(9, 9);
	std::shared_ptr<Library::Node> endNode = graph.At(end);
	std::set<std::shared_ptr<Library::Node>> closedSet;

	
	Library::IPathFinder *search = new Pathfinding::GreedyBestFirstSearch();
	
	
	std::deque<std::shared_ptr<Library::Node>> thePath = search->FindPath(startNode, endNode, closedSet);
    return 0;
}

