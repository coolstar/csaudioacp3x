#ifndef _CSAUDIOACP3X_COMMON_CLASS_H_
#define _CSAUDIOACP3X_COMMON_CLASS_H_

#pragma warning (disable : 4127)

#include <initguid.h>
#include "definitions.h"
#include "hw.h"
#include "endpoints.h"

//=============================================================================
// Classes
//=============================================================================

///////////////////////////////////////////////////////////////////////////////
// CAdapterCommon
//   
class CAdapterCommon :
    public IAdapterCommon,
    public IAdapterPowerManagement,
    public CUnknown
{
private:
    PSERVICEGROUP           m_pServiceGroupWave;
    PDEVICE_OBJECT          m_pDeviceObject;
    PDEVICE_OBJECT          m_pPhysicalDeviceObject;
    WDFDEVICE               m_WdfDevice;            // Wdf device. 
    DEVICE_POWER_STATE      m_PowerState;
    PPORTCLSETWHELPER       m_pPortClsEtwHelper;

    static LONG             m_AdapterInstances;     // # of adapter objects.

    DWORD                   m_dwIdleRequests;
public:
    PCCsAudioAcp3xHW   m_pHW;                  // Virtual Simple Audio Sample HW object

    //=====================================================================
    // Default CUnknown
    DECLARE_STD_UNKNOWN();
    DEFINE_STD_CONSTRUCTOR(CAdapterCommon);
    ~CAdapterCommon();

    //=====================================================================
    // Default IAdapterPowerManagement
    IMP_IAdapterPowerManagement;

    //=====================================================================
    // IAdapterCommon methods      

    STDMETHODIMP_(NTSTATUS) Init
    (
        _In_  PRESOURCELIST           ResourceList,
        _In_  PDEVICE_OBJECT  DeviceObject
    );

    STDMETHODIMP_(PDEVICE_OBJECT)   GetDeviceObject(void);

    STDMETHODIMP_(PDEVICE_OBJECT)   GetPhysicalDeviceObject(void);

    STDMETHODIMP_(WDFDEVICE)        GetWdfDevice(void);

    STDMETHODIMP_(void)     SetWaveServiceGroup
    (
        _In_  PSERVICEGROUP   ServiceGroup
    );

    STDMETHODIMP_(BOOL)     bDevSpecificRead();

    STDMETHODIMP_(void)     bDevSpecificWrite
    (
        _In_  BOOL            bDevSpecific
    );
    STDMETHODIMP_(INT)      iDevSpecificRead();

    STDMETHODIMP_(void)     iDevSpecificWrite
    (
        _In_  INT             iDevSpecific
    );
    STDMETHODIMP_(UINT)     uiDevSpecificRead();

    STDMETHODIMP_(void)     uiDevSpecificWrite
    (
        _In_  UINT            uiDevSpecific
    );

    STDMETHODIMP_(ULONG)    MixerMuxRead(void);

    STDMETHODIMP_(void)     MixerMuxWrite
    (
        _In_  ULONG           Index
    );

    STDMETHODIMP_(void)     MixerReset(void);

    STDMETHODIMP_(LONG)     MixerPeakMeterRead
    (
        _In_  ULONG           Index,
        _In_  ULONG           Channel
    );

    STDMETHODIMP_(NTSTATUS) WriteEtwEvent
    (
        _In_ EPcMiniportEngineEvent    miniportEventType,
        _In_ ULONGLONG      ullData1,
        _In_ ULONGLONG      ullData2,
        _In_ ULONGLONG      ullData3,
        _In_ ULONGLONG      ullData4
    );

    STDMETHODIMP_(VOID)     SetEtwHelper
    (
        PPORTCLSETWHELPER _pPortClsEtwHelper
    );

    STDMETHODIMP_(NTSTATUS) InstallSubdevice
    (
        _In_opt_        PIRP                                        Irp,
        _In_            PWSTR                                       Name,
        _In_opt_        PWSTR                                       TemplateName,
        _In_            REFGUID                                     PortClassId,
        _In_            REFGUID                                     MiniportClassId,
        _In_opt_        PFNCREATEMINIPORT                           MiniportCreate,
        _In_            ULONG                                       cPropertyCount,
        _In_reads_opt_(cPropertyCount) const CSAUDIOACP3X_DEVPROPERTY* pProperties,
        _In_opt_        PVOID                                       DeviceContext,
        _In_            PENDPOINT_MINIPAIR                          MiniportPair,
        _In_opt_        PRESOURCELIST                               ResourceList,
        _In_            REFGUID                                     PortInterfaceId,
        _Out_opt_       PUNKNOWN* OutPortInterface,
        _Out_opt_       PUNKNOWN* OutPortUnknown,
        _Out_opt_       PUNKNOWN* OutMiniportUnknown
    );

    STDMETHODIMP_(NTSTATUS) UnregisterSubdevice
    (
        _In_opt_ PUNKNOWN               UnknownPort
    );

    STDMETHODIMP_(NTSTATUS) ConnectTopologies
    (
        _In_ PUNKNOWN                   UnknownTopology,
        _In_ PUNKNOWN                   UnknownWave,
        _In_ PHYSICALCONNECTIONTABLE* PhysicalConnections,
        _In_ ULONG                      PhysicalConnectionCount
    );

    STDMETHODIMP_(NTSTATUS) DisconnectTopologies
    (
        _In_ PUNKNOWN                   UnknownTopology,
        _In_ PUNKNOWN                   UnknownWave,
        _In_ PHYSICALCONNECTIONTABLE* PhysicalConnections,
        _In_ ULONG                      PhysicalConnectionCount
    );

    STDMETHODIMP_(NTSTATUS) InstallEndpointFilters
    (
        _In_opt_    PIRP                Irp,
        _In_        PENDPOINT_MINIPAIR  MiniportPair,
        _In_opt_    PVOID               DeviceContext,
        _Out_opt_   PUNKNOWN* UnknownTopology,
        _Out_opt_   PUNKNOWN* UnknownWave,
        _Out_opt_   PUNKNOWN* UnknownMiniportTopology,
        _Out_opt_   PUNKNOWN* UnknownMiniportWave
    );

    STDMETHODIMP_(NTSTATUS) RemoveEndpointFilters
    (
        _In_        PENDPOINT_MINIPAIR  MiniportPair,
        _In_opt_    PUNKNOWN            UnknownTopology,
        _In_opt_    PUNKNOWN            UnknownWave
    );

    STDMETHODIMP_(NTSTATUS) GetFilters
    (
        _In_        PENDPOINT_MINIPAIR  MiniportPair,
        _Out_opt_   PUNKNOWN* UnknownTopologyPort,
        _Out_opt_   PUNKNOWN* UnknownTopologyMiniport,
        _Out_opt_   PUNKNOWN* UnknownWavePort,
        _Out_opt_   PUNKNOWN* UnknownWaveMiniport
    );

    STDMETHODIMP_(NTSTATUS) SetIdlePowerManagement
    (
        _In_        PENDPOINT_MINIPAIR  MiniportPair,
        _In_        BOOL                bEnabled
    );

    STDMETHODIMP_(VOID) Cleanup();

    //=====================================================================
    // friends
    friend NTSTATUS         NewAdapterCommon
    (
        _Out_       PUNKNOWN* Unknown,
        _In_        REFCLSID,
        _In_opt_    PUNKNOWN                UnknownOuter,
        _In_        POOL_FLAGS              PoolFlags
    );

private:

    LIST_ENTRY m_SubdeviceCache;

    NTSTATUS GetCachedSubdevice
    (
        _In_ PWSTR Name,
        _Out_opt_ PUNKNOWN* OutUnknownPort,
        _Out_opt_ PUNKNOWN* OutUnknownMiniport
    );

    NTSTATUS CacheSubdevice
    (
        _In_ PWSTR Name,
        _In_ PUNKNOWN UnknownPort,
        _In_ PUNKNOWN UnknownMiniport
    );

    NTSTATUS RemoveCachedSubdevice
    (
        _In_ PWSTR Name
    );

    VOID EmptySubdeviceCache();

    NTSTATUS CreateAudioInterfaceWithProperties
    (
        _In_ PCWSTR                                                 ReferenceString,
        _In_opt_ PCWSTR                                             TemplateReferenceString,
        _In_ ULONG                                                  cPropertyCount,
        _In_reads_opt_(cPropertyCount) const CSAUDIOACP3X_DEVPROPERTY* pProperties,
        _Out_ _At_(AudioSymbolicLinkName->Buffer, __drv_allocatesMem(Mem)) PUNICODE_STRING AudioSymbolicLinkName
    );

    NTSTATUS MigrateDeviceInterfaceTemplateParameters
    (
        _In_ PUNICODE_STRING    SymbolicLinkName,
        _In_opt_ PCWSTR         TemplateReferenceString
    );
};

typedef struct _MINIPAIR_UNKNOWN
{
    LIST_ENTRY              ListEntry;
    WCHAR                   Name[MAX_PATH];
    PUNKNOWN                PortInterface;
    PUNKNOWN                MiniportInterface;
    PADAPTERPOWERMANAGEMENT PowerInterface;
} MINIPAIR_UNKNOWN;

#define MAX_DEVICE_REG_KEY_LENGTH 0x100

#endif // _CSAUDIOACP3X_COMMON_CLASS_H_