#include "StdAfx.h"  
#include "IconUI.h"  

namespace DuiLib
{
    //////////////////////////////////////////////////////////////////////////  
    // CIconUI  
    CIconUI::CIconUI(void)
    {
        memset(&m_rcInset, 0, sizeof(m_rcInset));
        SetAttribute(_T("bkcolor"), _T("#00000000"));
    }

    CIconUI::~CIconUI(void)
    {
    }

    LPCTSTR CIconUI::GetClass() const
    {
        return _T("IconUI");
    }

    LPVOID CIconUI::GetInterface(LPCTSTR pstrName)
    {
        if (_tcscmp(pstrName, _T("Icon")) == 0)
            return static_cast<CIconUI*>(this);
        return __super::GetInterface(pstrName);
    }

    void CIconUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
    {
        if (_tcscmp(pstrName, _T("icon")) == 0)
            m_sIcoImage = pstrValue;
        if (_tcscmp(pstrName, _T("inset")) == 0)
        {
            RECT rcInset = { 0 };
            LPTSTR pstr = NULL;
            rcInset.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
            rcInset.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
            rcInset.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);
            rcInset.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);
            SetInset(rcInset);
        }
        Invalidate();
        __super::SetAttribute(pstrName, pstrValue);
    }

    void CIconUI::SetPos(RECT rc)
    {
        CControlUI::SetPos(rc);
    }

    void CIconUI::SetInset(RECT rc)
    {
        m_rcInset = rc;
    }

    void CIconUI::DoEvent(TEventUI& event)
    {
        CControlUI::DoEvent(event);


    }

    void CIconUI::SetVisible(bool bVisible)
    {
        CControlUI::SetVisible(bVisible);
    }

    void CIconUI::SetInternVisible(bool bVisible)
    {
        CControlUI::SetInternVisible(bVisible);

    }

    void CIconUI::DoPaint(HDC hDC, const RECT& rcPaint)
    {
        RECT rcTemp = { 0 };
        if (!::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem)) return;

        HICON hIcon = (HICON)::LoadImage(m_pManager->GetInstance(), m_sIcoImage, IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE | LR_DEFAULTSIZE);
        if (hIcon == NULL)
            hIcon = (HICON)::LoadImage(m_pManager->GetInstance(), m_pManager->GetResourcePath() + _T("\\Favicon\\blank_favicon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE | LR_DEFAULTSIZE);
        if (NULL != hIcon)
        {
            RECT rect;
            rect.left = m_rcItem.left + m_rcInset.left;
            rect.right = m_rcItem.right - m_rcInset.right;
            rect.top = m_rcItem.top + m_rcInset.top;
            rect.bottom = m_rcItem.bottom - m_rcInset.bottom;
            ::DrawIconEx(hDC, rect.left, rect.top, hIcon, rect.right - rect.left,
                rect.bottom - rect.top, 0, NULL, DI_NORMAL);
            ::DeleteObject(hIcon);
        }
    }


}