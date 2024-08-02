#pragma once

class FLogHelper
{
public:
	FORCEINLINE static void InGameDevLog(const FString LogString)
	{
		const FString& Log = LogString;
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, Log);
	}

	FORCEINLINE static void ConsoleLog(const FString LogString)
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *LogString);
	}
};
