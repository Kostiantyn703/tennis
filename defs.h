#pragma once

static const char *TITLE		= "TENNIS";

constexpr size_t WINDOW_HEIGHT	= 600;
constexpr size_t WINDOW_WIDTH	= 800;

constexpr float BORDER_OFFSET		= 10.f;
constexpr float PLAYER_MAX_SPEED	= 400.f;
constexpr size_t PLAYER_SHAPE_COUNT	= 4;

#include <cmath>

constexpr float PI = 3.14159f;
constexpr float PLANE_ANGLE = 180.f;

static float caculate_sine(float in_angle) {
	return std::sin(in_angle * (PI / PLANE_ANGLE));
}

static float calculate_cosine(float in_angle) {
	return std::cos(in_angle * (PI / PLANE_ANGLE));
}
