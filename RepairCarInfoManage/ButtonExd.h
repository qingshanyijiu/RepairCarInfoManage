#pragma once
#include <vector>


class CButtonExd
{
public:
	std::vector<CButtonExd*> m_Childs;
private:
	CString m_Name;
	CButton* m_pBtn;
	CWnd* m_pWnd;//父窗体，也是当前整个树结构上的父窗体，主要用到坐标转换
	CButtonExd* m_parent;
	bool m_bShow;
	bool m_bExpand;
	bool m_bUseAbsolutePos;
	bool m_bIsRoot;//是否是虚拟根节点
	int m_leftpad;//相对前一个节点的偏移（1.当前Index=0,则前一个节点是parent 2.其他情况，则是兄弟节点index-1）
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

