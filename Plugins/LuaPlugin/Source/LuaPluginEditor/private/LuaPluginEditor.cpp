// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#include "LuaFactory.h"
#include "CoreMinimal.h"
#include "AssetTypeActions_LuaScript.h"
#include "ILuaPluginEditor.h"


class FLuaPluginEditor : public ILuaPluginEditor
{
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

};

IMPLEMENT_MODULE(FLuaPluginEditor, LuaPluginEditor)

void FLuaPluginEditor::StartupModule() {

    // Register asset types
    IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    {
    TSharedRef<IAssetTypeActions> Action = MakeShareable(new FAssetTypeActions_LuaScript);
    AssetTools.RegisterAssetTypeActions(Action);
    }

}

void FLuaPluginEditor::ShutdownModule() {
}
