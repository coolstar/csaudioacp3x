
/*++

Copyright (c) Microsoft Corporation All Rights Reserved

Module Name:

    headphonetopo.h

Abstract:

    Declaration of topology miniport for the headphone (jack).
--*/

#ifndef _CSAUDIOACP3X_HEADPHONETOPO_H_
#define _CSAUDIOACP3X_HEADPHONETOPO_H_

NTSTATUS PropertyHandler_HeadphoneTopoFilter(_In_ PPCPROPERTY_REQUEST PropertyRequest);

NTSTATUS PropertyHandler_HeadphoneTopology(_In_ PPCPROPERTY_REQUEST PropertyRequest);

#endif // _CSAUDIOACP3X_HEADPHONETOPO_H_
