#include "CoreMinimal.h"
#include "LuaScript.h"
#include "EditorFramework/AssetImportData.h"

void ULuaScript::GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const {
    if (AssetImportData)
    {
        OutTags.Add(FAssetRegistryTag(SourceFileTagName(), AssetImportData->GetSourceData().ToJson(), FAssetRegistryTag::TT_Hidden));
    }

    Super::GetAssetRegistryTags(OutTags);
}

void ULuaScript::PostInitProperties() {
	if (IsAsset())
	{
		AssetImportData = NewObject<UAssetImportData>(this, TEXT("AssetImportData"));
	}

	Super::PostInitProperties();
}

void ULuaScript::PostLoad() {
	Super::PostLoad();

	if (!IsAsset() && AssetImportData)
	{
		// UCurves inside Blueprints previously created these sub objects incorrectly, so ones loaded off disk will still exist
		AssetImportData = nullptr;
	}

	if (!ImportPath_DEPRECATED.IsEmpty() && AssetImportData)
	{
		FAssetImportInfo Info;
		Info.Insert(FAssetImportInfo::FSourceFile(ImportPath_DEPRECATED));
		AssetImportData->SourceData = MoveTemp(Info);
	}
}
