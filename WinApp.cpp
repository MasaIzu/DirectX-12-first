#include"WinApp.h"


// @brief コンソール画面にフォーマット付き文字列の表示
// @param format フォーマット(%dとか%fとかの)
// @param 可変長引数
// @remarks この関数はデバック用です。デバッグ時にしか動作しません
void WinApp::DebugOutputFormatString(const char* format, ...) {
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif
}

LRESULT WinApp::WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//ウィンドウが破壊されたら呼ばれる
	if (msg == WM_DESTROY) {
		PostQuitMessage(0);//OSに対して「このアプリはもう終わる」と伝える
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


MSG WinApp::Msg()
{
	return this->msg;
}



WinApp::WinApp() {

}

void WinApp::WinApiInitialize()
{

#pragma region WindowsAPI初期化処理


	wndClass_ = {};
	wndClass_.cbSize = sizeof(WNDCLASSEX);
	wndClass_.lpfnWndProc = (WNDPROC)WinApp::WindowProcedure;	//ウィンドウプロシージャを設定
	wndClass_.lpszClassName = _T("DX12Sample");			//ウィンドウクラス名
	wndClass_.hInstance = GetModuleHandle(nullptr);		//ウィンドウハンドル
	wndClass_.hCursor = LoadCursor(NULL, IDC_ARROW);	//カーソル指定

	//ウィンドウクラスをOSに登録する
	RegisterClassEx(&wndClass_);
	//ウィンドウサイズ{X座標　Y座標　横幅　縦幅}
	wrc = { 0,0,kWindowWidth,kWindowHeight };
	//関数を使ってウィンドウのサイズを自動で補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウオブジェクトの生成
	hwnd_ = CreateWindow(wndClass_.lpszClassName,//クラス名指定
		_T("LE2B_16_イズミダ_マサト_AL3"),					//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,			//タイトルバーと境界線があるウィンドウ
		CW_USEDEFAULT,					//表示x座標はOSにお任せ
		CW_USEDEFAULT,					//表示y座標はOSにお任せ
		wrc.right - wrc.left,			//ウィンドウ幅
		wrc.bottom - wrc.top,			//ウィンドウ高
		nullptr,						//親ウィンドウハンドル
		nullptr,						//メニューハンドル
		wndClass_.hInstance,					//呼び出しアプリケーションハンドル
		nullptr);						//追加パラメーター(オプション)

	//ウィンドウ表示
	ShowWindow(hwnd_, SW_SHOW);

	msg = {};

#pragma endregion

}

void WinApp::Updata() {

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}

void WinApp::WinAppFinish()
{

#pragma region  WindowsAPI後始末

	//もうクラスは使わないので登録を解除する
	UnregisterClass(wndClass_.lpszClassName, wndClass_.hInstance);

#pragma endregion

}



