
// edge_extractDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "SetDlg.h"

using namespace cv;
using namespace std;

// Cedge_extractDlg �Ի���
class Cedge_extractDlg : public CDialogEx
{
// ����
public:
	Cedge_extractDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDGE_EXTRACT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CFont m_editFont;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// handle
	HWND hwnd;

	// Mat variables
	Mat im_resource;
	Mat imTmp;
	vector<vector<Point>> contours;   // store the contours
	vector<Vec4i> hierarchy;

	// Rect variables
	CRect rect_pic1;
	CStatic *pstatic;

	// Dialog 
	CSetDlg m_setDialog;

	// Control variables
	CButton m_button_open;
	CButton m_button_test;
	CButton m_button_store;
	CButton m_button_set1;
	CButton m_button_contours;
	CEdit m_edit_num;
	CEdit m_edit_path;
	CEdit m_edit_result;

	// Values of Controls
	CString m_result;
	CString m_path;
	CString m_sys_status;
	CString m_time;
	CString m_heightshow;
	CString m_originalsize;
	CString m_widthshow;
//	CString m_num;
	int m_num;
	int m_threshold;

	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnBnClickedButtonStore();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonContours();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
