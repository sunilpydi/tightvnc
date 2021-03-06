/* 
$XConsortium: record.h /main/4 1996/01/31 20:28:22 dpw $
*/

/***************************************************************************
 * Copyright 1995 Network Computing Devices
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Network Computing Devices 
 * not be used in advertising or publicity pertaining to distribution
 * of the software without specific, written prior permission.
 *
 * NETWORK COMPUTING DEVICES DISCLAIMs ALL WARRANTIES WITH REGARD TO 
 * THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS, IN NO EVENT SHALL NETWORK COMPUTING DEVICES BE LIABLE 
 * FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN 
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING 
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 **************************************************************************/
#ifndef _RECORD_H_
#define _RECORD_H_

#define XRecordBadContext       0	/* Not a valid RC */

/*
 * Constants for arguments of various requests
 */
#define	XRecordFromServerTime		0x01
#define	XRecordFromClientTime		0x02
#define	XRecordFromClientSequence	0x04

#define XRecordCurrentClients		1
#define XRecordFutureClients		2
#define XRecordAllClients		3

#define XRecordFromServer           	0
#define XRecordFromClient               1
#define XRecordClientStarted           	2
#define XRecordClientDied               3
#define XRecordStartOfData		4
#define XRecordEndOfData		5

typedef unsigned long   XRecordClientSpec;

#ifndef _XRECORD_SERVER_

typedef unsigned long 	XRecordContext;

typedef struct
{
    unsigned char 	first;
    unsigned char 	last;
} XRecordRange8;

typedef struct
{
    unsigned short 	first;
    unsigned short 	last;
} XRecordRange16; 

typedef struct
{
    XRecordRange8	ext_major;
    XRecordRange16 	ext_minor; 
} XRecordExtRange; 

typedef struct
{
    XRecordRange8     core_requests;	/* core X requests */
    XRecordRange8     core_replies;	/* core X replies */
    XRecordExtRange   ext_requests;	/* extension requests */
    XRecordExtRange   ext_replies;	/* extension replies */
    XRecordRange8     delivered_events;	/* delivered core and ext events */
    XRecordRange8     device_events; 	/* all core and ext device events */
    XRecordRange8     errors;		/* core X and ext errors */
    Bool	      client_started;	/* connection setup reply */
    Bool              client_died; 	/* notice of client disconnect */    
} XRecordRange;

typedef struct
{
    XRecordClientSpec 	client;
    unsigned long 	nranges; 
    XRecordRange 	**ranges;
} XRecordClientInfo;

typedef struct
{
    Bool 		enabled;
    int			datum_flags; 
    unsigned long 	nclients; 
    XRecordClientInfo 	**client_info;
} XRecordState;

typedef struct
{
    XID 		id_base;
    Time		server_time; 
    unsigned long 	client_seq;
    int			category; 
    Bool 		client_swapped;
    unsigned char 	*data;
    unsigned long 	data_len;	/* in 4-byte units */
} XRecordInterceptData;

_XFUNCPROTOBEGIN

/*********************************************************
 *
 * Prototypes 
 *
 */

XID XRecordIdBaseMask(
#if NeedFunctionPrototypes
    Display *dpy
#endif
);

extern Status XRecordQueryVersion(
#if NeedFunctionPrototypes
    Display* 			/* dpy */,
    int* 			/* cmajor_return */, 
    int*			/* cminor_return */  
#endif
);

extern XRecordContext XRecordCreateContext(
#if NeedFunctionPrototypes
    Display*			/* dpy */, 
    int				/* datum_flags */, 
    XRecordClientSpec*		/* clients */,
    int				/* nclients */,     
    XRecordRange**              /* ranges */,
    int				/* nranges */
#endif
);

extern XRecordRange *XRecordAllocRange(
#if NeedFunctionPrototypes
    void
#endif
);

extern Status XRecordRegisterClients(
#if NeedFunctionPrototypes
    Display* 			/* dpy */, 
    XRecordContext 		/* context */, 
    int				/* datum_flags */,
    XRecordClientSpec*		/* clients */,
    int				/* nclients */, 
    XRecordRange** 		/* ranges */,  
    int				/* nranges */
#endif
);

extern Status XRecordUnregisterClients(
#if NeedFunctionPrototypes
    Display* 			/* dpy */, 
    XRecordContext 		/* context */, 
    XRecordClientSpec*		/* clients */,
    int				/* nclients */ 
#endif
);

extern Status XRecordGetContext(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    XRecordContext 		/* context */, 
    XRecordState** 		/* state_return */ 
#endif
);

extern void XRecordFreeState(
#if NeedFunctionPrototypes
XRecordState*			/* state */
#endif
); 

typedef void (*XRecordInterceptProc) (
#if NeedFunctionPrototypes
    XPointer			/* closure */, 
    XRecordInterceptData*	/* recorded_data */
#endif
);

extern Status XRecordEnableContext(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    XRecordContext 		/* context */, 
    XRecordInterceptProc	/* callback */,
    XPointer			/* closure */
#endif
); 

extern Status XRecordEnableContextAsync(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    XRecordContext 		/* context */, 
    XRecordInterceptProc	/* callback */,
    XPointer			/* closure */
#endif
); 

extern void XRecordProcessReplies(
#if NeedFunctionPrototypes
    Display*			/* dpy */
#endif
); 

extern void XRecordFreeData(
#if NeedFunctionPrototypes
XRecordInterceptData*	/* data */
#endif
); 

extern Status XRecordDisableContext(
#if NeedFunctionPrototypes
    Display*			/* dpy */,
    XRecordContext 		/* context */
#endif
); 

extern Status XRecordFreeContext(
#if NeedFunctionPrototypes
    Display* 			/* dpy */, 
    XRecordContext 		/* context */
#endif
);

_XFUNCPROTOEND

#endif /* _XRECORD_SERVER_ */

#endif /* _RECORD_H_ */
