#pragma once

/**
 * \brief 地图中单元格的个数
 */
constexpr int CELL_COUNT = 200;

class GameWindow;
class GameRenderer;
class GameLogic;

/**
 * \brief 当前运行中的游戏
 */
extern GameLogic* current_game;

/**
 * \brief 当前运行中的游戏窗口
 */
extern GameWindow* current_window;

/**
 * \brief 当前运行中的游戏渲染器
 */
extern GameRenderer* current_renderer;

/**
 * \brief 调试用，校验 GL 错误
 * \param name 异常原因
 */
void log_error(const char* name);
