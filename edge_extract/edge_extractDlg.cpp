
// edge_extractDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "edge_extract.h"
#include "edge_extractDlg.h"
#include "afxdialogex.h"
#include "filename.h"
#include <string.h>
//#include <iostream>
#include <opencv2/opencv.hpp>

//using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cedge_extractDlg 对话框



Cedge_extractDlg::Cedge_extractDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EDGE_EXTRACT_DIALOG, pParent)
	, m_result(_T(""))
	, m_path(_T(""))
	, m_num(0)
	, m_sys_status(_T(""))
	, m_time(_T(""))
	, m_threshold(125)
	, m_heightshow(_T(""))
	, m_originalsize(_T(""))
	, m_widthshow(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cedge_extractDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_Open, m_button_open);
	DDX_Control(pDX, IDC_BUTTON_Test, m_button_test);
	DDX_Control(pDX, IDC_EDIT_NUM, m_edit_num);
	DDX_Control(pDX, IDC_EDIT_PATH, m_edit_path);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_edit_result);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_result);
	DDX_Text(pDX, IDC_EDIT_PATH, m_path);
	//  DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	DDX_Control(pDX, IDC_BUTTON_Store, m_button_store);
	DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	//  DDX_Control(pDX, IDC_BUTTON_Set, m_);
	DDX_Control(pDX, IDC_BUTTON_Set, m_button_set1);
	DDX_Text(pDX, IDC_EDIT_SYS, m_sys_status);
	DDX_Text(pDX, IDC_EDIT_TIME, m_time);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_threshold);
	//  DDX_Text(pDX, IDC_EDIT_Height, m_originalsize);
	DDX_Text(pDX, IDC_EDIT_Height, m_heightshow);
	DDX_Text(pDX, IDC_EDIT_OSize, m_originalsize);
	DDX_Text(pDX, IDC_EDIT_Width, m_widthshow);
	DDX_Control(pDX, IDC_BUTTON_Contours, m_button_contours);
}

BEGIN_MESSAGE_MAP(Cedge_extractDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Open, &Cedge_extractDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_Test, &Cedge_extractDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_Store, &Cedge_extractDlg::OnBnClickedButtonStore)
	ON_BN_CLICKED(IDC_BUTTON_Set, &Cedge_extractDlg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_Contours, &Cedge_extractDlg::OnBnClickedButtonContours)
END_MESSAGE_MAP()


// Cedge_extractDlg 消息处理程序

BOOL Cedge_extractDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_num = 0;

	// Change the window which contain the image
	namedWindow("im_resource");
	hwnd = (HWND)cvGetWindowHandle("im_resource");
	HWND hparent = ::GetParent(hwnd);
	::SetParent(hwnd, GetDlgItem(IDC_STATIC_PIC1)->m_hWnd);
	::ShowWindow(hparent, SW_HIDE);
	::ShowWindow(hwnd, SW_HIDE);

	// set the font of button control
	m_editFont.CreatePointFont(120, _T("黑体"));
	m_button_open.SetFont(&m_editFont);
	m_button_test.SetFont(&m_editFont);
	m_button_store.SetFont(&m_editFont);
	m_button_set1.SetFont(&m_editFont);
	m_button_contours.SetFont(&m_editFont);

	// set the font of edit control
	/*
	m_edit_path.SetFont(&m_editFont);
	m_edit_num.SetFont(&m_editFont);
	m_edit_result.SetFont(&m_editFont);
	*/

	// set the font of static control

	// initialize the picture control
	pstatic = (CStatic *)GetDlgItem(IDC_STATIC_PIC1);
	GetDlgItem(IDC_STATIC_PIC1)->GetClientRect(&rect_pic1);
	pstatic->GetDC()->FillSolidRect(rect_pic1.left, rect_pic1.top, rect_pic1.Width(), rect_pic1.Height(), RGB(240, 240, 240));

	m_sys_status = _T("Software initialization completed...");
	SetDlgItemText(IDC_EDIT_SYS, m_sys_status);

	return TRUE;  
}

void Cedge_extractDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cedge_extractDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cedge_extractDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// The overwrite founction to deal with "Enter" and "Esc" pressed event
BOOL Cedge_extractDlg::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message) 
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
		{
			switch (GetFocus()->GetDlgCtrlID())
			{
			case IDC_EDIT_THRESHOLD:
				UpdateData(true);
				UpdateData(false);
				return true;
			default:
				return true;
			}
		}
		case VK_ESCAPE:
			return true;
		default:
			;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void Cedge_extractDlg::OnBnClickedButtonOpen()
{
	double height;
	double width;
	string extension;
	CString errorinf;
	pstatic->GetDC()->FillSolidRect(rect_pic1.left, rect_pic1.top, rect_pic1.Width(), rect_pic1.Height(), RGB(240, 240, 240));
	m_sys_status = _T("Choose the image which will be edited...");
	SetDlgItemText(IDC_EDIT_SYS, m_sys_status);
	
	CFileDialog m_file_dialog(TRUE);
	if (!m_file_dialog.DoModal())
		exit(0);

	CString tmpPath = m_file_dialog.GetPathName();
	USES_CONVERSION;
	String path = W2A(tmpPath);
	m_path = tmpPath;

	extension = getFileExtension(m_file_dialog.GetFileName());
	SetDlgItemText(IDC_EDIT_PATH, tmpPath);
	//UpdateData(false);
	
	if (extension == ".jpg" || extension == ".png")
	{
		im_resource = imread(path);
		int originalHeight = im_resource.size[0];
		int originalWidth = im_resource.size[1];
		m_originalsize.Format(_T("%d X %d px"), originalHeight, originalWidth);
		SetDlgItemText(IDC_EDIT_OSize, m_originalsize);

		if (im_resource.data)
		{
			if (originalHeight > originalWidth)
			{
				height = rect_pic1.Height();
				width = originalWidth / (originalHeight / height);
				m_heightshow.Format(_T("%d px"), int(height));
				m_widthshow.Format(_T("%d px"), int(width));
			}
			else
			{
				width = rect_pic1.Width();
				height = originalHeight / (originalWidth / width);
				m_heightshow.Format(_T("%d px"), int(height));
				m_widthshow.Format(_T("%d px"), int(width));
			}
			UpdateData(false);

			resize(im_resource, imTmp, Size(width, height));
			GetDlgItem(IDC_STATIC_PIC1)->ShowWindow(true);
			::ShowWindow(hwnd, SW_NORMAL);
			imshow("im_resource", imTmp);
			m_sys_status = _T("Show the image which was chosen...");
			SetDlgItemText(IDC_EDIT_SYS, m_sys_status);
			//waitKey(0);
		}
		else
		{
			errorinf = _T("Can't find the file: ") + tmpPath;
			m_sys_status = errorinf + _T(" ...");
			SetDlgItemText(IDC_EDIT_SYS, m_sys_status);
			MessageBox(errorinf);
		}
	}
	else {
		CString ext(extension.c_str());
		errorinf = _T("Can't open the file with extension: ") + ext;
		m_sys_status = errorinf + _T(" ...");
		SetDlgItemText(IDC_EDIT_SYS, m_sys_status);
		MessageBox(errorinf);
	}
}


void Cedge_extractDlg::OnBnClickedButtonTest()
{
	if (imTmp.empty())
	{
		m_sys_status = _T("Don't find the image you want to edit ...");
		SetDlgItemText(IDC_EDIT_SYS, m_sys_status);
		MessageBox(_T("You have not open a image!"));
	}
	else
	{
		Mat imBinary = imTmp.clone();
		
		pstatic->GetDC()->FillSolidRect(rect_pic1.left, rect_pic1.top, rect_pic1.Width(), rect_pic1.Height(), RGB(240, 240, 240));

		cvtColor(imBinary, imBinary, CV_BGR2GRAY);
		threshold(imBinary, imBinary, m_threshold, 255, CV_THRESH_BINARY);
		
		findContours(imBinary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
		m_num = contours.size();
		UpdateData(false);
		drawContours(imTmp, contours, -1, Scalar(0, 255, 0), 1);
		
		imshow("im_resource", imTmp);
	}
}


void Cedge_extractDlg::OnBnClickedButtonStore()
{
	if (imTmp.empty())
	{
		m_sys_status = _T("The image you want to save is empty ...");
		SetDlgItemText(IDC_EDIT_SYS, m_sys_status);
		MessageBox(_T("You have not open a image!"));
	}
	else
	{
		string path;
		string extension;
		CString errorinf;
		CFileDialog fileoutput(false);
		
		if (!fileoutput.DoModal())
			exit(0);

		CString tmpPath = fileoutput.GetPathName();
		extension = getFileExtension(tmpPath);

		if (".jpg" == extension || ".png" == extension)
		{
			USES_CONVERSION;
			path = W2A(tmpPath);
			imwrite(path, imTmp);
		}
		else
		{
			CString ext(extension.c_str());
			errorinf = _T("Can't save this image into the file with extension: ");
			errorinf += ext;
			MessageBox(errorinf);
		}
	}
}


void Cedge_extractDlg::OnBnClickedButtonSet()
{
	if (!m_setDialog.DoModal())
		exit(0);
}


void Cedge_extractDlg::OnBnClickedButtonContours()
{
	if (0 == contours.size()) 
	{
		m_sys_status = _T("There is no contour was detected ...");
		SetDlgItemText(IDC_EDIT_SYS, m_sys_status);
		MessageBox(_T("Don't find any contours!"));
	}
	else 
	{
		int rows = im_resource.size[0];
		int cols = im_resource.size[1];
		Mat emptymat(rows, cols, CV_8UC3, Scalar(255, 255, 255));
		pstatic->GetDC()->FillSolidRect(rect_pic1.left, rect_pic1.top, rect_pic1.Width(), rect_pic1.Height(), RGB(240, 240, 240));
		drawContours(emptymat, contours, -1, Scalar(0, 255, 0), 1);
		imshow("im_resource", emptymat);
	}
}



