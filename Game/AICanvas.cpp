#include "AICanvas.h"
#include "Umath.h"
// 必要に応じて InputManager.h や RenderSystem.h などのエンジンヘッダをインクルードしてください

AICanvas::AICanvas()
    : m_canvasScreen(-1),
      m_width(0),
      m_height(0),
      m_prevX(0),
      m_prevY(0),
      m_isDrawing(false),
      m_penColor(GetColor(255, 255, 255))  // デフォルトは白色
      ,
      m_penSize(8)  // デフォルトの太さ
{}

AICanvas::~AICanvas() {
  // 安全のためデストラクタでも破棄処理を呼ぶ
  AICanvas::OnDestroy();
}

void AICanvas::Initialize() {

  // ウィジェット自身のサイズをキャンバスサイズとして採用
  // (Vector2 や構造体はエンジンの定義に合わせて調整してください)
  FVector2D size = GetWidgetSize();
  m_width = static_cast<int>(size.X);
  m_height = static_cast<int>(size.Y);

  // 1. アルファチャンネル(透過)付きのオフスクリーン（レンダーターゲット）を生成
  m_canvasScreen = MakeScreen(m_width, m_height, TRUE);

  // 2. 初期状態でキャンバスを透明にクリアする
  ClearCanvas();
}

void AICanvas::ClearCanvas() {
  if (m_canvasScreen == -1) return;

  // 【重要】現在の描画先ターゲットを退避
  int prevDrawScreen = GetDrawScreen();

  // 描画先をキャンバスに切り替えてクリア
  SetDrawScreen(m_canvasScreen);
  ClearDrawScreen();

  // 【重要】描画先を元のターゲットに復元
  SetDrawScreen(prevDrawScreen);
}

void AICanvas::OnUpdate(float deltaTime) {
  MUIWidgetComponent::OnUpdate(deltaTime);

  // 1. マウスの位置と入力を取得 (InputManager等のラップ関数があればそちらに差し替えてください)
  int mouseX = 0, mouseY = 0;
  GetMousePoint(&mouseX, &mouseY);
  bool isLeftClicked = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

  // 2. マウスがウィジェットのホバー領域内にあるか確認
  bool isOver = IsMouseOver(mouseX, mouseY);

  // 描画中、または新規描画開始（ホバー＆クリック時）の処理
  if (isLeftClicked && (m_isDrawing || isOver)) {
    // 現在のマウス位置をローカル座標に変換
    int localX = 0, localY = 0;
    ConvertToLocalSpace(mouseX, mouseY, localX, localY);

    // 【重要】現在の描画先ターゲットを退避
    int prevDrawScreen = GetDrawScreen();
    SetDrawScreen(m_canvasScreen);

    if (!m_isDrawing) {
      // クリック開始時の「点」を打つ（線の始点として丸く描画）
      DrawCircle(localX, localY, m_penSize / 2, m_penColor, TRUE);
      m_isDrawing = true;
    } else {
      // ドラッグ中の「線」を引く
      // 太い線を引いた時に角がカクカクしないよう、終点にも円を描くのが綺麗に描画するコツです
      DrawLine(m_prevX, m_prevY, localX, localY, m_penColor, m_penSize);
      DrawCircle(localX, localY, m_penSize / 2, m_penColor, TRUE);
    }

    // 【重要】描画先を復元
    SetDrawScreen(prevDrawScreen);

    // 座標履歴の更新
    m_prevX = localX;
    m_prevY = localY;
  } else {
    // クリックを離した、または描画中に完全に画面外に逸れた場合はフラグを下ろす
    m_isDrawing = false;
  }
}

void AICanvas::OnDraw() {
  if (m_canvasScreen == -1) return;

  // ウィジェットのスクリーン上のワールド座標を取得
  auto pos = GetWorldLocation();
  int posX = static_cast<int>(pos.X);
  int posY = static_cast<int>(pos.Y);

  // 仕様に基づき、UIのZオーダーに従って裏画面にテクスチャを描画
  // (※RenderSystemに直接ハンドルの描画登録を投げる設計の場合は、
  //  RenderSystem::GetInstance()->RegisterDrawUI(...) のように置き換えてください)
  DrawGraph(posX, posY, m_canvasScreen, TRUE);
}

void AICanvas::OnDestroy() {
  // DxLibが確保したグラフィックス用メモリを解放してメモリリークを防ぐ
  if (m_canvasScreen != -1) {
    DeleteGraph(m_canvasScreen);
    m_canvasScreen = -1;
  }
}

bool AICanvas::IsMouseOver(int mouseX, int mouseY) const {
  auto pos = GetWorldLocation();
  auto size = GetWidgetSize();

  int left = static_cast<int>(pos.X);
  int top = static_cast<int>(pos.Y);
  int right = left + static_cast<int>(size.X);
  int bottom = top + static_cast<int>(size.Y);

  return (mouseX >= left && mouseX <= right && mouseY >= top && mouseY <= bottom);
}

void AICanvas::ConvertToLocalSpace(int mouseX, int mouseY, int& outX, int& outY) const {
  auto pos = GetWorldLocation();
  outX = mouseX - static_cast<int>(pos.X);
  outY = mouseY - static_cast<int>(pos.Y);
}