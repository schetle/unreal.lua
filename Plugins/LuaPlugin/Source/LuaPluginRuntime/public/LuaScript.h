// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaScript.generated.h"

UCLASS(meta=(lua=1))
class LUAPLUGINRUNTIME_API ULuaScript : public UObject
{
	GENERATED_BODY()

public:

	// TODO: Add ByteCode field for pre-compiled scripts

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LuaScript)
	FString SourceFilename;*/
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = LuaScript)
	FString Code;


#if WITH_EDITORONLY_DATA

	/** Override to ensure we write out the asset import data */
	virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;
	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

	UPROPERTY(VisibleAnywhere, Instanced, Category=ImportSettings)
	class UAssetImportData* AssetImportData;

public:

	/** The filename imported to create this object. Relative to this object's package, BaseDir() or absolute */
	UPROPERTY()
	FString ImportPath_DEPRECATED;

#endif
};
