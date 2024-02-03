// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ViewmodelCalculator.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, BlueprintType)
class VIEWMODELMESHPLUGIN_API UViewmodelCalculator : public UObject
{
	GENERATED_BODY()
	
public:
	virtual bool CalculateViewmodel(const UPrimitiveComponent* Primitive, FMatrix& OutMatrix) const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Viewmodel", meta=(InlineEditConditionToggle))
		bool bModifyFOV = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Viewmodel", meta=(EditCondition=bModifyFOV))
		float FOV = 90.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Viewmodel", meta = (InlineEditConditionToggle))
		bool bModifyDepthScale = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Viewmodel", meta = (EditCondition = bModifyDepthScale))
		float DepthScale = 1.f;
};
