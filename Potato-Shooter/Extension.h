#pragma once
#include <stdlib.h> 
#include <string>
#include <cstdio>
#include <vector>
#include <random>

#define PI 3.1415926535

//VisualStudioのデバッグコンソールに文字列を出力
#define PRINTF_VS(msg, ...) _RPTFN(_CRT_WARN, msg,__VA_ARGS__);
#define PRINT_VS(msg) _RPTF0(_CRT_WARN, msg);

//２次元のベクトル情報
struct Vector2Int;
struct Vector2;


struct Vector2Int
{
	int x;
	int y;

	explicit operator Vector2() const;

	void operator =(const Vector2Int& delta);

	Vector2Int operator +(const Vector2Int& delta);
	Vector2Int operator -(const Vector2Int& delta);

	void operator +=(const Vector2Int& delta);
	void operator -=(const Vector2Int& delta);
};

struct Vector2
{
	float x;
	float y;

	Vector2(float x, float y);

	explicit operator Vector2Int() const;

	void operator =(const Vector2& delta);

	Vector2 operator +(const Vector2& delta) const;
	Vector2 operator -(const Vector2& delta) const;
	Vector2 operator *(const float& ext) const;
	Vector2 operator /(const float& ext) const;

	void operator +=(const Vector2& delta);
	void operator -=(const Vector2& delta);

	float magnitude() const;
	Vector2 normalized() const;
};

//乱数の初期化
void init_rand();

//min ~ maxで乱数を生成
int rand_int(int min, int max);

//min ~ maxでvalueを収める
float clamp(float min, float max, float value);

//min ~ maxでvalueを収める
int clamp_int(int min, int max, int value);

//0 ~ maxでvalueをループ
float repeat(float value, float max);

//度数からラジアンに変換
double deg_to_rad(double deg);



//配列をシャッフル
template <typename T>
void shuffle(T* arr, int count)
{
	for (int i = count - 1; i >= 1; i--) //fisher-yates shuffle
	{
		int x = rand() % (i + 1);

		T tmp = arr[x];
		arr[x] = arr[i];
		arr[i] = tmp;
	}
}


template <typename T>
T clamp(const T& min, const T& max, const T& value)
{
	if (value < min) return min;
	if (value > max) return max;

	return value;
}

//指定された文字列に文字をフォーマット
template <typename ... Args>
std::string format(const std::string& fmt, Args ... args)
{
	size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args ...);
	std::vector<char> buf(len + 1);
	std::snprintf(&buf[0], len + 1, fmt.c_str(), args ...);
	return std::string(&buf[0], &buf[0] + len);
}

