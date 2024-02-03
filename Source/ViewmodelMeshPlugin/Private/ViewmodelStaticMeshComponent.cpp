// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewmodelStaticMeshComponent.h"
#include "ViewmodelCalculator.h"


UViewmodelStaticMeshComponent::UViewmodelStaticMeshComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ViewmodelCalculator = CreateDefaultSubobject<UViewmodelCalculator>("Viewmodel Calculator");
}

FMatrix UViewmodelStaticMeshComponent::GetRenderMatrix() const
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
