#pragma once
#include <vector>


class CButtonExd
{
public:
	std::vector<CButtonExd*> m_Childs;
private:
	CString m_Name;
	CButton* m_pBtn;
	CWnd* m_pWnd;//�����壬Ҳ�ǵ�ǰ�������ṹ�ϵĸ����壬��Ҫ�õ�����ת��
	CButtonExd* m_parent;
	bool m_bShow;
	bool m_bExpand;
	bool m_bUseAbsolutePos;
	bool m_bIsRoot;//�Ƿ���������ڵ�
	int m_leftpad;//���ǰһ���ڵ��ƫ�ƣ�1.��ǰIndex=0,��ǰһ���ڵ���parent 2.��������������ֵܽڵ�index-1��
	int m_toppad;
	int m_index;
	CRect m_rc;
public:
	CRect Show(bool NeedRevise = false,int leftpad = 0,int toppad = 0);
	CRect Hide(bool NeedRevise = false);
	CRect Expand();
	CRect Folded();
	void AddChild(CButtonExd* pChild);
	void SetRoot(bool bRoot)
	{
		m_bIsRoot = bRoot;
	}

	bool IsRoot()
	{
		return m_bIsRoot;
	}

	void SetAbsolutePos(bool abspos)
	{
		m_bUseAbsolutePos = abspos;
	}

	bool IsAbsolutePos()
	{
		return m_bUseAbsolutePos;
	}

	bool IsExpand()
	{
		return m_bExpand;
	}

	CString GetName()
	{
		return m_Name;
	}

	bool IsShow()
	{
		return m_bShow;
	}
private:
	void Revise(int leftpad,int toppad);
	void Move(int leftpad,int toppad);
public:
	CButtonExd(void);
	~CButtonExd(void);
	CButtonExd(CWnd* pWnd,CButton* pBtn,LPTSTR Name,int leftpad=0,int toppad=0);
private:
	CButtonExd(CButtonExd&);
};

