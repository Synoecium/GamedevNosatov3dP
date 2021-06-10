// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI/ItemFound_Generator.h"

#include "EngineUtils.h"
#include "QueryItem.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

UItemFound_Generator::UItemFound_Generator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	QueryContext = UEnvQueryContext_Querier::StaticClass();
	ItemType = UEnvQueryItemType_Point::StaticClass();
}

void UItemFound_Generator::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	TArray<FVector> ContextLocations;
	if (QueryInstance.World)
	{
		for (TActorIterator<AQueryItem> Itr(QueryInstance.World);Itr;++Itr)
		{
			if (Itr->ValueOfItem <= ValueToCompare)
				ContextLocations.Add(Itr->GetActorLocation());
		}
	}

	for (const FVector& Location : ContextLocations)
	{
		FNavLocation NavLoc(Location);
		QueryInstance.AddItemData<UEnvQueryItemType_Point>(NavLoc);
	}
}
