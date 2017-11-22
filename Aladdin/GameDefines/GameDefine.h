#pragma once
namespace Define
{
#pragma region PLAYER
    const float PLAYER_MAX_JUMP_VELOCITY = 450.0f; //van toc nhay lon nhat
    const float PLAYER_MIN_JUMP_VELOCITY = -450.0f; //van toc nhay thap nhat
    const float PLAYER_MAX_RUNNING_SPEED = 300.0f; //toc do chay nhanh nhat cua player
	const float PLAYER_MAX_JUMPING_SPEED = 400.0f; //toc do bay nhanh nhat cua player khi nhay
	const float PLAYER_MAX_HURT_SPEED = 200.0f; //toc do chay nhanh nhat cua player khi bi thuong hoac attack
	const float PLAYER_MAX_VERTICAL_CLIMBING_SPEED = 100.0f; //toc do leo chieu doc nhanh nhat cua player
	const float PLAYER_MAX_HORIZONTAL_CLIMBING_SPEED = 100.0f; //toc do leo chieu ngang nhanh nhat cua player
    const float PLAYER_BOTTOM_RANGE_FALLING = 1.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
	const float PLAYER_RUN_SPEED_X = 30.0f; //toc do chay player
	const float PLAYER_JUMP_SPEED_X= 40.0f; //toc do bay player khi nhay
	const float PLAYER_FALL_SPEED_Y = 20.0f; //toc do roi player
	const float PLAYER_CLIM_SPPED = 5.0f; //toc do leo player
#pragma endregion

#pragma region BRICK
	const float APPLE_MAX_SPEED = 2500.0f; //toc do bay max cua apple
	const float APPLE_SPEED = 100.0f; //toc do bay cua apple
	const float SWORDFATGUARD_MAX_SPEED = 1500.0f; //toc do bay max cua sword
	const float SWORDFATGUARD_SPEED = 30.0f; //toc do bay cua sowrd
#pragma endregion

	const float DANGEROUS_AREA_MIN = 0.0f; //vung nguy hiem khi player buoc vao co the se gap oroku
	const float DANGEROUS_AREA_MAX = 200.0f; //vung nguy hiem khi player buoc vao co the se gap oroku
	const float AREA_OROKU_RUNAROUND = 50.0f; //vung nguy hiem khi player buoc vao co the se gap oroku

#pragma region OROKU
	const float OROKU_MAX_RUNNING_SPEED = 100.0f;
	const float OROKU_MAX_HURTING_SPEED = 500.0f;
	const float OROKU_NORMAL_SPPED_X = 15.0f;
	const float OROKU_HURT_SPPED_X = 50.0f;
#pragma endregion

}
