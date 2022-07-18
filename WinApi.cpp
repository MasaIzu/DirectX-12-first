#include"WinApi.h"


// @brief コンソール画面にフォーマット付き文字列の表示
// @param format フォーマット(%dとか%fとかの)
// @param 可変長引数
// @remarks この関数はデバック用です。デバッグ時にしか動作しません
void WinApi::DebugOutputFormatString(const char* format, ...) {
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif
}

LRESULT WinApi::WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//ウィンドウが破壊されたら呼ばれる
	if (msg == WM_DESTROY) {
		PostQuitMessage(0);//OSに対して「このアプリはもう終わる」と伝える
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


WinApi::WinApi() {

#pragma region WindowsAPI初期化処理


	//WNDCLASSEX w = {};
	//w.cbSize = sizeof(WNDCLASSEX);
	//w.lpfnWndProc = (WNDPROC)WinApi::WindowProcedure;	//ウィンドウプロシージャを設定
	//w.lpszClassName = _T("DX12Sample");			//ウィンドウクラス名
	//w.hInstance = GetModuleHandle(nullptr);		//ウィンドウハンドル
	//w.hCursor = LoadCursor(NULL, IDC_ARROW);	//カーソル指定

	////ウィンドウクラスをOSに登録する
	//RegisterClassEx(&w);
	////ウィンドウサイズ{X座標　Y座標　横幅　縦幅}
	//RECT wrc = { 0,0,window_width,window_height };
	////関数を使ってウィンドウのサイズを自動で補正する
	//AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	////ウィンドウオブジェクトの生成
	//HWND hwnd = CreateWindow(w.lpszClassName,//クラス名指定
	//	_T("LE2B_16_イズミダ_マサト_AL3"),					//タイトルバーの文字
	//	WS_OVERLAPPEDWINDOW,			//タイトルバーと境界線があるウィンドウ
	//	CW_USEDEFAULT,					//表示x座標はOSにお任せ
	//	CW_USEDEFAULT,					//表示y座標はOSにお任せ
	//	wrc.right - wrc.left,			//ウィンドウ幅
	//	wrc.bottom - wrc.top,			//ウィンドウ高
	//	nullptr,						//親ウィンドウハンドル
	//	nullptr,						//メニューハンドル
	//	w.hInstance,					//呼び出しアプリケーションハンドル
	//	nullptr);						//追加パラメーター(オプション)

	////ウィンドウ表示
	//ShowWindow(hwnd, SW_SHOW);

	//MSG msg = {};

#pragma endregion

}