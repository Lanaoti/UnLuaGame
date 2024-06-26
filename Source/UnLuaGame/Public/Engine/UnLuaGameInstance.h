// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UnLuaGameInstance.generated.h"


#if UE_EDITOR
namespace UnLua
{
	class FLuaEnv;
}
#endif

USTRUCT()
struct FLuaDebug
{
	GENERATED_BODY()

	FLuaDebug()
		: PIEInstance(INDEX_NONE)
		, IP(TEXT(""))
		, Port(0)
	{
		
	}

	UPROPERTY()
	int32 PIEInstance;

	UPROPERTY()
	FString IP;

	UPROPERTY()
	int32 Port;
};

UCLASS(Config=Game)
class UNLUAGAME_API UUnLuaGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()

	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init() override;

	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown() override;

	/** Called when the game instance is started either normally or through PIE. */
	virtual void OnStart() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnStart();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceivePreLoadMap(const FString& MapName);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceivePostLoadMapWithWorld(UWorld* LoadedWorld);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceivePreLogin(AGameModeBase* GameMode, const FUniqueNetIdRepl& UniqueNetId);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceivePostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveLogout(AGameModeBase* GameMode, AController* Exiting);

protected:
	virtual void PreLoadMap(const FString& MapName);
	virtual void PostLoadMapWithWorld(UWorld* LoadedWorld);
	virtual void PreLogin(AGameModeBase* GameMode, const struct FUniqueNetIdRepl& NewPlayer, FString& ErrorMessage);
	virtual void PostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer);
	virtual void Logout(AGameModeBase* GameMode, AController* Exiting);

private:
	FDelegateHandle PreLoadMapHandle;
	FDelegateHandle PostLoadMapWithWorldHandle;
	FDelegateHandle PreLoginHandle;
	FDelegateHandle PostLoginHandle;
	FDelegateHandle LogoutHandle;

protected:
	UFUNCTION(Exec)
	virtual void ForceGC();

	/** Returns true if this instance is for a dedicated server world */
	UFUNCTION(BlueprintCallable, Category = Game)
	virtual bool IsDedicatedServer() const;

protected:

	UPROPERTY(Config)
	TArray<FLuaDebug> LuaDebugs;

	void StartLuaDebuger();
};
