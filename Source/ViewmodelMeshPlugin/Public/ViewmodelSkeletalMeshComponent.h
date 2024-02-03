// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "ViewmodelSkeletalMeshComponent.generated.h"

class UViewmodelCalculator;

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup=Viewmodel, meta=(BlueprintSpawnableComponent))
class VIEWMODELMESHPLUGIN_API UViewmodelSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	UViewmodelSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer);

	virtual FMatrix GetRenderMatrix() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Viewmodel")
		UViewmodelCalculator* ViewmodelCalculator;
};
