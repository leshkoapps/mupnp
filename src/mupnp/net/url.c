/******************************************************************
*
*	CyberLink for C
*
*	Copyright (C) Satoshi Konno 2005
*
*       Copyright (C) 2006 Nokia Corporation. All rights reserved.
*
*       This is licensed under BSD-style license,
*       see file COPYING.
*
*	File: curl.c
*
*	Revision:
*
*	03/16/05
*		- first revision
*
*
*	10/31/05
*		- mupnp_net_getmodifierhosturl set the tag begin mark "<" before port
*		  while it must come before "http://"
*
*	19-Jan-06 Aapo Makela
*		- Fixed mupnp_net_gethosturl to call mupnp_net_getmodifierhosturl
******************************************************************/

#include <mupnp/net/uri.h>
#include <mupnp/net/interface.h>
#include <mupnp/util/log.h>

#include <stdio.h>

/****************************************
* mupnp_net_getmodifierhosturl
****************************************/

const char *mupnp_net_getmodifierhosturl(const char *host, int port, const char *uri, const char *begin, const char *end, char *buf, size_t bufSize)
{
	BOOL isIPv6Host;
	
	mupnp_log_debug_l4("Entering...\n");

	isIPv6Host = mupnp_net_isipv6address(host);
	
#if defined(HAVE_SNPRINTF)
	snprintf(buf, bufSize,
#else
	sprintf(buf,
#endif
		"%shttp://%s%s%s:%d%s%s",
		begin,
		((isIPv6Host == TRUE) ? "[" : ""),
		host,
		((isIPv6Host == TRUE) ? "]" : ""),
		port,
		uri,
		end);
	
  mupnp_log_debug_l4("Leaving...\n");
	
  return buf;
}

/****************************************
* mupnp_net_gethosturl
****************************************/

const char *mupnp_net_gethosturl(const char *host, int port, const char *uri, char *buf, size_t bufSize)
{
	mupnp_log_debug_l4("Entering...\n");

	return mupnp_net_getmodifierhosturl(host, port, uri, "", "", buf, bufSize);

	mupnp_log_debug_l4("Leaving...\n");
}