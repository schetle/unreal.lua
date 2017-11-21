#include "LuaFactory.h"
#include "AssetTypeActions_LuaScript.h"
#include "FileHelper.h"
#include "EditorStyle.h"
#include "Editor/UnrealEd/Public/EditorReimportHandler.h"
#include "EditorFramework/AssetImportData.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"


void FAssetTypeActions_LuaScript::OpenAssetEditor(const TArray<UObject*>& InObjects,
                                                  TSharedPtr<IToolkitHost> EditWithinLevelEditor) {
    //FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);

    // Enable this to allow an external editor to modify the asset's source file.
    ULuaScript* luaAsset = Cast<ULuaScript>(InObjects[0]);
    FPlatformProcess::LaunchFileInDefaultExternalApplication(*luaAsset->AssetImportData->GetFirstFilename(), NULL, ELaunchVerb::Open);
}

bool FAssetTypeActions_LuaScript::CanExecuteReimport(const TArray<TWeakObjectPtr<ULuaScript>> Objects) const {
    for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt) {
        auto Object = (*ObjIt).Get();
        if (Object) {
            return true;
        }
    }

    return false;
}

void FAssetTypeActions_LuaScript::ExecuteReimport(const TArray<TWeakObjectPtr<ULuaScript>> Objects) const {
    for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt) {
        auto Object = (*ObjIt).Get();
        if (Object) {
            FReimportManager::Instance()->Reimport(Object, /*bAskForNewFileIfMissing=*/false);
        }
    }
}

bool FAssetTypeActions_LuaScript::HasActions(const TArray<UObject*>& InObjects) const {
    return true;
}

void FAssetTypeActions_LuaScript::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) {
    auto Scripts = GetTypedWeakObjectPtrs<ULuaScript>(InObjects);

    MenuBuilder.AddMenuEntry(
        LOCTEXT("LuaScript_Reimport", "Reimport"),
        LOCTEXT("LuaScript_Reimport", "Reload the selected Lua script(s)."),
        FSlateIcon(FEditorStyle::GetStyleSetName(), "ContentBrowser.AssetActions.ReimportAsset"),
        FUIAction(
            FExecuteAction::CreateSP(this, &FAssetTypeActions_LuaScript::ExecuteReimport, Scripts),
            FCanExecuteAction::CreateSP(this, &FAssetTypeActions_LuaScript::CanExecuteReimport, Scripts)
        )
    );
}

#undef LOCTEXT_NAMESPACE
