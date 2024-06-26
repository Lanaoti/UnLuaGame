// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GameFramework/UnLuaCharacterMovementComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UnLuaCharacterMovementComponent)


UUnLuaCharacterMovementComponent::UUnLuaCharacterMovementComponent(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

float UUnLuaCharacterMovementComponent::GetMaxSpeed() const
{
	return K2_GetMaxSpeed();
}

float UUnLuaCharacterMovementComponent::K2_GetMaxSpeed_Implementation() const
{
	return UCharacterMovementComponent::GetMaxSpeed();
}