#pragma once
namespace Define
{
#pragma region PLAYER
    const float PLAYER_MAX_JUMP_VELOCITY = 800.0f; //van toc nhay lon nhat
    const float PLAYER_MIN_JUMP_VELOCITY = -800.0f; //van toc nhay thap nhat
    const float PLAYER_MAX_RUNNING_SPEED = 500.0f; //toc do chay nhanh nhat cua player
	const float PLAYER_MAX_HURT_SPEED = 200.0f; //toc do chay nhanh nhat cua player khi bi thuong hoac attack
	const float PLAYER_MAX_VERTICAL_CLIMBING_SPEED = 200.0f; //toc do leo chieu doc nhanh nhat cua player
	const float PLAYER_MAX_HORIZONTAL_CLIMBING_SPEED = 200.0f; //toc do leo chieu ngang nhanh nhat cua player
    const float PLAYER_BOTTOM_RANGE_FALLING = 1.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
	const float PLAYER_NORMAL_SPEED_X = 50.0f; //toc do player truc x luc binh thuong
	const float PLAYER_HURT_SPEED_X = 10.0f; //toc do player truc x luc bi thuong hoac attack
	const float PLAYER_JUMP_SPEED_Y = 50.0f; //toc do nhay player
	const float PLAYER_FALL_SPEED_Y = 70.0f; //toc do nhay player
	const float PLAYER_CLIM_SPPED = 15.0f; //toc do leo player
#pragma endregion

#pragma region APPLE
	const float APPLE_MAX_SPEED = 2500.0f; //toc do bay max cua apple
	const float APPLE_SPEED = 100.0f; //toc do bay cua apple
#pragma endregion

	const float DANGEROUS_AREA_MIN = 0.0f; //vung nguy hiem khi player buoc vao co the se gap oroku
	const float DANGEROUS_AREA_MAX = 200.0f; //vung nguy hiem khi player buoc vao co the se gap oroku
	const float AREA_OROKU_RUNAROUND = 50.0f; //vung nguy hiem khi player buoc vao co the se gap oroku

#pragma region OROKU
	const float OROKU_MAX_RUNNING_SPEED = 100.0f;
	const float OROKU_NORMAL_SPPED_X = 15.0f;
#pragma endregion

}
