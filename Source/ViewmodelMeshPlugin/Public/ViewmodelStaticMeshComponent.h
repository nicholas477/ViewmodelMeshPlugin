// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ViewmodelStaticMeshComponent.generated.h"

class UViewmodelCalculator;

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = Viewmodel, meta = (BlueprintSpawnableComponent))
class VIEWMODELMESHPLUGIN_API UViewmodelStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UViewmodelStaticMeshComponent(const FObjectInitializer& ObjectInitializer);

	virtual FMatrix GetRenderMatrix() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Viewmodel")
		UViewmodelCalculator* ViewmodelCalculator;
};
