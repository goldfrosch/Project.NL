﻿#pragma once

class FUtilHelper
{
};

#define GETTER(type, varName) \
public: \
FORCEINLINE type Get##varName() const { return varName; }

#define SETTER(type, varName) \
public: \
FORCEINLINE void Set##varName(type val) { varName = val; }

#define GETTER_SETTER(type, varName) \
public: \
FORCEINLINE type Get##varName() const { return varName; } \
FORCEINLINE void Set##varName(type val) { varName = val; }