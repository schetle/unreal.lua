#pragma once
#include "AssetTypeActions_Base.h"
#include "LuaScript.h"

class FAssetTypeActions_LuaScript : public FAssetTypeActions_Base
{
public:
    // IAssetTypeActions Implementation
    virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "FAssetTypeActions_LuaScript", "Lua"); }
    virtual FColor GetTypeColor() const override { return FColor(175, 0, 128); }
    virtual UClass* GetSupportedClass() const override { return ULuaScript::StaticClass(); }
    virtual bool HasActions(const TArray<UObject*>& InObjects) const override;
    virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
    virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
    virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }

private:
    /** Can we execute a reimport for the selected objects? */
    bool CanExecuteReimport(const TArray<TWeakObjectPtr<ULuaScript>> Objects) const;

    /** Handler for when Reimport is selected */
    void ExecuteReimport(const TArray<TWeakObjectPtr<ULuaScript>> Objects) const;
};