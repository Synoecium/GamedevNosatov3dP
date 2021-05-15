// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/ProceduralActor.h"

// Sets default values
AProceduralActor::AProceduralActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomMesh = CreateDefaultSubobject<UProceduralMeshComponent>("CustomMesh");
	SetRootComponent(CustomMesh);
	CustomMesh->bUseAsyncCooking = true;
}

void AProceduralActor::AddTriangle(int32 V1, int32 V2, int32 V3)
{
	Triangles.Add(V1);
	Triangles.Add(V2);
	Triangles.Add(V3);
}

void AProceduralActor::GenerateCubeMesh()
{
	//6 sides on cube, 4 verts each (corners)

	// These are relative locations to the placed Actor in the world
	Vertices.Add(FVector(0, -100, 0));	// lower left - 0
	Vertices.Add(FVector(0, -100, 100));	// upper left - 1
	Vertices.Add(FVector(0, 100, 0));		// lower right - 2
	Vertices.Add(FVector(0, 100, 100));	// upper right - 3

	Vertices.Add(FVector(100, -100, 0));		// lower front left - 4
	Vertices.Add(FVector(100, -100, 100));	// upper front left - 5

	Vertices.Add(FVector(100, 100, 100));	// upper front right - 6
	Vertices.Add(FVector(100, 100, 0));	// lower front left - 7

	// Back face of cube
	AddTriangle(0, 2, 3);
	AddTriangle(3, 1, 0);

	// Left face of cube
	AddTriangle(0, 1, 4);
	AddTriangle(4, 1, 5);

	// Front face of cube
	AddTriangle(4, 5, 7);
	AddTriangle(7, 5, 6);

	// Right face of cube
	AddTriangle(7, 6, 3);
	AddTriangle(3, 2, 7);

	// Top face of cube
	AddTriangle(1, 3, 5);
	AddTriangle(6, 5, 3);

	// Bottom face of cube
	AddTriangle(2, 0, 4);
	AddTriangle(4, 7, 2);

	TArray<FLinearColor> VertexColors;
	VertexColors.Add(FLinearColor(0.f, 0.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 0.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(0.5f, 1.f, 0.5f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 0.f));
	VertexColors.Add(FLinearColor(0.f, 1.f, 1.f));

	CustomMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), VertexColors,
		TArray<FProcMeshTangent>(), true);
	
}

void AProceduralActor::GenerateStarMesh()
{
	Vertices.Add(FVector(-20, 0, 0));		//0
	Vertices.Add(FVector(0, 0, 70));		//1
	Vertices.Add(FVector(0, 20, 20));		//2
	Vertices.Add(FVector(0, 80, 20));		//3
	Vertices.Add(FVector(0, 30, -10));	//4
	Vertices.Add(FVector(0, 50, -60));	//5
	Vertices.Add(FVector(0, 0, -30));		//6
	Vertices.Add(FVector(0, -50, -60));	//7
	Vertices.Add(FVector(0, -30, -10));	//8
	Vertices.Add(FVector(0, -80, 20));	//9
	Vertices.Add(FVector(0, -20, 20));	//10
	Vertices.Add(FVector(20, 0, 0));		//11

	TArray<FVector> normals;
	for (auto vert : Vertices)
	{
		normals.Add(FVector(1, 0, 0));
	}
	
	for (int32 i = 1; i<10; i++)
	{
		AddTriangle(0, i, i+1);
	}
	AddTriangle(0, 10, 1);

	for (int32 i = 1; i<10; i++)
	{
		AddTriangle(11, i+1, i);
	}
	AddTriangle(11, 1, 10);

	TArray<FLinearColor> VertexColors;
	CustomMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, normals, TArray<FVector2D>(), VertexColors,
		TArray<FProcMeshTangent>(), true);
	
}

void AProceduralActor::GenerateTriangleMesh()
{
	Vertices.Add(FVector(0, 0, 160));		//0
	Vertices.Add(FVector(0, 100, 0));		//1
	Vertices.Add(FVector(90, -60, 0));		//2
	Vertices.Add(FVector(-90, -60, 0));		//3

	AddTriangle(0, 1, 2);
	AddTriangle(0, 2, 3);
	AddTriangle(0, 3, 1);
	AddTriangle(3, 2, 1);

	TArray<FLinearColor> VertexColors;
	CustomMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), VertexColors,
		TArray<FProcMeshTangent>(), true);
}

// Called when the game starts or when spawned
void AProceduralActor::BeginPlay()
{
	Super::BeginPlay();
	if (MeshFigure == EMeshFigure::Cube) GenerateCubeMesh();
	if (MeshFigure == EMeshFigure::Star) GenerateStarMesh();
	if (MeshFigure == EMeshFigure::Triangle) GenerateTriangleMesh();
}

// Called every frame
void AProceduralActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

