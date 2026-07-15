#pragma once
#include <DxLib.h>
#include "UIWidgetComponent.h"

class AICanvas : public MUIWidgetComponent {
 public:
  AICanvas();
  virtual ~AICanvas() override;

  // ライフサイクル関数 (BroccoliEngineの基本設計に準拠)
  virtual void Initialize();
  virtual void OnUpdate(float deltaTime) override;
  virtual void OnDraw();
  virtual void OnDestroy();

  // 利便性のためのユーティリティ
  void ClearCanvas();
  void SetPenColor(unsigned int color) { m_penColor = color; }
  void SetPenSize(int size) { m_penSize = size; }

  // ゲッター
  int GetCanvasScreen() const { return m_canvasScreen; }

 private:
  int m_canvasScreen;  // キャンバス用のオフスクリーンハンドル
  int m_width;         // キャンバスの幅
  int m_height;        // キャンバスの高さ

  int m_prevX;       // 前回のマウス座標 (ローカル空間)
  int m_prevY;       // 前回のマウス座標 (ローカル空間)
  bool m_isDrawing;  // 描画中フラグ

  unsigned int m_penColor;  // ペンの色 (DxLibのカラーコード)
  int m_penSize;            // ペンの太さ (ピクセル)

 private:
  // マウスがキャンバス（ウィジェット）の矩形内にあるか判定
  bool IsMouseOver(int mouseX, int mouseY) const;

  // スクリーン座標をキャンバスの左上基準のローカル座標に変換
  void ConvertToLocalSpace(int mouseX, int mouseY, int& outX, int& outY) const;
};