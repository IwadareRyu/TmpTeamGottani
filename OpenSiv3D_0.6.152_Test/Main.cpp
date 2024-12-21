# include <Siv3D.hpp> // Siv3D v0.6.15
#include "SceneController.h"
#include "UIManager.h"

void Main()
{
	///
	// ウィンドウを 1280x720 にリサイズ
	Window::Resize(1280, 720);

	// 背景色を設定
	Scene::SetBackground(ColorF{ 0.2, 0.7, 1.0 });

	// 登場する絵文字
	const Array<String> emojis = { U"🐘", U"🐧", U"🐐", U"🐤" };

	Array<MultiPolygon> polygons;

	Array<Texture> textures;

	for (const auto& emoji : emojis)
	{
		// 絵文字の画像から形状情報を作成する
		polygons << Emoji::CreateImage(emoji).alphaToPolygonsCentered().simplified(2.0);

		// 絵文字の画像からテクスチャを作成する
		textures << Texture{ Emoji{ emoji } };
	}

	// 2D 物理演算のシミュレーションステップ（秒）
	constexpr double StepTime = (1.0 / 200.0);

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	double accumulatedTime = 0.0;

	// 2D 物理演算のワールド
	P2World world;

	// [_] 地面
	const P2Body ground = world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -300, 0, 300, 0 });

	// 動物の物体
	Array<P2Body> bodies;

	// 物体の ID と絵文字のインデックスの対応テーブル
	HashTable<P2BodyID, size_t> table;

	// 絵文字のインデックス
	size_t index = Random(polygons.size() - 1);

	// 2D カメラ
	Camera2D camera{ Vec2{ 0, -200 } };

	///

	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	SceneController sceneController;

	UIManager uiManager;

	while (System::Update())
	{
		if (sceneController.M_Scene() == SceneState::TitleScene)
		{
			uiManager.UITitleUpdate();
			if (uiManager.m_titleStartButton.ButtonClicked())
			{
				sceneController.ChangeScene(SceneState::GameScene);
			}
		}
		else if (sceneController.M_Scene() == SceneState::GameScene)
		{
			accumulatedTime += Scene::DeltaTime();

			while (StepTime <= accumulatedTime)
			{
				// 2D 物理演算のワールドを更新する
				world.update(StepTime);

				accumulatedTime -= StepTime;
			}

			// 地面より下に落ちた物体は削除する
			for (auto it = bodies.begin(); it != bodies.end();)
			{
				if (100 < it->getPos().y)
				{
					// 対応テーブルからも削除
					table.erase(it->id());

					it = bodies.erase(it);
				}
				else
				{
					++it;
				}
			}

			// 2D カメラを更新する
			camera.update();
			{
				// 2D カメラから Transformer2D を作成する
				const auto t = camera.createTransformer();

				// 左クリックされたら
				if (MouseL.down())
				{
					// ボディを追加する
					bodies << world.createPolygons(P2Dynamic, Cursor::PosF(), polygons[index], P2Material{ 0.1, 0.0, 1.0 });
					uiManager.AddScoreRef(30);
					// ボディ ID と絵文字のインデックスの組を対応テーブルに追加する
					table.emplace(bodies.back().id(), std::exchange(index, Random(polygons.size() - 1)));
				}

				// すべてのボディを描画する
				for (const auto& body : bodies)
				{
					textures[table[body.id()]].rotated(body.getAngle()).drawAt(body.getPos());
				}

				// 地面を描画する
				ground.draw(Palette::Green);

				// 現在操作できる絵文字を描画する
				textures[index].drawAt(Cursor::PosF(), AlphaF(0.5 + Periodic::Sine0_1(1s) * 0.5));
			}

			// 2D カメラの操作を描画する
			camera.draw(Palette::Orange);

			uiManager.UIGameUpdate();
			if (uiManager.ChackTime())
			{
				uiManager.UIResultInit();
				sceneController.ChangeScene(SceneState::ResultScene);
			}
		}
		else
		{
			uiManager.UIResultUpdate();
			if (uiManager.m_titleStartButton.ButtonClicked())
			{
				uiManager.ResetUI();
				sceneController.ChangeScene(SceneState::TitleScene);
			}
		}

		sceneController.FadeUpdate();
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
