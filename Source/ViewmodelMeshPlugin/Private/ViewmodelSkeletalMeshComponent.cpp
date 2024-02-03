// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewmodelSkeletalMeshComponent.h"
#include "ViewmodelCalculator.h"


UViewmodelSkeletalMeshComponent::UViewmodelSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ViewmodelCalculator = CreateDefaultSubobject<UViewmodelCalculator>("Viewmodel Calculator");
}

FMatrix UViewmodelSkeletalMeshComponent::GetRenderMatrix() const
{
    FMatrix Matrix;
    if (ViewmodelCalculator != nullptr && ViewmodelCalculator->CalculateViewmodel(this, Matrix))
    {
        return Matrix;
    }
    else
    {
        Matrix = Super::GetRenderMatrix();
    }
    return Matrix;
}
