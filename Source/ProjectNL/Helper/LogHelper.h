#pragma once

#define CONSOLE_LOG(Format, ...) \
{ \
	UE_LOG(LogTemp, Display, Format, ##__VA_ARGS__); \
}
