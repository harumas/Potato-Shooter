#pragma once
#include "DxLib.h"

//指定した時間が経過したかを確認するクラス
class DelayPromise
{
	const LONGLONG complete_time;

public:
	DelayPromise(int delay_time) :
		complete_time((long long)(GetNowHiPerformanceCount() + delay_time * 1000))
	{}

	bool complete()
	{
		return GetNowHiPerformanceCount() > complete_time;
	}
};

