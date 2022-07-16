#pragma once
#include "invoker.h"

typedef scrNativeHandler(*getNativeHandlerT)(scrNativeRegistrationTable* this, scrNativeHash hash);
typedef void(*fixVectorsT)(scrNativeCallContext* this);
typedef int(*scrThreadRunT)(uint32_t ops_to_execute);
typedef const char*(*getLabelTextT)(void* unk, const char* lbl);
typedef bool(*readBitbufferDwordT)(struct datBitBuffer* buffer, PVOID read, int bits);
typedef bool(*readBitbufferArrayT)(struct datBitBuffer* buffer, PVOID read, int bits, int unk);
typedef void(*sendEventAckT)(uint64_t eventMgr, struct CNetGamePlayer* source, struct CNetGamePlayer* target, int idx, int handledBitset);
typedef void(*receivedEventT)(uint64_t eventMgr, struct CNetGamePlayer* source, struct CNetGamePlayer* target, uint16_t id, int idx, int handledBitset, int bufferSize, struct datBitBuffer* buffer);
typedef bool(*receivedNetMessageT)(void* netConnectionMgr, void* unk, struct InFrame* frame);

typedef struct pointers {
	struct GtaThreadVtbl* m_gtaThreadVftable;
	scrNativeRegistrationTable* m_nativeRegTbl;
	getNativeHandlerT m_getNativeHandler;
	fixVectorsT m_fixVectors;
	scrThreadRunT m_scrThreadRun;
	getLabelTextT m_getLabelText;
	readBitbufferDwordT m_readBitbufferDword;
	readBitbufferArrayT m_readBitbufferArray;
	sendEventAckT m_sendEventAck;
	receivedEventT m_receivedEvent;
	receivedNetMessageT m_receivedNetMessage;
	struct atArray* m_gtaThreads;
	struct CPedFactory** m_pedFactory;
	struct CNetworkPlayerMgr** m_networkPlayerMgr;
	intptr_t** m_scriptGlobals;
} pointers;
extern pointers g_pointers;

void scanPointers(void* baseAdr, size_t imgSize);