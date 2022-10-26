#include "EnemyPop.h"
#include <stdlib.h>
#include"Player.h"
#include "wing.h"
#include <time.h>

EnemyPop::EnemyPop() {

	collision_ = new Collision();
	TrafficAccidentFlag = 0;
	overTakingCount = 0;
}

void EnemyPop::LoadTexture()
{
	puriusModel = Model::CreateFromOBJ("puriusu", true);
	trakuModel = Model::CreateFromOBJ("trakku", true);
	ferariModel = Model::CreateFromOBJ("CarFerari", true);
	GoalEnemyModel = Model::CreateFromOBJ("GoalCar", true);
	GoalFlagOBJModel = Model::CreateFromOBJ("GoalFlag", true);
}

void EnemyPop::Initialize()
{
	enemy1.clear();
	popTimer = 0;
	popInterval = 2 * 60;
	overTakingCount = 0;
	GoalEnemy.release();
	GoalFlagOBJ.release();
}

void EnemyPop::Update(Model* model)
{
	popTimer++;

	// 敵のデスフラグが立っていたらリストから消す
	enemy1.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->IsDead(); });

	// プレイヤーのスピードに応じて敵のポップの間隔を上げる
	popInterval = 3 * 60 - (10 * player_->GetPlayerSpeed());


	// タイマーが間隔時間になったらランダムに生成と車種を抽選して、設定する
	if (overTakingCount <= 200) {
		if (popTimer >= popInterval) {

			carPattern_ = rand() % 5 + 1;
			switch (carPattern_)
			{
			case 1:// 車の生成パターン---------------１
				for (int i = 0; i < 3; i++) {

					// 車種のパターンを設定
					CarModelLottery();

					// 敵を生成し、初期化
					std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
					newEnemy->SetPlayer(player_);
					if (carModelnum_ == 1) {
						newEnemy->Initialize(trakuModel, enemyPos1[i], carModel_);
					}
					else if (carModelnum_ == 2) {
						newEnemy->Initialize(puriusModel, enemyPos1[i], carModel_);
					}
					else if (carModelnum_ == 3) {
						newEnemy->Initialize(ferariModel, enemyPos1[i], carModel_);
					}
					// 敵をリストに登録
					enemy1.push_back(std::move(newEnemy));
				}

				// 生成タイマーを初期化
				popTimer = 0;

				break;
			case 2:// 車の生成パターン---------------２
				for (int i = 0; i < 3; i++) {

					// 車種のパターンを設定
					CarModelLottery();

					// 敵を生成し、初期化
					std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
					newEnemy->SetPlayer(player_);
					if (carModelnum_ == 1) {
						newEnemy->Initialize(trakuModel, enemyPos2[i], carModel_);
					}
					else if (carModelnum_ == 2) {
						newEnemy->Initialize(puriusModel, enemyPos2[i], carModel_);
					}
					else if (carModelnum_ == 3) {
						newEnemy->Initialize(ferariModel, enemyPos2[i], carModel_);
					}


					// 敵をリストに登録
					enemy1.push_back(std::move(newEnemy));
				}

				// 生成タイマーを初期化
				popTimer = 0;
				break;
			case 3:// 車の生成パターン---------------３
				for (int i = 0; i < 3; i++) {

					// 車種のパターンを設定
					CarModelLottery();

					// 敵を生成し、初期化
					std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
					newEnemy->SetPlayer(player_);

					if (carModelnum_ == 1) {
						newEnemy->Initialize(trakuModel, enemyPos3[i], carModel_);
					}
					else if (carModelnum_ == 2) {
						newEnemy->Initialize(puriusModel, enemyPos3[i], carModel_);
					}
					else if (carModelnum_ == 3) {
						newEnemy->Initialize(ferariModel, enemyPos3[i], carModel_);
					}


					// 敵をリストに登録
					enemy1.push_back(std::move(newEnemy));
				}

				// 生成タイマーを初期化
				popTimer = 0;
				break;
			case 4:
				for (int i = 0; i < 4; i++) {
					// 車種のパターンを設定
					CarModelLottery();

					// 敵を生成し、初期化
					std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
					newEnemy->SetPlayer(player_);

					if (carModelnum_ == 1) {
						newEnemy->Initialize(trakuModel, enemyPos4[i], carModel_);
					}
					else if (carModelnum_ == 2) {
						newEnemy->Initialize(puriusModel, enemyPos4[i], carModel_);
					}
					else if (carModelnum_ == 3) {
						newEnemy->Initialize(ferariModel, enemyPos4[i], carModel_);
					}

					// 敵をリストに登録
					enemy1.push_back(std::move(newEnemy));
				}
				// 生成タイマーを初期化
				popTimer = 0;
				break;
			case 5:
				for (int i = 0; i < 4; i++) {
					// 車種のパターンを設定
					CarModelLottery();

					// 敵を生成し、初期化
					std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
					newEnemy->SetPlayer(player_);

					if (carModelnum_ == 1) {
						newEnemy->Initialize(trakuModel, enemyPos5[i], carModel_);
					}
					else if (carModelnum_ == 2) {
						newEnemy->Initialize(puriusModel, enemyPos5[i], carModel_);
					}
					else if (carModelnum_ == 3) {
						newEnemy->Initialize(ferariModel, enemyPos5[i], carModel_);
					}

					// 敵をリストに登録
					enemy1.push_back(std::move(newEnemy));
				}
				// 生成タイマーを初期化
				popTimer = 0;
				break;
			default:
				break;
			}
		}
	}

	if (overTakingCount == 200) {
		goalFlag = true;

	}
	if (goalFlag == true) {

		GoalEnemy = std::make_unique<Enemy>();
		GoalFlagOBJ = std::make_unique<Enemy>();
		GoalEnemy->SetPlayer(player_);
		GoalFlagOBJ->SetPlayer(player_);
		GoalEnemy->Initialize(GoalEnemyModel, GoalEnemyPos, CarModel::ferrari);
		GoalFlagOBJ->Initialize(GoalFlagOBJModel, GoalEnemyPos, CarModel::ferrari);
		goalFlag = false;
	}
	if (GoalEnemy != nullptr)
	{
		GoalEnemy->Update();
		GoalFlagOBJ->Update();
	}
	// 敵の更新処理の呼び出し
	for (std::unique_ptr<Enemy>& enemy : enemy1) {
		for (std::unique_ptr<Enemy>& enemy2 : enemy1) {
			// 自分自身とは判定とらないようにする処理
			if (enemy->GetPos().x == enemy2->GetPos().x &&
				enemy->GetPos().y == enemy2->GetPos().y &&
				enemy->GetPos().z == enemy2->GetPos().z) {
			}
			else {
				Vector3 pos = enemy2->GetPos();

				// 一番左のレーンをチェック
				enemy->Lane1ChangeCheck(pos);

				// 一番右のレーンチェック
				enemy->Lane5ChangeCheck(pos);

				// それ以外の時のチェック
				if (enemy->lane1ChangeFlag() == false && enemy->lane5ChangeFlag() == false) {
					enemy->LaneChangeCheck(pos);
				}

				// 前に別の車がいたら右もしくは左に移動可能かチェックする
				if (enemy->laneChangeFlag() == true) {
					if (enemy->leftLaneChangeFlag() == false && enemy->rightLaneChangeFlag() == false) {
						for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
							// 自分自身とは判定とらないようにする処理
							if (enemy->GetPos().x == enemy3->GetPos().x &&
								enemy->GetPos().y == enemy3->GetPos().y &&
								enemy->GetPos().z == enemy3->GetPos().z) {
							}
							else {
								Vector3 pos = enemy3->GetPos();

								// 左に移動可能かチェック
								if (enemy->rightLaneChangeFlag() == false) {
									enemy->LeftLaneChangeCheck(pos);

									if (enemy->leftLaneChangeFlag() == false) {
										// 左が無理だった場合に右に移動可能かチェック
										enemy->RightLaneChangeCheck(pos);

										// 右が可能なら
										if (enemy->rightLaneChangeFlag() == true) {
											enemy->SetLeftLaneChangeFlag(false);
										}
										// どっちも無理だった場合処理を抜ける
										if (enemy->rightLaneChangeFlag() == false) {
											break;
										}
									}
								}
							}
						}
					}
				}

				// 一番左の時右に移動可能かチェックする
				if (enemy->lane1ChangeFlag() == true) {
					for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
						// 自分自身とは判定とらないようにする処理
						if (enemy->GetPos().x == enemy3->GetPos().x &&
							enemy->GetPos().y == enemy3->GetPos().y &&
							enemy->GetPos().z == enemy3->GetPos().z) {
						}
						else {
							Vector3 pos = enemy3->GetPos();

							if (enemy->rightLaneChangeFlag() == false) {
								// 右に移動可能かチェック
								enemy->RightLaneChangeCheck(pos);
							}
						}
					}
				}

				// 一番右の時左に移動可能かチェックする
				if (enemy->lane5ChangeFlag() == true) {
					for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
						// 自分自身とは判定とらないようにする処理
						if (enemy->GetPos().x == enemy3->GetPos().x &&
							enemy->GetPos().y == enemy3->GetPos().y &&
							enemy->GetPos().z == enemy3->GetPos().z) {
						}
						else {
							Vector3 pos = enemy3->GetPos();

							if (enemy->leftLaneChangeFlag() == false)
							{
								// 左に移動可能かチェック
								enemy->LeftLaneChangeCheck(pos);
							}

						}
					}
				}
			}
		}
		enemy->Update();

		if (player_->GetPlayerPos().z > enemy->GetPos().z) {
			if (enemy->playerOverTaking == 0) {
				enemy->playerOverTaking = 1;
				overTakingCount++;
			}
		}
	}


	CarBack();
	TrafficAccidentEnemyVer();

}

void EnemyPop::Draw(const ViewProjection& viewProjection)
{
	//敵キャラの描画
	for (std::unique_ptr<Enemy>& enemy : enemy1) {
		enemy->Draw(viewProjection);
	}
	if (GoalEnemy != nullptr) {
		GoalEnemy->Draw(viewProjection);
		GoalFlagOBJ->Draw(viewProjection);
	}
}

void EnemyPop::CarBack() {

	Vector3 PlayerVec = player_->GetPlayerPos();
	Vector3 Psize = { 5,5,500 };
	Vector3 Esize = { 5,5,5 };
	for (std::unique_ptr<Enemy>& enemy : enemy1) {

		Vector3 enemyPos_ = enemy->GetWorldTransform().translation_;
		if (collision_->BoxCollision(PlayerVec, enemyPos_, Psize, Esize, true) == true) {
			player_->EnemyCarBack();
			wing_->Distance();
		}
	}
}

void EnemyPop::TrafficAccidentEnemyVer() {

	Vector3 PlayerVec = player_->GetPlayerPos();
	Vector3 Psize = { 2.0f,2,5 };
	Vector3 Esize = { 5,6,5 };
	for (std::unique_ptr<Enemy>& enemy : enemy1) {

		Vector3 enemyPos_ = enemy->GetWorldTransform().translation_;
		if (collision_->BoxCollision(PlayerVec, enemyPos_, Psize, Esize) == true) {
			TrafficAccidentFlag = 1;
			player_->TrafficAccidentFlag();
		}
		/*else {
			TrafficAccidentFlag = 0;
		}*/
	}

}

int EnemyPop::GetTrafficAccidentFlag() {

	return TrafficAccidentFlag;
}

float EnemyPop::GetGoalEmemyPos()
{
	if (GoalEnemy != NULL) {
		return GoalEnemy->GetPos().z;
	}
	return 100.0f;
}

void EnemyPop::CarModelLottery()
{
	// 車種のパターンを抽選
	carModelnum_ = rand() % 3 + 1;

	// 車種のパターンを設定
	if (carModelnum_ == 1)
	{
		carModel_ = CarModel::truck;
	}
	else if (carModelnum_ == 2) {
		carModel_ = CarModel::prius;
	}
	else if (carModelnum_ == 3) {
		carModel_ = CarModel::ferrari;
	}
}

int EnemyPop::GetEnemyOverTakingCount()
{
	return overTakingCount;
}