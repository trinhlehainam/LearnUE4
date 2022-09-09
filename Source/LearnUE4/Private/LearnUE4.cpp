// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearnUE4.h"
#include "Modules/ModuleManager.h"

void FLearnUE4::StartupModule()
{
#if (ENGINE_MINOR_VERSION >= 21)    
	FString ShaderDirectory = FPaths::Combine(*(FPaths::ProjectDir()), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping("/Project", ShaderDirectory);
#endif
}

void FLearnUE4::ShutdownModule()
{
}

IMPLEMENT_PRIMARY_GAME_MODULE( FLearnUE4, LearnUE4, "LearnUE4" );