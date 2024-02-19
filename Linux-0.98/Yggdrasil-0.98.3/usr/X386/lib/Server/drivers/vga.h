/*
 * $Header: /home/x_cvs/mit/server/ddx/x386/vga256/vga/vga.h,v 1.10 1992/09/12 08:31:05 dawes Exp $
 * Copyright 1990,91 by Thomas Roell, Dinkelscherben, Germany.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Thomas Roell not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Thomas Roell makes no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
 * THOMAS ROELL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THOMAS ROELL BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  Thomas Roell, roell@informatik.tu-muenchen.de
 *
 * $Header: /proj/X11/mit/server/ddx/x386/vga/RCS/vga.h,v 1.2 1991/06/27 00:02:52 root Exp $
 */

#include "X.h"
#include "misc.h"
#include "x386.h"

extern Bool    vgaProbe();
extern void    vgaPrintIdent();
extern Bool    vgaScreenInit();
extern void    vgaEnterLeaveVT();
extern void    vgaAdjustFrame();
extern void    vgaSwitchMode();

extern Bool    vgaSaveScreen();
extern Bool    vgaCloseScreen();
#ifndef MONOVGA
extern void    vgaBitBlt();
extern void    vgaImageRead();
extern void    vgaImageWrite();
extern void    vgaPixBitBlt();
extern void    vgaImageGlyphBlt();
#endif

extern void    vgaHWInit();
extern void    vgaHWRestore();
extern void *  vgaHWSave();
extern void    vgaGetClocks();

#ifndef MONOVGA
extern int     vgaListInstalledColormaps();
extern void    vgaStoreColors();
extern void    vgaInstallColormap();
extern void    vgaUninstallColormap();
#endif


/*
 * structure for accessing the video chip`s functions
 */
typedef struct {
  Bool (* ChipProbe)();
  char * (* ChipIdent)();
  void (* ChipEnterLeave)();
  void (* ChipInit)();
  void * (* ChipSave)();
  void (* ChipRestore)();
  void (* ChipAdjust)();
  void (* ChipSetRead)();
  void (* ChipSetWrite)();
  void (* ChipSetReadWrite)();
  int ChipMapSize;
  int ChipSegmentSize;
  int ChipSegmentShift;
  int ChipSegmentMask;
  int ChipReadBottom;
  int ChipReadTop;
  int ChipWriteBottom;
  int ChipWriteTop;
  Bool ChipUse2Banks;               /* TRUE if the chip uses separate read
                                       and write banks */    
  
} vgaVideoChipRec, *vgaVideoChipPtr;


/*
 * hooks for communicating with the VideoChip on the VGA
 */
extern void (* vgaInitFunc)();
extern void (* vgaEnterLeaveFunc)();
extern void * (* vgaSaveFunc)();
extern void (* vgaRestoreFunc)();
extern void (* vgaAdjustFunc)();
#ifndef MONOVGA
extern void (* vgaSetReadFunc)();
extern void (* vgaSetWriteFunc)();
extern void (* vgaSetReadWriteFunc)();
extern int vgaMapSize;
extern int vgaSegmentSize;
extern int vgaSegmentShift;
extern int vgaSegmentMask;
#endif
extern int vgaIOBase;

#ifdef MONOVGA
#define VGABASE vgaBase
#else
#include "vgaBank.h"
#endif
extern pointer vgaOrigVideoState;    /* buffers for all video information */
extern pointer vgaNewVideoState;
extern pointer vgaBase;              /* the framebuffer himself */


typedef struct {
  unsigned char MiscOutReg;     /* */
  unsigned char CRTC[25];       /* Crtc Controller */
  unsigned char Sequencer[5];   /* Video Sequencer */
  unsigned char Graphics[9];    /* Video Graphics */
  unsigned char Attribute[21];  /* Video Atribute */
  unsigned char DAC[768];       /* Internal Colorlookuptable */
  unsigned char NoClock;        /* number of selected clock */
  pointer FontInfo1;            /* save area for fonts in plane 2 */ 
  pointer FontInfo2;            /* save area for fonts in plane 3 */ 
  pointer TextInfo;             /* save area for text */ 
} vgaHWRec, *vgaHWPtr;

#ifndef MONOVGA
#define BITS_PER_GUN 6
#define COLORMAP_SIZE 256

extern void vgaImageGlyphBlt();
extern void vgaDoBitBlt();
#endif

#ifdef MONOVGA
#define vga256InfoRec vga2InfoRec
#endif
extern ScrnInfoRec vga256InfoRec;
