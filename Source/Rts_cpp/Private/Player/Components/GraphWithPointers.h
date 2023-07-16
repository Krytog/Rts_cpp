// Krytog, 2023

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

struct TKeySet : public TSet<const AActor*> {};

class FGraphWithPointers
{
public:
	FGraphWithPointers();
	~FGraphWithPointers();

	void AddVertexToGraph(const AActor* Vertex);
	void ConnectVerticesDirected(const AActor* From, const AActor* To);
	void RemoveConnectionDirected(const AActor* From, const AActor* To);
	void ConnectVertices(const AActor* First, const AActor* Second);
	void RemoveConnection(const AActor* First, const AActor* Second);
	void RemoveVertex(const AActor* Vertex);

	bool IsInGraph(const AActor* Vertex) const;
	bool IsConnectedDirected(const AActor* From, const AActor* To) const;
	bool IsConnected(const AActor* First, const AActor* Second) const;

	void CalculateComponents();
	int32 GetComponentOf(const AActor* Vertex) const;
	int32 GetComponentsNumber() const;

	bool IsComponentNumsValid() const;

private:
	void InvalidateComponentsNum();
	void DFS(const AActor* From);

private:
	UPROPERTY();
	TMap<const AActor*, TKeySet> Graph;

	UPROPERTY()
	TMap<const AActor*, int32> ComponentNum;

	int32 TotalComponents = 0;
	bool bComponentNumsValid = true;
};
