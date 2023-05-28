#pragma once

#include <cmath>
#include <random>

/**
 * \brief 判断两个浮点数是否相等
 * \param a a
 * \param b b
 * \return 相等
 */
inline bool feq(const float a, const float b)
{
	return std::fabsf(a - b) <= FLT_EPSILON;
}

// c++ 随机数
static std::random_device rd;
static std::mt19937_64 engine{};
static std::uniform_int_distribution int_distribution{0, 99};
static std::uniform_real_distribution real_distribution;

inline void random_seed(const long long seed)
{
	engine.seed(seed);
}

/**
 * \brief 获取一个整形随机数，随机数范围为 [0, 100)
 * \return 随机数
 */
inline int random_int()
{
	return int_distribution(engine);
}

/**
 * \brief 获取一个浮点随机数，随机数范围为 [0, 1]
 * \return 随机数
 */
inline float random()
{
	return static_cast<float>(real_distribution(engine));
}
