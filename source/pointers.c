#include "pointers.h"
#include "pattern.h"
#include "classes.h"

pointers g_pointers;
void scanPointers(void* baseAdr, size_t imgSize) {
	g_pointers.m_gtaThreadVftable = (GtaThreadVtbl*)rip(scan(baseAdr, imgSize, "GTV", "48 83 A3 10 01 ? ? ? 48 8D 05 ? ? ? ? 48 8B CB", 11));
	int8_t* ptr = scan(baseAdr, imgSize, "GT/STR", "45 33 F6 8B E9 85 C9 B8", -4);
	g_pointers.m_scrThreadRun = (scrThreadRunT)(ptr - 17);
	g_pointers.m_gtaThreads = (uintptr_t)rip(ptr) - 8;
	int8_t* ptr2 = scan(baseAdr, imgSize, "NRT/GNH", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", 0);
	g_pointers.m_nativeRegTbl = (scrNativeRegistrationTable*)rip(ptr2 + 3);
	g_pointers.m_getNativeHandler = (getNativeHandlerT)rip(ptr2 + 12);
	g_pointers.m_fixVectors = (fixVectorsT)scan(baseAdr, imgSize, "FV", "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA", 0);
	g_pointers.m_getLabelText = (fixVectorsT)scan(baseAdr, imgSize, "GLT", "75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9", -19);
	g_pointers.m_readBitbufferDword = (readBitbufferDwordT)scan(baseAdr, imgSize, "RBD", "48 89 74 24 ? 57 48 83 EC 20 48 8B D9 33 C9 41 8B F0 8A", -5);
	g_pointers.m_readBitbufferArray = (readBitbufferArrayT)scan(baseAdr, imgSize, "RBA", "48 89 5C 24 ? 57 48 83 EC 30 41 8B F8 4C", 0);
	g_pointers.m_sendEventAck = (sendEventAckT)scan(baseAdr, imgSize, "SEA", "48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 7A", -5);
	g_pointers.m_receivedEvent = (receivedEventT)scan(baseAdr, imgSize, "RE", "66 41 83 F9 ? 0F 83", 0);
	g_pointers.m_receivedNetMessage = (receivedNetMessageT)scan(baseAdr, imgSize, "RNM", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 20 4C 8B 71 50 33 ED", 0);
	g_pointers.m_pedFactory = (CPedFactory**)rip(scan(baseAdr, imgSize, "PF", "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81", 3));
	g_pointers.m_networkPlayerMgr = (CNetworkPlayerMgr**)rip(scan(baseAdr, imgSize, "NPM", "48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF", 3));
	g_pointers.m_scriptGlobals = (intptr_t**)rip(scan(baseAdr, imgSize, "SG", "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", 3));
	printPatternNumbers();
}