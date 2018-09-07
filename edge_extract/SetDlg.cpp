// SetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "edge_extract.h"
#include "SetDlg.h"
#include "afxdialogex.h"
#include "OTSU.h"
#include "edge_extractDlg.h"


// CSetDlg 对话框

IMPLEMENT_DYNAMIC(CSetDlg, CDialogEx)

CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SET, pParent)
	, m_edit_otsu(0)
{

}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OTSUTHRE, m_edit_otsu);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSetDlg 消息处理程序


void CSetDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	Cedge_extractDlg *parent = (Cedge_extractDlg *)GetParent();
	img = parent->im_resource;
	m_edit_otsu = OTSU(img);
	UpdateData(false);
}
