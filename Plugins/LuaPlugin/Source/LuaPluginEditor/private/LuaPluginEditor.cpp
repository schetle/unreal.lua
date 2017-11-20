// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#include "LuaFactory.h"
#include "CoreMinimal.h"
#include "AssetTypeActions_LuaScript.h"
#include "ILuaPluginEditor.h"


class FLuaPluginEditor : public ILuaPluginEditor
{
    /** IModuleInterface implementation */
    virtual void StartupModule() override {

        // Register asset types
        IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
        {
            TSharedRef<IAssetTypeActions> Action = MakeShareable(new FAssetTypeActions_LuaScript);
            AssetTools.RegisterAssetTypeActions(Action);

            RegisteredAssetTypeActions.Add(Action);
        }
    }

    virtual void ShutdownModule() override {
        FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

        if (AssetToolsModule != nullptr)
        {
            IAssetTools& AssetTools = AssetToolsModule->Get();

            for (auto Action : RegisteredAssetTypeActions)
            {
                AssetTools.UnregisterAssetTypeActions(Action);
            }
        }
    }

    /** The collection of registered asset type actions. */
    TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;

};

IMPLEMENT_MODULE(FLuaPluginEditor, LuaPluginEditor)
