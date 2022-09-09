#pragma once

#include "/Engine/Private/Common.ush"

void TestFunc(float InFloat, out float OutFloat)
{
	OutFloat = ClampToHalfFloatRange(InFloat);
}
