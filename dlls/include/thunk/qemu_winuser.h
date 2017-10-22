#ifndef HAVE_QEMU_WINUSER_H
#define HAVE_QEMU_WINUSER_H

struct qemu_WNDCLASSEX
{
    UINT        cbSize;
    UINT        style;
    qemu_ptr    lpfnWndProc;
    INT         cbClsExtra;
    INT         cbWndExtra;
    qemu_handle hInstance;
    qemu_handle hIcon;
    qemu_handle hCursor;
    qemu_handle hbrBackground;
    qemu_ptr    lpszMenuName;
    qemu_ptr    lpszClassName;
    qemu_handle hIconSm;
};

struct qemu_CREATESTRUCT
{
    qemu_ptr        lpCreateParams;
    qemu_handle     hInstance;
    qemu_handle     hMenu;
    qemu_handle     hwndParent;
    INT             cy;
    INT             cx;
    INT             y;
    INT             x;
    LONG            style;
    qemu_ptr        lpszName;
    qemu_ptr        lpszClass;
    DWORD           dwExStyle;
};

struct qemu_WINDOWPOS
{
    qemu_handle hwnd;
    qemu_handle hwndInsertAfter;
    INT         x;
    INT         y;
    INT         cx;
    INT         cy;
    UINT        flags;
};

struct qemu_NMHDR
{
    qemu_handle hwndFrom;
    qemu_ptr    idFrom;
    UINT        code;
};

static inline void NMHDR_h2g(struct qemu_NMHDR *guest, const NMHDR *host)
{
    guest->hwndFrom = (ULONG_PTR)host->hwndFrom;
    guest->idFrom = host->idFrom;
    guest->code = host->code;
}

static inline void NMHDR_g2h(NMHDR *host, const struct qemu_NMHDR *guest)
{
    host->hwndFrom = HANDLE_g2h(guest->hwndFrom);
    host->idFrom = guest->idFrom;
    host->code = guest->code;
}

struct qemu_PAINTSTRUCT
{
    qemu_handle     hdc;
    BOOL            fErase;
    RECT            rcPaint;
    BOOL            fRestore;
    BOOL            fIncUpdate;
    BYTE            rgbReserved[32];
};

static inline void PAINTSTRUCT_h2g(struct qemu_PAINTSTRUCT *guest, const PAINTSTRUCT *host)
{
    guest->hdc = (ULONG_PTR)host->hdc;
    guest->fErase = host->fErase;
    memcpy(&guest->rcPaint, &host->rcPaint, sizeof(guest->rcPaint));
    guest->fRestore = host->fRestore;
    guest->fIncUpdate = host->fIncUpdate;
    memcpy(guest->rgbReserved, host->rgbReserved, sizeof(guest->rgbReserved));
}

static inline void PAINTSTRUCT_g2h(PAINTSTRUCT *host, const struct qemu_PAINTSTRUCT *guest)
{
    host->hdc = HANDLE_g2h(guest->hdc);
    host->fErase = guest->fErase;
    memcpy(&host->rcPaint, &guest->rcPaint, sizeof(host->rcPaint));
    host->fRestore = guest->fRestore;
    host->fIncUpdate = guest->fIncUpdate;
    memcpy(host->rgbReserved, guest->rgbReserved, sizeof(host->rgbReserved));
}

#endif
