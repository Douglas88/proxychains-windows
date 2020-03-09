// SPDX-License-Identifier: GPL-2.0-or-later
/* hookdll_util_ipc_win32.h
 * Copyright (C) 2020 Feng Shun.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2 as 
 *   published by the Free Software Foundation, either version 3 of the
 *   License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License version 2 for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   version 2 along with this program. If not, see
 *   <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "defines_win32.h"
#include "hookdll_util_ipc_generic.h"

#pragma pack(push, 1)
typedef struct _REPORTED_CHILD_DATA {
	PXCH_UINT32 dwPid;
	HANDLE hMapFile;
	LPCVOID pMappedBuf;
	PROXYCHAINS_CONFIG* pSavedPxchConfig;
	PXCH_INJECT_REMOTE_DATA* pSavedRemoteData;
	PXCH_UINT32 dwSavedTlsIndex;
	void* /* UT_array* */ pSavedHeapAllocatedPointers;
} REPORTED_CHILD_DATA;

typedef struct _IPC_MSGHDR_CHILDDATA {
	UINT32 dwTag;
	REPORTED_CHILD_DATA ChildData;
} PXCH_IPC_MSGHDR_CHILDDATA;

typedef struct _IPC_MSGHDR_QUERYSTORAGE {
	UINT32 dwTag;
	PXCH_UINT32 dwChildPid;
} PXCH_IPC_MSGHDR_QUERYSTORAGE;
#pragma pack(pop)

PXCH_DLL_API PXCH_UINT32 ChildDataToMessage(PXCH_IPC_MSGBUF chMessageBuf, PXCH_UINT32* pcbMessageSize, const REPORTED_CHILD_DATA* pChildData);
PXCH_DLL_API PXCH_UINT32 MessageToChildData(REPORTED_CHILD_DATA* pChildData, CPXCH_IPC_MSGBUF chMessageBuf, PXCH_UINT32 cbMessageSize);

PXCH_DLL_API PXCH_UINT32 QueryStorageToMessage(PXCH_IPC_MSGBUF chMessageBuf, PXCH_UINT32* pcbMessageSize, PXCH_UINT32 dwChildPid);
PXCH_DLL_API PXCH_UINT32 MessageToQueryStorage(PXCH_UINT32* pdwChildPid, CPXCH_IPC_MSGBUF chMessageBuf, PXCH_UINT32 cbMessageSize);

PXCH_DLL_API PXCH_UINT32 HostnameAndIpsToMessage(PXCH_IPC_MSGBUF chMessageBuf, PXCH_UINT32* pcbMessageSize, PXCH_UINT32 dwPid, const PXCH_HOSTNAME* Hostname, BOOL bWillMapResolvedIpToHost, PXCH_UINT32 dwIpNum, const PXCH_IP_ADDRESS* Ips, PXCH_UINT32 dwTarget);
PXCH_DLL_API PXCH_UINT32 MessageToHostnameAndIps(PXCH_UINT32* pdwPid, PXCH_HOSTNAME* pHostname, BOOL* pbWillMapResolvedIpToHost, PXCH_UINT32* pdwIpNum, PXCH_IP_ADDRESS* Ips, PXCH_UINT32* pdwTarget, CPXCH_IPC_MSGBUF chMessageBuf, PXCH_UINT32 cbMessageSize);