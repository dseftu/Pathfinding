#include "pch.h"
#include <GridHelper.h>
#include "BreadthFirstSearch.h"
#include "GreedyBestFirstSearch.h"

#include "DijkstrasAlgorithm.h"
#include "AStar.h"
#include <iostream>

using namespace std;
using namespace Library;

void DrawGrid(int32_t graphWidth, int32_t graphHeight, std::shared_ptr<Library::Node> start, std::shared_ptr<Library::Node> end, std::deque<std::shared_ptr<Library::Node>> path, Graph graph)
{

	for (int32_t y = 0; y < graphHeight; y++)
	{
		for (int32_t x = 0; x < graphWidth; x++)
		{
			Library::Point xy = Library::Point(x, y);
			if (graph.At(xy)->Type() == Library::NodeType::Wall)
			{
				cout << " X ";
			}
			else
			{
				if (start->Location().X == xy.X && start->Location().Y == xy.Y)
				{
					cout << " S ";
				}
				else if (end->Location().X == xy.X && end->Location().Y == xy.Y)
				{
					cout << " E ";
				}
				else if (std::find(path.begin(), path.end(), graph.At(xy)) != path.end())
				{
					cout << " P:" << graph.At(xy)->TotalCost() << " ";
				}
				else
				{
					cout << " " << graph.At(xy)->TotalCost() << " ";
				}
			}
		}
		cout << "\n";
	}
}

int main(int argc, char* argv[])
{
	// Pathfinding.ConsoleApplication.exe Grid.grid
	string filename = (argc == 2 ? argv[1] : ".\\Content\\Grid.grid");
	
	int32_t graphWidth;
	int32_t graphHeight;
	Graph graph = GridHelper::LoadGridFromFile(filename, graphWidth, graphHeight);

	Library::Point start = Library::Point(0, 8);
	std::shared_ptr<Library::Node> startNode = graph.At(start);
	Library::Point end = Library::Point(9, 0);
	std::shared_ptr<Library::Node> endNode = graph.At(end);
	std::set<std::shared_ptr<Library::Node>> closedSeta;

	std::shared_ptr<Library::IPathFinder> search = make_shared<Pathfinding::GreedyBestFirstSearch>();
	std::deque<std::shared_ptr<Library::Node>> aStar = search->FindPath(startNode, endNode, closedSeta);
	std::cout << "Done!, path length = " << aStar.size() << " visited nodes = " << closedSeta.size() << "\n";

	DrawGrid(graphWidth, graphHeight, startNode, endNode, aStar, graph);
	/*
	std::shared_ptr<Library::IPathFinder> bfsearch = make_shared<Pathfinding::BreadthFirstSearch>();
	std::deque<std::shared_ptr<Library::Node>> bfs = bfsearch->FindPath(startNode, endNode, closedSetb);
	std::cout << "BreadthFirstSearch done, visited nodes = " << closedSetb.size() << "\n";
	std::shared_ptr<Library::IPathFinder> gbfssearch = make_shared<Pathfinding::GreedyBestFirstSearch>();
	std::deque<std::shared_ptr<Library::Node>> gbfs = gbfssearch->FindPath(startNode, endNode, closedSetc);
	std::cout << "GreedyBestFirstSearch done, visited nodes = " << closedSetc.size() << "\n";
	std::shared_ptr<Library::IPathFinder> dsearch = make_shared<Pathfinding::DijkstrasAlgorithm>();
	std::deque<std::shared_ptr<Library::Node>> dja = dsearch->FindPath(startNode, endNode, closedSetd);
	std::cout << "DijkstrasAlgorithm done, visited nodes = " << closedSetd.size() << "\n";
	*/
    return 0;
}





