#include "main.h"
#include "rc.h"

int size_dialog::idd() const {
	return IDD_SIZE; 
}

bool size_dialog::on_init_dialog(){
	SetDlgItemInt(*this, IDC_EDIT1, BOARD_SIZE_W, false);
	SetDlgItemInt(*this, IDC_EDIT2, BOARD_SIZE_H, false);
	return true;
}

bool size_dialog::on_ok(){
	BOARD_SIZE_W = GetDlgItemInt(*this, IDC_EDIT1, NULL, false);
	BOARD_SIZE_H = GetDlgItemInt(*this, IDC_EDIT2, NULL, false);
	return true;
}


void main_window::on_paint(HDC hdc){
	
	HBRUSH blackBrush = CreateSolidBrush(squareColor);
	RECT rc;
	GetClientRect(*this, &rc);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, rc.right, rc.bottom, NULL);
	SetWindowExtEx(hdc, boardWidth, boardHeight, NULL);


	 
	for (int i = 0; i < boardWidth; i++) {
		for (int j = i % 2; j < boardHeight; j += 2) {
			RECT square = { i, j, i + 1, j + 1 };
			FillRect(hdc, &square, blackBrush);
		}
	}
	DeleteObject(blackBrush);

}

COLORREF chooseCustomColor[16] = { 0 };

COLORREF get_color(HWND parent, COLORREF color) {
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.hwndOwner = parent;
	cc.lpCustColors = chooseCustomColor;
	cc.rgbResult = color;
	if (ChooseColor(&cc))
		color = cc.rgbResult;
	return color;
}

void main_window::on_command(int id)
{
	switch (id) 
	{
	case ID_SIZE: 
	{
				size_dialog dlg;
				dlg.BOARD_SIZE_W = boardWidth;
				dlg.BOARD_SIZE_H = boardHeight;

				if (dlg.do_modal(0, *this) == IDOK)
				{
					boardWidth = dlg.BOARD_SIZE_W;
					boardHeight = dlg.BOARD_SIZE_H;
					InvalidateRect(*this, NULL, true);

				}

				break;
	}
	case ID_COLOR: 
	{
		squareColor = get_color(*this, squareColor);
		InvalidateRect(*this, nullptr, true);
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
