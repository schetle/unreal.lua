// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaFactory.h"
#include "Misc/FileHelper.h"
#include "LuaScript.h"
#include "Editor.h"


ULuaFactory::ULuaFactory() {
    SupportedClass = ULuaScript::StaticClass();

    bCreateNew = false;
    bEditorImport = true;
    bEditAfterNew = false;

    Formats.Add(TEXT("lua;Lua script file"));
}

bool ULuaFactory::FactoryCanImport(const FString& Filename) {
    return true;
}

UObject* ULuaFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                        const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn,
                                        bool& bOutOperationCanceled) {

    ULuaScript* LuaScript = nullptr;
    FString Code;

    FEditorDelegates::OnAssetPreImport.Broadcast(this, InClass, InParent, InName, *Filename);

    if (FFileHelper::LoadFileToString(Code, *Filename)) {
        LuaScript = NewObject<ULuaScript>(InParent, InClass, InName, Flags);
        LuaScript->Code = Code;
        LuaScript->SourceFilename = GetCurrentFilename();
    }

    FEditorDelegates::OnAssetPostImport.Broadcast(this, LuaScript);

    bOutOperationCanceled = false;

    return LuaScript;
}

bool ULuaFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames) {
    ULuaScript* LuaScriptToReimport = Cast<ULuaScript>(Obj);
    if (LuaScriptToReimport) {
        OutFilenames.Add(LuaScriptToReimport->SourceFilename);
        return true;
    }
    return false;
}

void ULuaFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) {
    ULuaScript* LuaScriptToReimport = Cast<ULuaScript>(Obj);
    if (LuaScriptToReimport && ensure(NewReimportPaths.Num() == 1)) {
        LuaScriptToReimport->SourceFilename = NewReimportPaths[0];
    }
}

EReimportResult::Type ULuaFactory::Reimport(UObject* InObject) {
    ULuaScript* LuaScriptToReimport = Cast<ULuaScript>(InObject);

    if (!LuaScriptToReimport) {
        return EReimportResult::Failed;
    }

    if (LuaScriptToReimport->SourceFilename.IsEmpty() || !FPaths::FileExists(LuaScriptToReimport->SourceFilename)) {
        return EReimportResult::Failed;
    }

    bool OutCanceled = false;
    if (ImportObject(InObject->GetClass(), InObject->GetOuter(), *InObject->GetName(), RF_Public | RF_Standalone,
                     LuaScriptToReimport->SourceFilename, nullptr, OutCanceled)) {
        

        return EReimportResult::Succeeded;
    }

    return EReimportResult::Failed;
}

int32 ULuaFactory::GetPriority() const {
    return 100;
}
