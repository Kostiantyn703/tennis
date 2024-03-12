#pragma once

static const char *TITLE		= "TENNIS";

constexpr size_t WINDOW_HEIGHT	= 600;
constexpr size_t WINDOW_WIDTH	= 800;

constexpr float BORDER_OFFSET		= 10.f;
constexpr float PLAYER_MAX_SPEED	= 400.f;

#include <cmath>

constexpr float pi = 3.14159f;
constexpr float plane_angle = 180.f;

static float caculate_sine(float in_angle) {
	return std::sin(in_angle * (pi / plane_angle));
}

static float calculate_cosine(float in_angle) {
	return std::cos(in_angle * (pi / plane_angle));
}
