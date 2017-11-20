// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaFactory.h"
#include "Misc/FileHelper.h"
#include "LuaScript.h"


ULuaFactory::ULuaFactory()
{
	SupportedClass = ULuaScript::StaticClass();

	bCreateNew = false;
	bEditorImport = true;
	bEditAfterNew = false;

	Formats.Add(TEXT("lua;Lua script file"));
}

bool ULuaFactory::FactoryCanImport(const FString& Filename)
{
	return true;
}

UObject* ULuaFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) {

	ULuaScript* LuaScript = nullptr;
	FString Code;

	if (FFileHelper::LoadFileToString(Code, *Filename)) {
		LuaScript = NewObject<ULuaScript>(InParent, InClass, InName, Flags);
		LuaScript->Code = Code;
		LuaScript->FileName = *Filename.ToString();
	}

	bOutOperationCanceled = false;

	return LuaScript;
}
