// Copyright 2022 CQUnreal. All Rights Reserved.

#include "Camera/UnLuaPlayerCameraManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UnLuaPlayerCameraManager)

AUnLuaPlayerCameraManager::AUnLuaPlayerCameraManager(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AUnLuaPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	ReceiveUpdateCamera(DeltaTime);

	OnUpdateCamera.Broadcast(DeltaTime, GetCameraRotation(), GetCameraLocation());
}