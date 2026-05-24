#pragma once

template<typename A>
A clampValue(A wartosc, A minW, A maxW)
{
	if (wartosc < minW) return minW;
	if (wartosc > maxW) return maxW;
	return wartosc;
}

template<typename A>
A lerp(A a, A b, float i)
{
	return a + static_cast<A>((b - a) * i);
}