#pragma once
#include "AssetTypeActions_Base.h"
#include "LuaScript.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

class FAssetTypeActions_LuaScript : public FAssetTypeActions_Base
{
public:
    // IAssetTypeActions Implementation
    virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_LuaScript", "Lua"); }
    virtual FColor GetTypeColor() const override { return FColor(175, 0, 128); }
    virtual UClass* GetSupportedClass() const override { return ULuaScript::StaticClass(); }
    virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }

    virtual bool HasActions(const TArray<UObject*>& InObjects) const override;
    virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;

    virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
};