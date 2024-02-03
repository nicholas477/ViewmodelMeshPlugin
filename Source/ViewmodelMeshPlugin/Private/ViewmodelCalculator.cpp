// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewmodelCalculator.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

bool UViewmodelCalculator::CalculateViewmodel(const UPrimitiveComponent* Primitive, FMatrix& OutMatrix) const
{
	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	const APlayerCameraManager* PlayerCameraManager = PlayerController ? PlayerController->PlayerCameraManager : nullptr;
	if (PlayerController == nullptr || PlayerCameraManager == nullptr)
	{
		return false;
	}

	const float CurrentFOV = PlayerCameraManager->GetFOVAngle();
	const float ViewmodelFOV = FOV;

	const float CurrentHalfFOVRadians = FMath::DegreesToRadians(FMath::Max(0.001f, CurrentFOV)) / 2.0f;
	const float DesiredHalfFOVRadians = FMath::DegreesToRadians(FMath::Max(0.001f, ViewmodelFOV)) / 2.0f;
	const float FOVRatio = CurrentHalfFOVRadians / DesiredHalfFOVRadians;

	FVector ViewOrigin;
	FRotator ViewRotation;
	PlayerController->GetPlayerViewPoint(ViewOrigin, ViewRotation);

	FMatrix ViewRotationMatrix = FInverseRotationMatrix(ViewRotation) * FMatrix(
		FPlane(0, 0, 1, 0),
		FPlane(1, 0, 0, 0),
		FPlane(0, 1, 0, 0),
		FPlane(0, 0, 0, 1));

	if (!ViewRotationMatrix.GetOrigin().IsNearlyZero(0.0f))
	{
		ViewOrigin += ViewRotationMatrix.InverseTransformPosition(FVector::ZeroVector);
		ViewRotationMatrix = ViewRotationMatrix.RemoveTranslation();
	}

	const FMatrix ViewMatrix = FTranslationMatrix(-ViewOrigin) * ViewRotationMatrix;
	const FMatrix InverseViewMatrix = FTranslationMatrix(-ViewMatrix.GetOrigin()) * ViewMatrix.RemoveTranslation().GetTransposed();

	// Convert from component to world, then world to view
	OutMatrix = Primitive->GetComponentToWorld().ToMatrixWithScale() * ViewMatrix;
	if (bModifyFOV)
	{
		FMatrix PerspectiveAdjustmentMatrix = FMatrix(
			FPlane(FOVRatio, 0,        0, 0),
			FPlane(0,        FOVRatio, 0, 0),
			FPlane(0,        0,        1, 0),
			FPlane(0,        0,        0, 1));
		
		// Apply the projection adjustment matrix relative to the view (camera) position
		OutMatrix *= PerspectiveAdjustmentMatrix;
	}

	if (bModifyDepthScale)
	{
		FMatrix DepthAdjustmentMatrix = FMatrix(
			FPlane(DepthScale, 0,          0,          0),
			FPlane(0,          DepthScale, 0,          0),
			FPlane(0,          0,          DepthScale, 0),
			FPlane(0,          0,          0,          1));

		OutMatrix *= DepthAdjustmentMatrix;
	}

	// Convert the matrix back to just component to world
	OutMatrix *= InverseViewMatrix;

	return true;
}
