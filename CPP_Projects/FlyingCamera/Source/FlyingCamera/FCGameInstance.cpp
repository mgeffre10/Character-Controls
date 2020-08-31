// Fill out your copyright notice in the Description page of Project Settings.


#include "FCGameInstance.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

void UFCGameInstance::Init()
{
	FString FilePath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("LevelGrids.txt"));
	FString FileData;

	UE_LOG(LogTemp, Warning, TEXT("File Path: %s"), *FilePath);
		
	FFileHelper::LoadFileToString(FileData, *FilePath);

	TArray<FString> FileLines;

	int32 LineCount = FileData.ParseIntoArray(FileLines, TEXT("\n"), true);

	if (LineCount)
	{
		int32 StartingGridLine = 0;
		int32 EndingGridLine = 0;
		bool bIsCapturingGrid = false;
		FString EntryLevelName;
		TArray<FString> GridLines;

		for (int i = 0; i < LineCount; i++)
		{
			FString Line = FileLines[i];

			if (Line.Len())
			{
				UE_LOG(LogTemp, Warning, TEXT("Line: %s"), *Line);

				if (!bIsCapturingGrid)
				{
					TArray<FString> LineParts;
					int32 LinePartsCount = Line.ParseIntoArray(LineParts, TEXT(" "), true);

					EntryLevelName = LineParts[0];
					EndingGridLine = FCString::Atoi(*LineParts[1]);
					bIsCapturingGrid = true;

					UE_LOG(LogTemp, Warning, TEXT("Level Name : %s, Ending Grid Line: %d"), *EntryLevelName, EndingGridLine);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Starting Grid Line: %d"), StartingGridLine);
					UE_LOG(LogTemp, Warning, TEXT("Ending Grid Line: %d"), EndingGridLine);

					if (StartingGridLine < EndingGridLine)
					{
						UE_LOG(LogTemp, Warning, TEXT("Adding line to GridLines: %s"), *Line);
						GridLines.Add(Line);
						StartingGridLine++;

						if (StartingGridLine == EndingGridLine)
						{
							UE_LOG(LogTemp, Warning, TEXT("Finished adding Grid Lines, adding to Levels"));
							Levels.Add(EntryLevelName, GridLines);
							GridLines.Empty();
							bIsCapturingGrid = false;
							StartingGridLine = 0;
						}
					}
				}
			}
		}

		PrintLevels();
	}
}

void UFCGameInstance::PrintLevels()
{
	for (auto Iter = Levels.CreateConstIterator(); Iter; ++Iter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Level Name: %s"), *Iter->Key);

		TArray<FString> Grid = Iter->Value;

		for (auto GridLine : Grid)
		{
			UE_LOG(LogTemp, Warning, TEXT("Grid Line: %s"), *GridLine);
		}
	}
}