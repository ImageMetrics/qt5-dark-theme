/*
 * Copyright (C) Pedram Pourang (aka Tsu Jan) 2014-2023 <tsujan2000@gmail.com>
 *
 * Kvantum is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Kvantum is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Kvantum.h"

#include <QLibrary> // only for setGtkVariant()
#include <QPainter>
#include <QTimer>
#include <QApplication>
#include <QToolBar>
#include <QMainWindow>
#include <QPushButton>
#include <QCommandLinkButton>
#include <QComboBox>
#include <QLineEdit>
#include <QProgressBar>
#include <QMenu>
#include <QGroupBox>
#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QDoubleSpinBox>
#include <QDateTimeEdit>
#include <QPaintEvent>
#include <QMenuBar>
#include <QDialog>
#include <QWindow> // for positioning menus
#include <QScreen> // for positioning menus
#include <QStylePainter>

namespace Kvantum
{

void setGtkVariant(QWidget *widget, bool dark) // by Craig Drummond
{
  if (!widget || QLatin1String("xcb")!=qApp->platformName()) {
    return;
  }
  static const char *_GTK_THEME_VARIANT="_GTK_THEME_VARIANT";

  // Check if already set
  QByteArray styleVar = dark ? "dark" : "light";
  QVariant var=widget->property("_GTK_THEME_VARIANT");
  if (var.isValid() && var.toByteArray()==styleVar) {
    return;
  }

  // Typedef's from xcb/xcb.h - copied so that there is no
  // direct xcb dependency
  typedef quint32 XcbAtom;

  struct XcbInternAtomCookie {
    unsigned int sequence;
  };

  struct XcbInternAtomReply {
    quint8  response_type;
    quint8  pad0;
    quint16 sequence;
    quint32 length;
    XcbAtom atom;
  };

  typedef void * (*XcbConnectFn)(int, int);
  typedef XcbInternAtomCookie (*XcbInternAtomFn)(void *, int, int, const char *);
  typedef XcbInternAtomReply * (*XcbInternAtomReplyFn)(void *, XcbInternAtomCookie, int);
  typedef int (*XcbChangePropertyFn)(void *, int, int, XcbAtom, XcbAtom, int, int, const void *);
  typedef int (*XcbFlushFn)(void *);

  static QLibrary *lib = 0;
  static XcbAtom variantAtom = 0;
  static XcbAtom utf8TypeAtom = 0;
  static void *xcbConn = 0;
  static XcbChangePropertyFn XcbChangePropertyFnPtr = 0;
  static XcbFlushFn XcbFlushFnPtr = 0;

  if (!lib) {
    lib = new QLibrary("libxcb", qApp);

    if (lib->load()) {
      XcbConnectFn XcbConnectFnPtr=(XcbConnectFn)lib->resolve("xcb_connect");
      XcbInternAtomFn XcbInternAtomFnPtr=(XcbInternAtomFn)lib->resolve("xcb_intern_atom");
      XcbInternAtomReplyFn XcbInternAtomReplyFnPtr=(XcbInternAtomReplyFn)lib->resolve("xcb_intern_atom_reply");

      XcbChangePropertyFnPtr=(XcbChangePropertyFn)lib->resolve("xcb_change_property");
      XcbFlushFnPtr=(XcbFlushFn)lib->resolve("xcb_flush");
      if (XcbConnectFnPtr && XcbInternAtomFnPtr && XcbInternAtomReplyFnPtr && XcbChangePropertyFnPtr && XcbFlushFnPtr) {
        xcbConn=(*XcbConnectFnPtr)(0, 0);
        if (xcbConn) {
          XcbInternAtomReply *typeReply = (*XcbInternAtomReplyFnPtr)(xcbConn, (*XcbInternAtomFnPtr)(xcbConn, 0, 11, "UTF8_STRING"), 0);

          if (typeReply) {
            XcbInternAtomReply *gtkVarReply = (*XcbInternAtomReplyFnPtr)(xcbConn, (*XcbInternAtomFnPtr)(xcbConn, 0, strlen(_GTK_THEME_VARIANT),
                                                                                                        _GTK_THEME_VARIANT), 0);
            if (gtkVarReply) {
               utf8TypeAtom = typeReply->atom;
               variantAtom = gtkVarReply->atom;
               free(gtkVarReply);
            }
            free(typeReply);
          }
        }
      }
    }
  }

  if (0!=variantAtom) {
    (*XcbChangePropertyFnPtr)(xcbConn, 0, widget->effectiveWinId(), variantAtom, utf8TypeAtom, 8,
                              styleVar.length(), (const void *)styleVar.constData());
    (*XcbFlushFnPtr)(xcbConn);
    widget->setProperty(_GTK_THEME_VARIANT, styleVar);
  }
}

void Style::drawBg(QPainter *p, const QWidget *widget) const
{
  if (widget->palette().color(widget->backgroundRole()) == Qt::transparent)
    return; // Plasma FIXME: needed?
  QRect bgndRect(widget->rect());
  interior_spec ispec = getInteriorSpec("DialogTranslucent");
  if (ispec.element.isEmpty())
    ispec = getInteriorSpec("Dialog");
  if (!ispec.element.isEmpty()
      && !widget->windowFlags().testFlag(Qt::FramelessWindowHint)) // not a panel
  {
    if (QWidget *child = widget->childAt(0,0))
    { // even dialogs may have menubar or toolbar (as in Qt Designer)
      if (qobject_cast<QMenuBar*>(child) || qobject_cast<QToolBar*>(child))
      {
        ispec = getInteriorSpec("WindowTranslucent");
        if (ispec.element.isEmpty())
          ispec = getInteriorSpec("Window");
      }
    }
  }
  else
  {
    ispec = getInteriorSpec("WindowTranslucent");
    if (ispec.element.isEmpty())
      ispec = getInteriorSpec("Window");
  }
  frame_spec fspec;
  default_frame_spec(fspec);

  QString suffix = "-normal";
  if (isWidgetInactive(widget))
    suffix = "-normal-inactive";

  if (tspec_.no_window_pattern && (ispec.px > 0 || ispec.py > 0))
    ispec.px = -2; // no tiling pattern with translucency

  p->setClipRegion(bgndRect, Qt::IntersectClip);
  int ro = tspec_.reduce_window_opacity;
  if (ro > 0)
  {
    p->save();
    p->setOpacity(1.0 - (qreal)tspec_.reduce_window_opacity/100.0);
  }
  if (!renderInterior(p,bgndRect,fspec,ispec,ispec.element+suffix))
  { // no window interior element but with reduced translucency
    p->fillRect(bgndRect, QApplication::palette().color(suffix.contains("-inactive")
                                                          ? QPalette::Inactive
                                                          : QPalette::Active,
                                                        QPalette::Window));
  }
  if (ro > 0)
    p->restore();
}



} // namespace
