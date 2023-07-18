// Krytog, 2023


#include "Player/Components/GraphWithPointers.h"

FGraphWithPointers::FGraphWithPointers() = default;

FGraphWithPointers::~FGraphWithPointers() = default;

void FGraphWithPointers::AddVertexToGraph(const AActor* Vertex)
{
	if (Graph.Contains(Vertex))
	{
		return;
	}
	Graph.Add(Vertex, {});
	ComponentNum.Add(Vertex, 0);
	bComponentNumsValid = false;
}

void FGraphWithPointers::ConnectVerticesDirected(const AActor* From, const AActor* To)
{
	if (!Graph.Contains(From))
	{
		return;
	}
	Graph[From].Add(To);
	bComponentNumsValid = false;
}

void FGraphWithPointers::RemoveConnectionDirected(const AActor* From, const AActor* To)
{
	if (!Graph.Contains(From))
	{
		return;
	}
	Graph[From].Remove(To);
	bComponentNumsValid = false;
}

void FGraphWithPointers::ConnectVertices(const AActor* First, const AActor* Second)
{
	ConnectVerticesDirected(First, Second);
	ConnectVerticesDirected(Second, First);
}

void FGraphWithPointers::RemoveConnection(const AActor* First, const AActor* Second)
{
	RemoveConnectionDirected(First, Second);
	RemoveConnectionDirected(Second, First);
}

void FGraphWithPointers::RemoveVertex(const AActor* Vertex)
{
	if (!Graph.Contains(Vertex))
	{
		return;
	}
	for (auto& [GraphVertex, Set] : Graph)
	{
		Set.Remove(Vertex);
	}
	Graph.Remove(Vertex);
	ComponentNum.Remove(Vertex);
	bComponentNumsValid = false;
}

bool FGraphWithPointers::IsInGraph(const AActor* Vertex) const
{
	return Graph.Contains(Vertex);
}

bool FGraphWithPointers::IsConnectedDirected(const AActor* From, const AActor* To) const
{
	if (!Graph.Contains(From))
	{
		return false;
	}
	return Graph[From].Contains(To);
}

bool FGraphWithPointers::IsConnected(const AActor* First, const AActor* Second) const
{
	return IsConnectedDirected(First, Second) || IsConnectedDirected(Second, First);
}

void FGraphWithPointers::CalculateComponents()
{
	InvalidateComponentsNum();
	for (auto& [Object, Set] : Graph)
	{
		if (!ComponentNum[Object])
		{
			++TotalComponents;
			DFS(Object);
		}
	}
	bComponentNumsValid = true;
}

int32 FGraphWithPointers::GetComponentOf(const AActor* Vertex) const
{
	if (!ComponentNum.Contains(Vertex))
	{
		return -1;
	}
	return ComponentNum[Vertex];
}

int32 FGraphWithPointers::GetComponentsNumber() const
{
	return TotalComponents;
}

bool FGraphWithPointers::IsComponentNumsValid() const
{
	return bComponentNumsValid;
}

void FGraphWithPointers::InvalidateComponentsNum()
{
	for (auto& [Key, Value] : ComponentNum)
	{
		Value = 0;
	}
	TotalComponents = 0;
	bComponentNumsValid = false;
}

void FGraphWithPointers::DFS(const AActor* From)
{
	ComponentNum[From] = TotalComponents;
	for (auto Neighbour : Graph[From])
	{
		if (!ComponentNum[Neighbour])
		{
			DFS(Neighbour);
		}
	}
}
