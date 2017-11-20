#include "LuaFactory.h"
#include "AssetTypeActions_LuaScript.h"
#include "FileHelper.h"

void FAssetTypeActions_LuaScript::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) {
    ULuaScript* luaAsset = Cast<ULuaScript>(InObjects[0]);
    FPlatformProcess::LaunchFileInDefaultExternalApplication(*luaAsset->FileName, NULL, ELaunchVerb::Open);
}

bool FAssetTypeActions_LuaScript::HasActions(const TArray<UObject*>& InObjects) const {
    return true;
}

void FAssetTypeActions_LuaScript::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) {
    FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);

    auto ScriptAssets = GetTypedWeakObjectPtrs<ULuaScript>(InObjects);

    MenuBuilder.AddMenuEntry(
        LOCTEXT("LuaScript_Reimport", "Re-Import"),
        LOCTEXT("LuaScript_Reimport", "Reload contents"),
        FSlateIcon(),
        FUIAction(
            FExecuteAction::CreateLambda([=] {
                for (auto& Script : ScriptAssets)
                {
                    if (Script.IsValid() && !Script->FileName.IsEmpty())
                    {
                        FString Code;
                        if (FFileHelper::LoadFileToString(Code, *Script->FileName)) {
                            Script->Code = Code;
                            Script->PostEditChange();
                            Script->MarkPackageDirty();
                        }
                      
                    }
                }
            }),
            FCanExecuteAction::CreateLambda([=] {
                for (auto& Script : ScriptAssets)
                {
                    if (Script.IsValid() && !Script->FileName.IsEmpty())
                    {
                        return true;
                    }
                }
                return false;
            })
        )
    );
}