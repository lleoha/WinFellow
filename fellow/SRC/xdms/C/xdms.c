
/*
 *     xDMS  v1.3b  -  Portable DMS archive unpacker  -  Public Domain
 *     Written by     "Andre Rodrigues de la Rocha"  <adlroc@usa.net>
 *     Hacked to pieces by Dan Sutherland <dan@chromerhino.demon.co.uk>
 *     for use in ADF Opus.
 */

#include <stdio.h>

#ifdef _FELLOW_DEBUG_CRT_MALLOC
#define _CRTDBG_MAP_ALLOC
#endif
#include <stdlib.h>
#ifdef _FELLOW_DEBUG_CRT_MALLOC
#include <crtdbg.h>
#endif

#include <string.h>
#include <ctype.h>

#include "cdata.h"
#include "pfile.h"
#include "crc_csum.h"



USHORT dmsUnpack(char *src, char *dest)
{
	return Process_File(src, dest, 0, 0, 0);
}

void dmsErrMsg(USHORT err, char *i, char *o, char *errMess)
{
	switch (err) {
		case NO_PROBLEM:
		case DMS_FILE_END:
			return;
		case ERR_NOMEMORY:
			sprintf(errMess,"Not enough memory for buffers !\n");
			break;
		case ERR_CANTOPENIN:
			sprintf(errMess,"Can't open source file for reading\n");
			break;
		case ERR_CANTOPENOUT:
			sprintf(errMess,"Can't open %s for writing !\n",o);
			break;
		case ERR_NOTDMS:
			sprintf(errMess,"File %s is not a DMS archive !\n",i);
			break;
		case ERR_SREAD:
			sprintf(errMess,"Error reading file %s : unexpected end of file !\n",i);
			break;
		case ERR_HCRC:
			sprintf(errMess,"Error in file %s : header CRC error !\n",i);
			break;
		case ERR_NOTTRACK:
			sprintf(errMess,"Error in file %s : track header not found !\n",i);
			break;
		case ERR_BIGTRACK:
			sprintf(errMess,"Error in DMS file: track too big");
			break;
		case ERR_THCRC:
			sprintf(errMess,"Error in file %s : track header CRC error !\n",i);
			break;
		case ERR_TDCRC:
			sprintf(errMess,"Error in file %s : track data CRC error !\n",i);
			break;
		case ERR_CSUM:
			sprintf(errMess,"Error in file %s : checksum error after unpacking !\n",i);
			break;
		case ERR_CANTWRITE:
			sprintf(errMess,"Error : can't write to file %s  !\n",o);
			break;
		case ERR_BADDECR:
			sprintf(errMess,"Error in file %s : error unpacking !\n",i);
			break;
		case ERR_UNKNMODE:
			sprintf(errMess,"Error in file %s : unknown compression mode used !\n",i);
			break;
		case ERR_NOPASSWD:
			sprintf(errMess,"Can't process file %s : file is encrypted !\n",i);
			break;
		case ERR_BADPASSWD:
			sprintf(errMess,"Error unpacking file %s . The password is probably wrong.\n",i);
			break;
		case ERR_FMS:
			sprintf(errMess,"Error in file %s : this file is not really a compressed disk image, but an FMS archive !\n",i);
			break;
		default:
			sprintf(errMess,"Error while processing file  %s : internal error !\n",i);
			break;
	}
}
