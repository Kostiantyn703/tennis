#pragma once

static const char *TITLE		= "TENNIS";
static const char *FONT_PATH	= "../content/score_font.ttf";
static const char *NETWORK_CONFIG_FILENAME = "network.ini";

constexpr size_t WINDOW_HEIGHT	= 600;
constexpr size_t WINDOW_WIDTH	= 800;

constexpr float BORDER_OFFSET		= 10.f;
constexpr float PLAYER_MAX_SPEED	= 400.f;

constexpr size_t PADDLE_SHAPE_COUNT	= 4;
constexpr float	PADDLE_PADDING		= 1.f;
constexpr float PADDLE_WIDTH		= 10.f;
constexpr float PADDLE_HEIGHT		= 25.f;

#include <cmath>

constexpr float PI = 3.14159f;
constexpr float PLANE_ANGLE = 180.f;

static float caculate_sine(float in_angle) {
	return std::sin(in_angle * (PI / PLANE_ANGLE));
}

static float calculate_cosine(float in_angle) {
	return std::cos(in_angle * (PI / PLANE_ANGLE));
}
