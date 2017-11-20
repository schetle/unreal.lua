// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaScript.generated.h"

UCLASS(meta=(lua=1))
class LUAPLUGINRUNTIME_API ULuaScript : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LuaScript)
	FString FileName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = LuaScript)
	FString Code;
};
