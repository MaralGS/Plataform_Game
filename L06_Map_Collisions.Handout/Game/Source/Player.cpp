#include "Player.h"

#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Collisions.h"
#include "Scene.h"


Player::Player() : Module()
{
	//idle anim
	idle.PushBack({ 4, 4, 20, 36 });
	idle.PushBack({ 51, 4, 21, 36 });
	idle.PushBack({ 99, 4, 21, 36 });
	idle.PushBack({ 148, 4, 20, 36 });
	idle.loop = true;
	idle.speed = 0.02f;


	idleE.PushBack({ 150, 42, 20, 36 });
	idleE.PushBack({ 102, 42, 21, 36 });
	idleE.PushBack({ 54, 42, 21, 36 });
	idleE.PushBack({ 6, 42, 20, 36 });
	idleE.loop = true;
	idleE.speed = 0.02f;



	//mode Dreta sprites
	MoveD.PushBack({ 2, 80, 24, 34 });
	MoveD.PushBack({ 55, 81, 16, 33 });
	MoveD.PushBack({ 96, 81, 31, 33 });
	MoveD.PushBack({ 146, 80, 31, 33 });
	MoveD.PushBack({ 199, 81, 16, 33 });
	MoveD.PushBack({ 240, 81, 28, 33 });
	MoveD.loop = true;
	MoveD.speed = 0.02f;

	//mode Esquerra sprites
	MoveE.PushBack({ 246, 116, 24, 34 });
	MoveE.PushBack({ 201, 117, 16, 33 });
	MoveE.PushBack({ 145, 117, 31, 33 });
	MoveE.PushBack({ 57, 117, 16, 33 });
	MoveE.PushBack({ 4, 117, 28, 33 });
	MoveE.loop = true;
	MoveE.speed = 0.02f;

	JumpD.PushBack({ 2, 246, 26, 32 });
	JumpD.PushBack({ 55, 245, 16, 33 });
	JumpD.PushBack({ 99, 243, 19, 35 });
	JumpD.PushBack({ 147, 237, 19, 37 });
	JumpD.PushBack({ 194, 241, 19, 34 });
	JumpD.PushBack({ 246, 246, 17, 32 });
	JumpD.loop = false;
	JumpD.speed = 0.06f;

	JumpE.PushBack({ 237, 294, 26, 32 });
	JumpE.PushBack({ 194, 293, 16, 33 });
	JumpE.PushBack({ 147, 291, 19, 35 });
	JumpE.PushBack({ 99, 285, 19, 37 });
	JumpE.PushBack({ 52, 289, 19, 34 });
	JumpE.PushBack({ 2, 294, 17, 32 });
	JumpE.loop = false;
	JumpE.speed = 0.02f;
}

Player::~Player()
{

}

bool Player::Start()
{
	bool ret = true;
	Dead.Reset();
	currentAnimation = &idle;
	
	player = app->tex->Load("Assets/textures/SteamMan/Sprites.png");

	/*
	position.x = 40;
	position.y = 24;*/

	// L10: DONE 4: Retrieve the player when playing a second time
	win = false;
	stop = false;

	// L6: DONE 3: Add a collider to the player
	collider = app->collisions->AddCollider({ playerX, playerY }, Collider::Type::PLAYER);

	return ret;
}

/*
UpdateResult ModulePlayer::Update()
{

	prevposition = position;
	// Get gamepad info
	GamePad& pad = App->input->pads[0];

	// Moving the player with the camera scroll
	App->player->position.x += 0;

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_1] == KeyState::KEY_DOWN)
	{
		App->input->ShakeController(0, 12, 0.33f);
	}

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_2] == KeyState::KEY_DOWN)
	{
		App->input->ShakeController(0, 36, 0.66f);
	}

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_3] == KeyState::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 1.0f);
	}

	// L10: TODO: Implement gamepad support

	/*if (pads->left_x < 0.0f) {
		(App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT))
	}*/
/*
	if (App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT || pad.left_x < 0.0f)
	{
		position.x -= speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT || pad.left_x > 0.0f)
	{
		position.x += speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT || pad.left_y > 0.0f)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT || pad.left_y < 0.0f)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if ((App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_DOWN || pad.x == true)) //|| (pad.x))
	{
		if (App->Placebomb->BombUp == true) {
			App->particles->bom.position.x = App->player->position.x;
			App->particles->bom.position.y = App->player->position.y;
			App->Placebomb->PutBomb();
			App->Placebomb->BombUp = false;
			App->Placebomb->ExplosionUp = true;
		}
		//App->Placebomb->DrawBomb();
	}

	//Debbug Keys

	//godmode
	if (App->input->keys[SDL_SCANCODE_F1] == KeyState::KEY_DOWN) {
		godmode = !godmode;
	}

	// Switch gamepad debug info && show colliders
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debugGamepadInfo = !debugGamepadInfo;


	//spawn enemy robot
	if (App->input->keys[SDL_SCANCODE_F9] == KeyState::KEY_DOWN)
		App->enemies->AddEnemy(Enemy_Type::BROWNROBOT, 53, 155);

	//spawn enemy rabbit
	if (App->input->keys[SDL_SCANCODE_F10] == KeyState::KEY_DOWN)
		App->enemies->AddEnemy(Enemy_Type::RABBIT, 150, 200);

	//spawn enemy snail
	if (App->input->keys[SDL_SCANCODE_F11] == KeyState::KEY_DOWN)
		App->enemies->AddEnemy(Enemy_Type::CARGOL, 182, 114);

	//spawn powerup bomb+1
	if (App->input->keys[SDL_SCANCODE_F6] == KeyState::KEY_DOWN)


		//spawn powerUp ?
		if (App->input->keys[SDL_SCANCODE_F7] == KeyState::KEY_DOWN)


			//spawn powerUp invincible
			if (App->input->keys[SDL_SCANCODE_F8] == KeyState::KEY_DOWN)



				//insta win
				if (App->input->keys[SDL_SCANCODE_F3] == KeyState::KEY_REPEAT)
				{
					App->audio->PlayFx(winFx);
					win = true;
				}

	//insta lose
	if (App->input->keys[SDL_SCANCODE_F4] == KeyState::KEY_DOWN)
	{
		lifes = 0;
		App->audio->PlayFx(deadFx);
	}

	//close game
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KeyState::KEY_DOWN) {
		return UpdateResult::UPDATE_STOP;
	}




	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE) {
		if (lifes > 0 && stop == false)
		{
			currentAnimation = &idleAnim;
		}

	}

	// L6: DONE 4: Update collider position to player position
	collider->SetPos(position.x, position.y + 7);

	currentAnimation->Update();

	// Update shot countdown
	if (shotCountdown > 0) --shotCountdown;

	if (powerTouch == true) {
		if (timer < 150) {
			timer++;
		}
		if (timer == 150) {
			powerTouch = false;
			timer = 0;
		}
	}

	if (death == true)
	{
		if (lifes != 0) {
			if (App->sceneLevel_1->inLevel1 == true)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_1, 160);
			}
			if (App->sceneLevel_2->inLevel2 == true)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_2, (Module*)App->sceneLevel_2, 160);
			}
			if (App->sceneLevel_Boss->inLevel3 == true)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_Boss, (Module*)App->sceneLevel_Boss, 160);
			}

			currentAnimation = &deadAnim;
			destroyed = true;
			death = false;
		}
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneDeath, 160);
	}

	return UpdateResult::UPDATE_CONTINUE;
}
*/

bool Player::PostUpdate()
{
	int dx = 0;
	int dy = 0;
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		dx = 1;
		if (currentAnimation != &MoveD)
		{
			MoveD.Reset();
			currentAnimation = &MoveD;
		}

	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		if (currentAnimation != &idle)
		{
			idle.Reset();
			currentAnimation = &idle;
		}

	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		dx = -1;
		if (currentAnimation != &MoveE)
		{
			MoveE.Reset();
			currentAnimation = &MoveE;
		}

	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		if (currentAnimation != &idleE)
		{
			idleE.Reset();
			currentAnimation = &idleE;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		dy = 1;
		if (currentAnimation != &JumpD)
		{
			JumpD.Reset();
			currentAnimation = &JumpD;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{

		if (currentAnimation != &JumpD)
		{
			JumpD.Reset();
			currentAnimation = &JumpD;

		}
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{

		if (currentAnimation != &JumpE)
		{
			JumpE.Reset();
			currentAnimation = &JumpE;
		}
	}

	//jump
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !isJumping)
	{
		yVel = 3.5;
		isJumping = true;
	}
	dy = -yVel;

	if (dx != 0 || dy != 0)
	{
		playerX += dx;
		playerY += dy;
	}

	if (playerY < app->scene->TerraY) {
		yVel -= 0.04;
	}


	//dead
	/*if (dead == true)
	{
		playerX = 60;
		playerY = 0;
		vides--;
		dead = false;
	}

	if (playerX == 300)
	{
		dead = true;
	}*/

	
	else {
		yVel = 0;
		isJumping = false;
		playerY = app->scene->TerraY;
		if (app->input->GetKey(SDL_SCANCODE_D) != KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_A) != KEY_REPEAT) {

		}
	}

	//draw player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(player, playerX, playerY, &rect);

	return true;
}


void Player::OnCollision(Collider* c1, Collider* c2)
{
	if ((c1 == collider) && (destroyed == false))
	{
		if (c1 == collider && destroyed == false) {
			switch (c2->type) {
			case Collider::Type::WALL:
				if (c1->rect.y < c2->rect.y) // up
				{
					playerY -= 0.8f;
				}
				else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) // down
				{
					playerY += 0.8f;
				}
				if (c1->rect.x < c2->rect.x) // left
				{
					playerX -= 0.8f;
				}
				else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) // right
				{
					playerX += 0.8f;
				}; break;
			case Collider::Type::DEATH:
				break;
			case Collider::Type::FINISH:
				break;
			}
		}
	}
}
