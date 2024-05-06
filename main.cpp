#include "main.h"
#include "rc.h"

int size_dialog::idd() const {
	return IDD_SIZE; 
}

bool size_dialog::on_init_dialog(){
	SetDlgItemInt(*this, IDC_EDIT1, BOARD_SIZE, false);
	return true;
}

bool size_dialog::on_ok(){
	newBoardSize = GetDlgItemInt(*this, IDC_EDIT1, NULL, false);
	return true;
}


void main_window::on_paint(HDC hdc){
	RECT rc;
	GetClientRect(*this, &rc);
	
	int width = BOARD_SIZE * SQUARE_SIZE;
	int height = BOARD_SIZE * SQUARE_SIZE;

	int x = (rc.right - width) / 2;
	int y = (rc.bottom - height) / 2;

	HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH blackBrush;
	if (useCustomColors) {
		blackBrush = CreateSolidBrush(squareColor1);
	}
	else {
		blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	}
	 
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			RECT square = {x + i * SQUARE_SIZE, y + j * SQUARE_SIZE, x + (i + 1) * SQUARE_SIZE, y + (j + 1) * SQUARE_SIZE};
			HBRUSH brush = (i + j) % 2 == 0 ? whiteBrush : blackBrush;
			FillRect(hdc, &square, brush);
		}
	}
	DeleteObject(whiteBrush);
	if (useCustomColors) {
		DeleteObject(blackBrush);
	}
}

void main_window::on_command(int id){
	switch (id) {
	case ID_SIZE: {
				size_dialog dlg;
				if (dlg.do_modal(0, *this) == IDOK)
				{
					BOARD_SIZE = dlg.newBoardSize;
					InvalidateRect(*this, NULL, true);

				}

				break;
	}
	case ID_COLOR: {
		
		CHOOSECOLOR cc;
		COLORREF customColors[16] = { 0 };
		ZeroMemory(&cc, sizeof(cc));
		cc.lStructSize = sizeof(cc);
		cc.hwndOwner = *this;
		cc.lpCustColors = customColors;
		cc.rgbResult = RGB(255, 255, 255);
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;

		if (ChooseColor(&cc) == TRUE) {
			squareColor1 = cc.rgbResult;
			squareColor2 = ~cc.rgbResult;
			useCustomColors = true;
			InvalidateRect(*this, 0, true);
		}
		break;
	}
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window wnd;	
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.run();
}
