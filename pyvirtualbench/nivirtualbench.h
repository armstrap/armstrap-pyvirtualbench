/*============================================================================*/
/*                  National Instruments / VirtualBench API                   */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 2014-2018.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:   nivirtualbench.h                                                  */
/* Purpose: Include file to interact with the NI VirtualBench API             */
/*                                                                            */
/*============================================================================*/

#ifndef ___nivirtualbench_h___
#define ___nivirtualbench_h___

#if !defined(NIVB_DONT_DEFINE_STDINT)
#if defined(_MSC_VER) && _MSC_VER < 1600
   // <stdint.h> not present in Visual Studio prior to 2010.
   typedef signed   __int8  int8_t;
   typedef signed   __int16 int16_t;
   typedef signed   __int32 int32_t;
   typedef signed   __int64 int64_t;
   typedef unsigned __int8  uint8_t;
   typedef unsigned __int16 uint16_t;
   typedef unsigned __int32 uint32_t;
   typedef unsigned __int64 uint64_t;
#elif defined(_CVI_) && _CVI_ < 910
   // <stdint.h> not present in CVI prior to 2009.
   typedef signed   char    int8_t;
   typedef signed   short   int16_t;
   typedef signed   int     int32_t;
   typedef signed   __int64 int64_t;
   typedef unsigned char    uint8_t;
   typedef unsigned short   uint16_t;
   typedef unsigned int     uint32_t;
   typedef unsigned __int64 uint64_t;
#else
   // C99 and Visual Studio 2010 and later.
   #include <stdint.h>
#endif
#endif

#if !defined(NIVB_DONT_DEFINE_STDBOOL)
#if defined(_MSC_VER) && _MSC_VER < 1800 && !defined(_BOOL_DEFINED)
   // <stdbool.h> not present in Visual Studio prior to 2013.
   #if !defined(__cplusplus)
      typedef unsigned __int8 _Bool;
      typedef _Bool bool;
      #define true   1
      #define false  0
      #define __bool_true_false_are_defined 1
   #else
      typedef bool _Bool;
   #endif
#elif defined(_CVI_)
   // <stdbool.h> not present in CVI.
   #if _CVI_ < 1300
      // _Bool not defined in CVI prior to 2013.
      typedef char _Bool;
   #endif

   typedef _Bool bool;
   #define true   1
   #define false  0
   #define __bool_true_false_are_defined 1
#else
   #include <stdbool.h>
#endif
#endif

// CVI doesn't support Unicode.
#if defined(_WIN32) && !defined(_CVI_) && !defined(_NATIVE_WCHAR_T_DEFINED) && !defined(WCHAR_MIN) && !defined(NIVB_DONT_INCLUDE_WCHAR_H)
   #include <wchar.h>
#endif

#if defined(_MSC_VER)
   #define NIVB_INLINE __inline
#elif defined(_CVI_) && _CVI_ < 900
   // CVI doesn't support inline prior to 9.0.
   #define NIVB_INLINE
#else
   #define NIVB_INLINE inline
#endif

#if defined(__cplusplus)
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
// Enumerations
////////////////////////////////////////////////////////////////////////////////

// If the compiler supports it, we specify int32_t as our enum type.
#if defined(__cplusplus) && ((defined(_MSC_VER) && _MSC_VER >= 1700) || __cplusplus >= 201103L)
#define NIVB_ENUM_TYPE : int32_t
#else
#define NIVB_ENUM_TYPE
#endif

typedef enum NIVB_ENUM_TYPE {
   niVB_Language_CurrentThreadLocale = 0,
   niVB_Language_English = 1033,
   niVB_Language_French = 1036,
   niVB_Language_German = 1031,
   niVB_Language_Japanese = 1041,
   niVB_Language_Korean = 1042,
   niVB_Language_SimplifiedChinese = 2052,
} niVB_Language;

typedef enum NIVB_ENUM_TYPE {
   niVB_Edge_Rising = 0,
   niVB_Edge_Falling = 1,
} niVB_Edge;

typedef enum NIVB_ENUM_TYPE {
   niVB_EdgeWithEither_Rising = 0,
   niVB_EdgeWithEither_Falling = 1,
   niVB_EdgeWithEither_Either = 2,
} niVB_EdgeWithEither;

typedef enum NIVB_ENUM_TYPE {
   niVB_ClockPhase_FirstEdge = 0,
   niVB_ClockPhase_SecondEdge = 1,
} niVB_ClockPhase;

typedef enum NIVB_ENUM_TYPE {
   niVB_Polarity_IdleLow = 0,
   niVB_Polarity_IdleHigh = 1,
} niVB_Polarity;

typedef enum NIVB_ENUM_TYPE {
   niVB_Waveform_Sine = 0,
   niVB_Waveform_Square = 1,
   niVB_Waveform_Triangle = 2,
   niVB_Waveform_DC = 3,
} niVB_Waveform;

typedef enum NIVB_ENUM_TYPE {
   niVB_CalibrationAction_Commit = 0,
   niVB_CalibrationAction_Cancel = 1,
} niVB_CalibrationAction;

typedef enum NIVB_ENUM_TYPE {
   niVB_Dig_SignalSource_FGENStart = 0,
   niVB_Dig_SignalSource_MSOTrigger = 1,
} niVB_Dig_SignalSource;

typedef enum NIVB_ENUM_TYPE {
   niVB_FGEN_WaveformMode_Standard = 0,
   niVB_FGEN_WaveformMode_Arbitrary = 1,
} niVB_FGEN_WaveformMode;

typedef enum NIVB_ENUM_TYPE {
   niVB_FGEN_GenerationStatus_Running = 0,
   niVB_FGEN_GenerationStatus_Stopped = 1,
} niVB_FGEN_GenerationStatus;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_ProbeAttenuation_1x = 1,
   niVB_MSO_ProbeAttenuation_10x = 10,
} niVB_MSO_ProbeAttenuation;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_Coupling_AC = 0,
   niVB_MSO_Coupling_DC = 1,
} niVB_MSO_Coupling;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_SamplingMode_Sample = 0,
   niVB_MSO_SamplingMode_PeakDetect = 1,
} niVB_MSO_SamplingMode;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_DigitalSampleRateControl_Automatic = 0,
   niVB_MSO_DigitalSampleRateControl_Manual = 1,
} niVB_MSO_DigitalSampleRateControl;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_BufferControl_Automatic = 0,
   niVB_MSO_BufferControl_Manual = 1,
} niVB_MSO_BufferControl;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_TriggerInstance_A = 0,
   niVB_MSO_TriggerInstance_B = 1,
} niVB_MSO_TriggerInstance;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_TriggerType_Immediate = 0,
   niVB_MSO_TriggerType_AnalogEdge = 1,
   niVB_MSO_TriggerType_DigitalEdge = 2,
   niVB_MSO_TriggerType_DigitalPattern = 3,
   niVB_MSO_TriggerType_DigitalGlitch = 4,
   niVB_MSO_TriggerType_AnalogPulseWidth = 5,
   niVB_MSO_TriggerType_DigitalPulseWidth = 6,
} niVB_MSO_TriggerType;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_AcquisitionStatus_Stopped = 0,
   niVB_MSO_AcquisitionStatus_Running = 1,
   niVB_MSO_AcquisitionStatus_Triggered = 2,
   niVB_MSO_AcquisitionStatus_AcquisitionComplete = 3,
} niVB_MSO_AcquisitionStatus;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_TriggerReason_Normal = 0,
   niVB_MSO_TriggerReason_Forced = 1,
   niVB_MSO_TriggerReason_Auto = 2,
} niVB_MSO_TriggerReason;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_ComparisonMode_GreaterThanUpperLimit = 0,
   niVB_MSO_ComparisonMode_LessThanLowerLimit = 1,
   niVB_MSO_ComparisonMode_InsideLimits = 2,
   niVB_MSO_ComparisonMode_OutsideLimits = 3,
} niVB_MSO_ComparisonMode;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_TriggerPolarity_Positive = 0,
   niVB_MSO_TriggerPolarity_Negative = 1,
} niVB_MSO_TriggerPolarity;

typedef enum NIVB_ENUM_TYPE {
   niVB_MSO_InputImpedance_1megaohm = 0,
   niVB_MSO_InputImpedance_50ohms = 1,
} niVB_MSO_InputImpedance;

typedef enum NIVB_ENUM_TYPE {
   niVB_DMM_Function_DCVolts = 0,
   niVB_DMM_Function_ACVolts = 1,
   niVB_DMM_Function_DCCurrent = 2,
   niVB_DMM_Function_ACCurrent = 3,
   niVB_DMM_Function_Resistance = 4,
   niVB_DMM_Function_Diode = 5,
} niVB_DMM_Function;

typedef enum NIVB_ENUM_TYPE {
   niVB_DMM_CurrentTerminal_Low = 0,
   niVB_DMM_CurrentTerminal_High = 1,
} niVB_DMM_CurrentTerminal;

typedef enum NIVB_ENUM_TYPE {
   niVB_DMM_InputResistance_10MOhm = 0,
   niVB_DMM_InputResistance_10GOhm = 1,
} niVB_DMM_InputResistance;

typedef enum NIVB_ENUM_TYPE {
   niVB_PS_State_ConstantCurrent = 0,
   niVB_PS_State_ConstantVoltage = 1,
} niVB_PS_State;

typedef enum NIVB_ENUM_TYPE {
   niVB_PS_CalType_Voltage = 0,
   niVB_PS_CalType_Current = 1,
} niVB_PS_CalType;

typedef enum NIVB_ENUM_TYPE {
   niVB_I2C_AddressSize_7Bits = 0,
   niVB_I2C_AddressSize_10Bits = 1,
} niVB_I2C_AddressSize;

typedef enum NIVB_ENUM_TYPE {
   niVB_I2C_ClockRate_100kHz = 0,
   niVB_I2C_ClockRate_400kHz = 1,
   niVB_I2C_ClockRate_1MHz = 2,
} niVB_I2C_ClockRate;


////////////////////////////////////////////////////////////////////////////////
// Error Handling
////////////////////////////////////////////////////////////////////////////////

typedef enum NIVB_ENUM_TYPE {
   niVB_Status_Success = 0,
   niVB_Status_ErrorCalFunctionNotSupported = -375995,
   niVB_Status_ErrorInputTerminationOverloaded = -375993,
   niVB_Status_ErrorArbClipping = -375992,
   niVB_Status_ErrorInvalidOperationForMultipleChansEdgeTrigger = -375991,
   niVB_Status_ErrorI2CArbLost = -375990,
   niVB_Status_ErrorI2CNak = -375989,
   niVB_Status_ErrorI2CTimeout = -375988,
   niVB_Status_ErrorUnknownDevicePidOrVid = -375987,
   niVB_Status_ErrorCannotStartTransferWhileInProgress = -375986,
   niVB_Status_ErrorInvalidPointer = -375985,
   niVB_Status_ErrorInvalidFrameSize = -375984,
   niVB_Status_ErrorInvalidNextCalDate = -375983,
   niVB_Status_ErrorSetNextCalDateWithLastCalDate = -375982,
   niVB_Status_ErrorLastCalDateBlank = -375981,
   niVB_Status_ErrorDeviceNotInStorage = -375980,
   niVB_Status_ErrorDeviceDidNotReboot = -375979,
   niVB_Status_ErrorInvalidConfigurationFileWrongModel = -375978,
   niVB_Status_ErrorInvalidDeviceNameHasAllNumbers = -375977,
   niVB_Status_ErrorHostnameResolutionTimeout = -375976,
   niVB_Status_ErrorHostnameResolutionFailure = -375975,
   niVB_Status_ErrorDigitalInitializationFailed = -375974,
   niVB_Status_ErrorFirmwareIsTooNew = -375971,
   niVB_Status_ErrorFirmwareIsTooOld = -375970,
   niVB_Status_ErrorInvalidMethod = -375969,
   niVB_Status_ErrorOvertemp = -375968,
   niVB_Status_ErrorInvalidDeviceName = -375967,
   niVB_Status_ErrorFGENOvervoltage = -375966,
   niVB_Status_ErrorCannotRenameDeviceBecauseNameInUse = -375965,
   niVB_Status_ErrorDeviceWithSameNameAlreadyExists = -375964,
   niVB_Status_ErrorInternalStorageFailure = -375963,
   niVB_Status_ErrorLAAcquisitionLength = -375962,
   niVB_Status_ErrorScopeAcquisitionLength = -375961,
   niVB_Status_ErrorCannotDeleteUsb = -375960,
   niVB_Status_ErrorInvalidNetworkPathSyntax = -375959,
   niVB_Status_ErrorCannotRunWhenNoChannelsEnabled = -375958,
   niVB_Status_ErrorTriggerPatternSize = -375957,
   niVB_Status_ErrorTransportTimeout = -375956,
   niVB_Status_ErrorPSCurrentCalNeedsShortCircuit = -375955,
   niVB_Status_ErrorPSVoltageCalNeedsOpenCircuit = -375954,
   niVB_Status_ErrorHardwareFault = -375950,
   niVB_Status_ErrorNoPermissionForOperationWhenNotLoggedIn = -375949,
   niVB_Status_ErrorNoPermissionForOperation = -375948,
   niVB_Status_ErrorAuthenticationFailure = -375947,
   niVB_Status_ErrorAuthenticationCredentialsInvalid = -375946,
   niVB_Status_ErrorPSReadWhenDisabled = -375945,
   niVB_Status_ErrorDeviceIsNotAuthentic = -375944,
   niVB_Status_ErrorCalibrationSignalInvalid = -375943,
   niVB_Status_ErrorInvalidCalibrationOrder = -375942,
   niVB_Status_ErrorUnknownDevice = -375941,
   niVB_Status_ErrorCalFailed = -375940,
   niVB_Status_ErrorNotEnoughCalRefPoints = -375939,
   niVB_Status_ErrorNoCalRefPoint = -375938,
   niVB_Status_ErrorInvalidCalRefPoint = -375937,
   niVB_Status_ErrorPSInitializationFailed = -375936,
   niVB_Status_ErrorFGENInitializationFailed = -375935,
   niVB_Status_ErrorScopeInitializationFailed = -375934,
   niVB_Status_ErrorDMMInitializationFailed = -375933,
   niVB_Status_ErrorConfigDataIsCorrupt = -375932,
   niVB_Status_ErrorPNGFileDoesNotContainConfigurationData = -375931,
   niVB_Status_ErrorPNGFileIsCorrupt = -375930,
   niVB_Status_ErrorNoPermissionToWriteFile = -375929,
   niVB_Status_ErrorNoPermissionToReadFile = -375928,
   niVB_Status_ErrorFileIOError = -375927,
   niVB_Status_ErrorNoSpaceLeftOnDevice = -375926,
   niVB_Status_ErrorInvalidFileName = -375925,
   niVB_Status_ErrorUnknownConfigurationFileFormat = -375924,
   niVB_Status_ErrorCalibrationCorrupt = -375923,
   niVB_Status_ErrorInvalidCalibrationPassword = -375922,
   niVB_Status_ErrorTooManySavedConfigurations = -375921,
   niVB_Status_ErrorConfigurationNameIsTooLong = -375920,
   niVB_Status_ErrorSavedConfigurationDataIsTooLarge = -375919,
   niVB_Status_ErrorSavedConfigurationAlreadyExists = -375918,
   niVB_Status_ErrorSavedConfigurationDoesNotExist = -375917,
   niVB_Status_ErrorInvalidConfigurationFileFormat = -375916,
   niVB_Status_ErrorInvalidOperationForMultipleChans = -375914,
   niVB_Status_ErrorCannotForceTriggerWhenStopped = -375913,
   niVB_Status_ErrorOnlyOneChannelValidForRate = -375912,
   niVB_Status_ErrorMultipleTriggerSources = -375911,
   niVB_Status_ErrorTriggerChannelsNotEnabled = -375910,
   niVB_Status_ErrorCannotReadWhenStopped = -375909,
   niVB_Status_ErrorNotConnected = -375908,
   niVB_Status_ErrorCannotChangeConfigWhileRunning = -375907,
   niVB_Status_ErrorInvalidSession = -375906,
   niVB_Status_ErrorInvalidChannelName = -375905,
   niVB_Status_ErrorDigNumLinesDoesntMatchData = -375904,
   niVB_Status_ErrorReservationFailed = -375903,
   niVB_Status_ErrorInvalidConfiguration = -375902,
   niVB_Status_ErrorOutOfMemory = -375901,
   niVB_Status_ErrorInternal = -375900,
   niVB_Status_WarningCApiHeaderOutOfDate = 374310,
   niVB_Status_WarningNotEnoughMemory = 374309,
   niVB_Status_WarningDeviceNameUsedAsHostname = 374308,
   niVB_Status_WarningDMMHardwareOverrange = 374307,
   niVB_Status_WarningDeviceDifferentFromExpected = 374306,
   niVB_Status_WarningDeviceHasBeenRenamed = 374305,
   niVB_Status_WarningNoSignalSuitableForSampleRateInAutoSetup = 374304,
   niVB_Status_WarningNoSignalsFoundForAutoSetup = 374303,
   niVB_Status_WarningImportArbMode = 374302,
   niVB_Status_WarningDMMOverrange = 374301,
   niVB_Status_WarningArbClipping = 374300,
} niVB_Status;

static NIVB_INLINE bool niVB_Status_Warning(niVB_Status status) { return (bool)((int32_t)(status) > 0); }
static NIVB_INLINE bool niVB_Status_Failed(niVB_Status status) { return (bool)((int32_t)(status) < 0); }
static NIVB_INLINE bool niVB_Status_Assign(niVB_Status* status, niVB_Status other)
{
   if (status)
   {
      if ((*status == niVB_Status_Success) && (other != niVB_Status_Success)) { *status = other; return true; }
      if (niVB_Status_Warning(*status) && niVB_Status_Failed(other)) { *status = other; return true; }
   }
   return false;
}

////////////////////////////////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////////////////////////////////

typedef struct niVB_LibraryHandleT* niVB_LibraryHandle;

typedef struct niVB_Dig_InstrumentHandleT*  niVB_Dig_InstrumentHandle;
typedef struct niVB_FGEN_InstrumentHandleT* niVB_FGEN_InstrumentHandle;
typedef struct niVB_MSO_InstrumentHandleT*  niVB_MSO_InstrumentHandle;
typedef struct niVB_DMM_InstrumentHandleT*  niVB_DMM_InstrumentHandle;
typedef struct niVB_PS_InstrumentHandleT*   niVB_PS_InstrumentHandle;
typedef struct niVB_SPI_InstrumentHandleT*  niVB_SPI_InstrumentHandle;
typedef struct niVB_I2C_InstrumentHandleT*  niVB_I2C_InstrumentHandle;

typedef struct niVB_FGENCal_InstrumentHandleT* niVB_FGENCal_InstrumentHandle;
typedef struct niVB_MSOCal_InstrumentHandleT*  niVB_MSOCal_InstrumentHandle;
typedef struct niVB_DMMCal_InstrumentHandleT*  niVB_DMMCal_InstrumentHandle;
typedef struct niVB_PSCal_InstrumentHandleT*   niVB_PSCal_InstrumentHandle;

typedef struct {
   uint32_t t1;
   uint32_t t2;
   uint32_t t3;
   uint32_t t4;
} niVB_Timestamp;

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#define NIVB_DECL __cdecl
#else
#define NIVB_DECL
#endif

#define NIVB_LIBRARY_VERSION 302039040

/*
 * Initialize the VirtualBench library.  This must be called at least once for
 * the application.
 *
 * The 'version' parameter must be set to the NIVB_LIBRARY_VERSION constant.
 */
niVB_Status NIVB_DECL niVB_Initialize(uint32_t version, niVB_LibraryHandle* handle);

/*
 * Finalize the VirtualBench library.
 */
niVB_Status NIVB_DECL niVB_Finalize(niVB_LibraryHandle handle);

/*
 * Return the version of the VirtualBench runtime library.
 */
niVB_Status NIVB_DECL niVB_GetLibraryVersion(uint32_t* version);

/*
 * Converts a timestamp to seconds and fractional seconds.
 */
niVB_Status NIVB_DECL niVB_ConvertTimestampToValues(
   niVB_Timestamp timestamp,
   int64_t* secondsSince1970,
   double* fractionalSeconds);

/*
 * Converts seconds and fractional seconds to a timestamp.
 */
niVB_Status NIVB_DECL niVB_ConvertValuesToTimestamp(
   int64_t secondsSince1970,
   double fractionalSeconds,
   niVB_Timestamp* timestamp);

/*
 * Adds a networked device to the system.
 */
niVB_Status NIVB_DECL niVB_AddNetworkDevice(
   niVB_LibraryHandle libraryHandle,
   const char* ipOrHostname,
   int32_t timeoutInMs,
   char* device,
   size_t deviceSize,
   size_t* deviceSizeOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_AddNetworkDeviceW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* ipOrHostname,
   int32_t timeoutInMs,
   wchar_t* device,
   size_t deviceSize,
   size_t* deviceSizeOut);
#endif

/*
 * Removes a device from the system. The device must not be connected via USB 
 * to be removed.
 */
niVB_Status NIVB_DECL niVB_RemoveDevice(
   niVB_LibraryHandle libraryHandle,
   const char* device);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_RemoveDeviceW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* device);
#endif

/*
 * Collapses a channel string into a comma and colon-delimited equivalent.
 */
niVB_Status NIVB_DECL niVB_CollapseChannelString(
   niVB_LibraryHandle libraryHandle,
   const char* namesIn,
   char* namesOut,
   size_t namesOutSize,
   size_t* namesOutSizeOut,
   size_t* numberOfChannels);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_CollapseChannelStringW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* namesIn,
   wchar_t* namesOut,
   size_t namesOutSize,
   size_t* namesOutSizeOut,
   size_t* numberOfChannels);
#endif

/*
 * Expands a channel string into a comma-delimited (no colon) equivalent.
 */
niVB_Status NIVB_DECL niVB_ExpandChannelString(
   niVB_LibraryHandle libraryHandle,
   const char* namesIn,
   char* namesOut,
   size_t namesOutSize,
   size_t* namesOutSizeOut,
   size_t* numberOfChannels);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_ExpandChannelStringW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* namesIn,
   wchar_t* namesOut,
   size_t namesOutSize,
   size_t* namesOutSizeOut,
   size_t* numberOfChannels);
#endif

/*
 * Returns the extended error information for the last error to occur on the 
 * specified library handle.
 */
niVB_Status NIVB_DECL niVB_GetExtendedErrorInformation(
   niVB_LibraryHandle libraryHandle,
   niVB_Language language,
   char* errorInformation,
   size_t errorInformationSize,
   size_t* errorInformationSizeOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_GetExtendedErrorInformationW(
   niVB_LibraryHandle libraryHandle,
   niVB_Language language,
   wchar_t* errorInformation,
   size_t errorInformationSize,
   size_t* errorInformationSizeOut);
#endif

/*
 * Returns the error description for the given status.
 */
niVB_Status NIVB_DECL niVB_GetErrorDescription(
   niVB_LibraryHandle libraryHandle,
   niVB_Status code,
   niVB_Language language,
   char* description,
   size_t descriptionSize,
   size_t* descriptionSizeOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_GetErrorDescriptionW(
   niVB_LibraryHandle libraryHandle,
   niVB_Status code,
   niVB_Language language,
   wchar_t* description,
   size_t descriptionSize,
   size_t* descriptionSizeOut);
#endif

/*
 * Attempts to log in to a networked device. Logging in to a device grants 
 * access to the permissions set for the specified user in NI Web-Based 
 * Monitoring and Configuration.
 */
niVB_Status NIVB_DECL niVB_LogIn(
   niVB_LibraryHandle libraryHandle,
   const char* device,
   const char* username,
   const char* password);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_LogInW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* device,
   const wchar_t* username,
   const wchar_t* password);
#endif

/*
 * Logs out of a networked device that you are logged in to. Logging out of a 
 * device revokes access to the permissions set for the specified user in NI 
 * Web-Based Monitoring and Configuration.
 */
niVB_Status NIVB_DECL niVB_LogOut(
   niVB_LibraryHandle libraryHandle,
   const char* device);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_LogOutW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* device);
#endif

/*
 * Sets calibration information for the specified device.
 */
niVB_Status NIVB_DECL niVB_Cal_SetCalibrationInformation(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   niVB_Timestamp calibrationDate,
   int32_t calibrationInterval,
   const char* password);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_Cal_SetCalibrationInformationW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   niVB_Timestamp calibrationDate,
   int32_t calibrationInterval,
   const wchar_t* password);
#endif

/*
 * Sets a new calibration password for the specified device. This method 
 * requires the current password for the device, and returns an error if the 
 * specified password is incorrect.
 */
niVB_Status NIVB_DECL niVB_Cal_SetCalibrationPassword(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   const char* currentPassword,
   const char* newPassword);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_Cal_SetCalibrationPasswordW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   const wchar_t* currentPassword,
   const wchar_t* newPassword);
#endif

/*
 * Returns calibration information for the specified device, including the 
 * last calibration date and calibration interval.
 */
niVB_Status NIVB_DECL niVB_Cal_GetCalibrationInformation(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   niVB_Timestamp* calibrationDate,
   int32_t* recommendedCalibrationInterval,
   int32_t* calibrationInterval);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_Cal_GetCalibrationInformationW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   niVB_Timestamp* calibrationDate,
   int32_t* recommendedCalibrationInterval,
   int32_t* calibrationInterval);
#endif

/*
 * Establishes communication with the device. This method should be called 
 * once per session.
 */
niVB_Status NIVB_DECL niVB_Dig_Initialize(
   niVB_LibraryHandle libraryHandle,
   const char* lines,
   bool reset,
   niVB_Dig_InstrumentHandle* instrumentHandle);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_Dig_InitializeW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* lines,
   bool reset,
   niVB_Dig_InstrumentHandle* instrumentHandle);
#endif

/*
 * Sets all specified lines to a high-impedance state.
 */
niVB_Status NIVB_DECL niVB_Dig_TristateLines(
   niVB_Dig_InstrumentHandle instrumentHandle,
   const char* lines);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_Dig_TristateLinesW(
   niVB_Dig_InstrumentHandle instrumentHandle,
   const wchar_t* lines);
#endif

/*
 * Exports a signal to the specified line.
 */
niVB_Status NIVB_DECL niVB_Dig_ExportSignal(
   niVB_Dig_InstrumentHandle instrumentHandle,
   const char* line,
   niVB_Dig_SignalSource signal);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_Dig_ExportSignalW(
   niVB_Dig_InstrumentHandle instrumentHandle,
   const wchar_t* line,
   niVB_Dig_SignalSource signal);
#endif

/*
 * Indicates the current line configurations. Tristate Lines, Static Lines, 
 * and Export Lines contain comma-separated range and/or colon-delimited lists 
 * of all lines specified in Dig Initialize
 */
niVB_Status NIVB_DECL niVB_Dig_QueryLineConfiguration(
   niVB_Dig_InstrumentHandle instrumentHandle,
   char* tristateLines,
   size_t tristateLinesSize,
   size_t* tristateLinesSizeOut,
   char* staticLines,
   size_t staticLinesSize,
   size_t* staticLinesSizeOut,
   char* exportLines,
   size_t exportLinesSize,
   size_t* exportLinesSizeOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_Dig_QueryLineConfigurationW(
   niVB_Dig_InstrumentHandle instrumentHandle,
   wchar_t* tristateLines,
   size_t tristateLinesSize,
   size_t* tristateLinesSizeOut,
   wchar_t* staticLines,
   size_t staticLinesSize,
   size_t* staticLinesSizeOut,
   wchar_t* exportLines,
   size_t exportLinesSize,
   size_t* exportLinesSizeOut);
#endif

/*
 * Indicates the signal being exported on the specified line. Use Dig Query 
 * Line Configuration to check the state of a line.
 */
niVB_Status NIVB_DECL niVB_Dig_QueryExportSignal(
   niVB_Dig_InstrumentHandle instrumentHandle,
   const char* line,
   niVB_Dig_SignalSource* signal);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_Dig_QueryExportSignalW(
   niVB_Dig_InstrumentHandle instrumentHandle,
   const wchar_t* line,
   niVB_Dig_SignalSource* signal);
#endif

/*
 * Writes data to the specified lines.
 */
niVB_Status NIVB_DECL niVB_Dig_Write(
   niVB_Dig_InstrumentHandle instrumentHandle,
   const char* lines,
   const bool* data,
   size_t dataSize);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_Dig_WriteW(
   niVB_Dig_InstrumentHandle instrumentHandle,
   const wchar_t* lines,
   const bool* data,
   size_t dataSize);
#endif

/*
 * Reads the current state of the specified lines.
 */
niVB_Status NIVB_DECL niVB_Dig_Read(
   niVB_LibraryHandle libraryHandle,
   const char* lines,
   bool* data,
   size_t dataSize,
   size_t* dataSizeOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_Dig_ReadW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* lines,
   bool* data,
   size_t dataSize,
   size_t* dataSizeOut);
#endif

/*
 * Resets the session configuration to default values, and resets the device 
 * and driver software to a known state.
 */
niVB_Status NIVB_DECL niVB_Dig_ResetInstrument(
   niVB_Dig_InstrumentHandle instrumentHandle);

/*
 * Stops the session and deallocates any resources acquired during the 
 * session. If output is enabled on any channels, they remain in their current 
 * state and continue to output data.
 */
niVB_Status NIVB_DECL niVB_Dig_Close(
   niVB_Dig_InstrumentHandle instrumentHandleIn);

/*
 * Establishes communication with the device. This method should be called 
 * once per session.
 */
niVB_Status NIVB_DECL niVB_FGEN_Initialize(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   bool reset,
   niVB_FGEN_InstrumentHandle* instrumentHandle);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_FGEN_InitializeW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   bool reset,
   niVB_FGEN_InstrumentHandle* instrumentHandle);
#endif

/*
 * Configures the instrument to output a standard waveform.
 */
niVB_Status NIVB_DECL niVB_FGEN_ConfigureStandardWaveform(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   niVB_Waveform waveformFunction,
   double amplitude,
   double dcOffset,
   double frequency,
   double dutyCycle);

/*
 * Configures the instrument to output a waveform. The waveform is output 
 * either after the end of the current waveform if output is enabled, or 
 * immediately after output is enabled.
 */
niVB_Status NIVB_DECL niVB_FGEN_ConfigureArbitraryWaveform(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   const double* waveform,
   size_t waveformSize,
   double samplePeriod);

/*
 * Configures the instrument to output an arbitrary waveform with a specified 
 * gain and offset value. The waveform is output either after the end of the 
 * current waveform if output is enabled, or immediately after output is 
 * enabled.
 */
niVB_Status NIVB_DECL niVB_FGEN_ConfigureArbitraryWaveformGainAndOffset(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   double gain,
   double dcOffset);

/*
 * Enables or disables the filter on the instrument.
 */
niVB_Status NIVB_DECL niVB_FGEN_EnableFilter(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   bool enableFilter);

/*
 * Indicates whether the waveform output by the instrument is a standard or 
 * arbitrary waveform.
 */
niVB_Status NIVB_DECL niVB_FGEN_QueryWaveformMode(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   niVB_FGEN_WaveformMode* waveformMode);

/*
 * Returns the settings for a standard waveform generation.
 */
niVB_Status NIVB_DECL niVB_FGEN_QueryStandardWaveform(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   niVB_Waveform* waveformFunction,
   double* amplitude,
   double* dcOffset,
   double* frequency,
   double* dutyCycle);

/*
 * Returns the settings for arbitrary waveform generation.
 */
niVB_Status NIVB_DECL niVB_FGEN_QueryArbitraryWaveform(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   double* sampleRate);

/*
 * Returns the settings for arbitrary waveform generation that includes gain 
 * and offset settings.
 */
niVB_Status NIVB_DECL niVB_FGEN_QueryArbitraryWaveformGainAndOffset(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   double* gain,
   double* offset);

/*
 * Indicates whether the filter is enabled on the instrument.
 */
niVB_Status NIVB_DECL niVB_FGEN_QueryFilter(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   bool* filterEnabled);

/*
 * Returns the status of waveform generation on the instrument.
 */
niVB_Status NIVB_DECL niVB_FGEN_QueryGenerationStatus(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   niVB_FGEN_GenerationStatus* status);

/*
 * Transitions the session from the Stopped state to the Running state.
 */
niVB_Status NIVB_DECL niVB_FGEN_Run(
   niVB_FGEN_InstrumentHandle instrumentHandle);

/*
 * Performs offset nulling calibration on the device. You must run FGEN 
 * Initialize prior to running this method.
 */
niVB_Status NIVB_DECL niVB_FGEN_SelfCalibrate(
   niVB_FGEN_InstrumentHandle instrumentHandle);

/*
 * Transitions the acquisition from either the Triggered or Running state to 
 * the Stopped state.
 */
niVB_Status NIVB_DECL niVB_FGEN_Stop(
   niVB_FGEN_InstrumentHandle instrumentHandle);

/*
 * Resets the session configuration to default values, and resets the device 
 * and driver software to a known state.
 */
niVB_Status NIVB_DECL niVB_FGEN_ResetInstrument(
   niVB_FGEN_InstrumentHandle instrumentHandle);

/*
 * Exports a configuration file for use with the function generator.
 */
niVB_Status NIVB_DECL niVB_FGEN_ExportConfiguration(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_FGEN_ExportConfigurationW(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Imports a configuration file for use with the function generator. You can 
 * import PNG files exported from the VirtualBench Application or files 
 * created from FGEN Export Configuration.
 */
niVB_Status NIVB_DECL niVB_FGEN_ImportConfiguration(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_FGEN_ImportConfigurationW(
   niVB_FGEN_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Stops the session and deallocates any resources acquired during the 
 * session. If output is enabled on any channels, they remain in their current 
 * state and continue to output data.
 */
niVB_Status NIVB_DECL niVB_FGEN_Close(
   niVB_FGEN_InstrumentHandle instrumentHandleIn);

/*
 * Returns instrument information from the last successful calibration 
 * adjustment.
 */
niVB_Status NIVB_DECL niVB_FGEN_GetCalibrationAdjustmentInformation(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   niVB_Timestamp* adjustmentDate,
   double* adjustmentTemperature);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_FGEN_GetCalibrationAdjustmentInformationW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   niVB_Timestamp* adjustmentDate,
   double* adjustmentTemperature);
#endif

/*
 * Opens a calibration session with the instrument. The instrument is reset 
 * upon successful completion of this method. This method returns an error if 
 * the instrument is reserved or if Password is incorrect.
 */
niVB_Status NIVB_DECL niVB_FGEN_InitializeCalibration(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   const char* password,
   niVB_FGENCal_InstrumentHandle* instrumentHandle);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_FGEN_InitializeCalibrationW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   const wchar_t* password,
   niVB_FGENCal_InstrumentHandle* instrumentHandle);
#endif

/*
 * Configures the instrument to output the offset values of the function 
 * generator.
 */
niVB_Status NIVB_DECL niVB_FGEN_SetupOffsetCalibration(
   niVB_FGENCal_InstrumentHandle instrumentHandle,
   bool enableFilter);

/*
 * Stores a measured reference value to the instrument and associates that 
 * value with the adjustment point and filter values previously configured 
 * with FGEN Setup Offset Calibration. You must run FGEN Setup Offset 
 * Calibration prior to running this method.
 */
niVB_Status NIVB_DECL niVB_FGEN_AdjustOffsetCalibration(
   niVB_FGENCal_InstrumentHandle instrumentHandle,
   double referenceValue,
   bool* calibrationDone);

/*
 * Returns the adjustment points and filter configurations needed to sweep the 
 * instrument for adjustment.
 */
niVB_Status NIVB_DECL niVB_FGEN_GetGainCalibrationAdjustmentPoints(
   niVB_FGENCal_InstrumentHandle instrumentHandle,
   bool* enableFilter,
   size_t enableFilterSize,
   size_t* enableFilterSizeOut,
   double* adjustmentPoint,
   size_t adjustmentPointSize,
   size_t* adjustmentPointSizeOut);

/*
 * Configures the instrument to output the values returned by FGEN Get 
 * Calibration Adjustment Points.
 */
niVB_Status NIVB_DECL niVB_FGEN_SetupGainCalibration(
   niVB_FGENCal_InstrumentHandle instrumentHandle,
   bool enableFilter,
   double adjustmentPoint);

/*
 * Stores a measured reference value to the instrument and associates that 
 * value with the adjustment point and filter values previously configured 
 * with FGEN Setup Gain Calibration. You must run FGEN Setup Gain Calibration 
 * prior to running this method.
 */
niVB_Status NIVB_DECL niVB_FGEN_AdjustGainCalibration(
   niVB_FGENCal_InstrumentHandle instrumentHandle,
   double referenceValue);

/*
 * Closes the calibration session, then resets the device.
 */
niVB_Status NIVB_DECL niVB_FGEN_CloseCalibration(
   niVB_FGENCal_InstrumentHandle instrumentHandleIn,
   niVB_CalibrationAction action);

/*
 * Establishes communication with the device. This method should be called 
 * once per session.
 */
niVB_Status NIVB_DECL niVB_MSO_Initialize(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   bool reset,
   niVB_MSO_InstrumentHandle* instrumentHandle);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_InitializeW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   bool reset,
   niVB_MSO_InstrumentHandle* instrumentHandle);
#endif

/*
 * Automatically configures the instrument.
 */
niVB_Status NIVB_DECL niVB_MSO_Autosetup(
   niVB_MSO_InstrumentHandle instrumentHandle);

/*
 * Configures the settings of the specified analog channel.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureAnalogChannel(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* channel,
   bool enableChannel,
   double verticalRange,
   double verticalOffset,
   niVB_MSO_ProbeAttenuation probeAttenuation,
   niVB_MSO_Coupling verticalCoupling);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ConfigureAnalogChannelW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   bool enableChannel,
   double verticalRange,
   double verticalOffset,
   niVB_MSO_ProbeAttenuation probeAttenuation,
   niVB_MSO_Coupling verticalCoupling);
#endif

/*
 * Configures the properties that control the electrical characteristics of 
 * the specified channel.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureAnalogChannelCharacteristics(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* channel,
   niVB_MSO_InputImpedance inputImpedance,
   double bandwidthLimit);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ConfigureAnalogChannelCharacteristicsW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   niVB_MSO_InputImpedance inputImpedance,
   double bandwidthLimit);
#endif

/*
 * Enables or disables the specified digital channels.
 */
niVB_Status NIVB_DECL niVB_MSO_EnableDigitalChannels(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* channel,
   bool enableChannel);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_EnableDigitalChannelsW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   bool enableChannel);
#endif

/*
 * Configures the threshold level for logic analyzer lines.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureDigitalThreshold(
   niVB_MSO_InstrumentHandle instrumentHandle,
   double threshold);

/*
 * Configures the basic timing settings of the instrument.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureTiming(
   niVB_MSO_InstrumentHandle instrumentHandle,
   double sampleRate,
   double acquisitionTime,
   double pretriggerTime,
   niVB_MSO_SamplingMode samplingMode);

/*
 * Configures the rate and buffer settings of the logic analyzer. This method 
 * allows for more advanced configuration options than MSO Configure Timing.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureAdvancedDigitalTiming(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_DigitalSampleRateControl digitalSampleRateControl,
   double digitalSampleRate,
   niVB_MSO_BufferControl bufferControl,
   double bufferPretriggerPercent);

/*
 * Configures how to clock data on the logic analyzer channels that are 
 * enabled.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureStateMode(
   niVB_MSO_InstrumentHandle instrumentHandle,
   bool enable,
   const char* clockChannel,
   niVB_EdgeWithEither clockEdge);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ConfigureStateModeW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   bool enable,
   const wchar_t* clockChannel,
   niVB_EdgeWithEither clockEdge);
#endif

/*
 * Configures a trigger to immediately activate on the specified channels 
 * after the pretrigger time has expired.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureImmediateTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle);

/*
 * Configures a trigger to activate on the specified source when the analog 
 * edge reaches the specified levels.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureAnalogEdgeTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* triggerSource,
   niVB_EdgeWithEither triggerSlope,
   double triggerLevel,
   double triggerHysteresis,
   niVB_MSO_TriggerInstance triggerInstance);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ConfigureAnalogEdgeTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* triggerSource,
   niVB_EdgeWithEither triggerSlope,
   double triggerLevel,
   double triggerHysteresis,
   niVB_MSO_TriggerInstance triggerInstance);
#endif

/*
 * Configures a trigger to activate on the specified source when the digital 
 * edge reaches the specified levels.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureDigitalEdgeTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* triggerSource,
   niVB_EdgeWithEither triggerSlope,
   niVB_MSO_TriggerInstance triggerInstance);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ConfigureDigitalEdgeTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* triggerSource,
   niVB_EdgeWithEither triggerSlope,
   niVB_MSO_TriggerInstance triggerInstance);
#endif

/*
 * Configures a trigger to activate on the specified channels when a digital 
 * pattern is matched. A trigger is produced when every level (high/low) 
 * requirement specified in Trigger Pattern is met, and when at least one 
 * toggling (toggle/fall/rise) requirement is met. If no toggling requirements 
 * are set, then only the level requirements must be met to produce a trigger.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureDigitalPatternTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* triggerSource,
   const char* triggerPattern,
   niVB_MSO_TriggerInstance triggerInstance);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ConfigureDigitalPatternTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* triggerSource,
   const wchar_t* triggerPattern,
   niVB_MSO_TriggerInstance triggerInstance);
#endif

/*
 * Configures a trigger to activate on the specified channels when a digital 
 * glitch occurs. A glitch occurs when a channel in Trigger Source toggles 
 * between two edges of the sample clock, but has the same state for both 
 * samples. This may happen when the sampling rate is less than 1 GHz.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureDigitalGlitchTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* triggerSource,
   niVB_MSO_TriggerInstance triggerInstance);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ConfigureDigitalGlitchTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* triggerSource,
   niVB_MSO_TriggerInstance triggerInstance);
#endif

/*
 * Configures a trigger to activate on the specified source when the analog 
 * edge reaches the specified levels within a specified window of time.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureAnalogPulseWidthTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* triggerSource,
   niVB_MSO_TriggerPolarity triggerPolarity,
   double triggerLevel,
   niVB_MSO_ComparisonMode comparisonMode,
   double lowerLimit,
   double upperLimit,
   niVB_MSO_TriggerInstance triggerInstance);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ConfigureAnalogPulseWidthTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* triggerSource,
   niVB_MSO_TriggerPolarity triggerPolarity,
   double triggerLevel,
   niVB_MSO_ComparisonMode comparisonMode,
   double lowerLimit,
   double upperLimit,
   niVB_MSO_TriggerInstance triggerInstance);
#endif

/*
 * Configures a trigger to activate on the specified source when the digital 
 * edge reaches the specified levels within a specified window of time.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureDigitalPulseWidthTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* triggerSource,
   niVB_MSO_TriggerPolarity triggerPolarity,
   niVB_MSO_ComparisonMode comparisonMode,
   double lowerLimit,
   double upperLimit,
   niVB_MSO_TriggerInstance triggerInstance);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ConfigureDigitalPulseWidthTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* triggerSource,
   niVB_MSO_TriggerPolarity triggerPolarity,
   niVB_MSO_ComparisonMode comparisonMode,
   double lowerLimit,
   double upperLimit,
   niVB_MSO_TriggerInstance triggerInstance);
#endif

/*
 * Configures the amount of time to wait after a trigger condition is met 
 * before triggering.
 */
niVB_Status NIVB_DECL niVB_MSO_ConfigureTriggerDelay(
   niVB_MSO_InstrumentHandle instrumentHandle,
   double triggerDelay);

/*
 * Indicates the vertical configuration of the specified channel.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryAnalogChannel(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* channel,
   bool* channelEnabled,
   double* verticalRange,
   double* verticalOffset,
   niVB_MSO_ProbeAttenuation* probeAttenuation,
   niVB_MSO_Coupling* verticalCoupling);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryAnalogChannelW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   bool* channelEnabled,
   double* verticalRange,
   double* verticalOffset,
   niVB_MSO_ProbeAttenuation* probeAttenuation,
   niVB_MSO_Coupling* verticalCoupling);
#endif

niVB_Status NIVB_DECL niVB_MSO_QueryEnabledAnalogChannels(
   niVB_MSO_InstrumentHandle instrumentHandle,
   char* channels,
   size_t channelsSize,
   size_t* channelsSizeOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryEnabledAnalogChannelsW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   wchar_t* channels,
   size_t channelsSize,
   size_t* channelsSizeOut);
#endif

/*
 * Indicates the properties that control the electrical characteristics of the 
 * specified channel. This method returns an error if too much power is 
 * applied to the channel.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryAnalogChannelCharacteristics(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* channel,
   niVB_MSO_InputImpedance* inputImpedance,
   double* bandwidthLimit);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryAnalogChannelCharacteristicsW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   niVB_MSO_InputImpedance* inputImpedance,
   double* bandwidthLimit);
#endif

/*
 * Indicates whether the specified digital channel is enabled.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalChannel(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* channel,
   bool* channelEnabled);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalChannelW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   bool* channelEnabled);
#endif

niVB_Status NIVB_DECL niVB_MSO_QueryEnabledDigitalChannels(
   niVB_MSO_InstrumentHandle instrumentHandle,
   char* channels,
   size_t channelsSize,
   size_t* channelsSizeOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryEnabledDigitalChannelsW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   wchar_t* channels,
   size_t channelsSize,
   size_t* channelsSizeOut);
#endif

/*
 * Indicates the threshold configuration of the logic analyzer channels.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalThreshold(
   niVB_MSO_InstrumentHandle instrumentHandle,
   double* threshold);

/*
 * Indicates the timing configuration of the MSO.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryTiming(
   niVB_MSO_InstrumentHandle instrumentHandle,
   double* sampleRate,
   double* acquisitionTime,
   double* pretriggerTime,
   niVB_MSO_SamplingMode* samplingMode);

/*
 * Indicates the buffer configuration of the logic analyzer.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryAdvancedDigitalTiming(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_DigitalSampleRateControl* digitalSampleRateControl,
   double* digitalSampleRate,
   niVB_MSO_BufferControl* bufferControl,
   double* bufferPretriggerPercent);

/*
 * Indicates the clock configuration of the logic analyzer.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryStateMode(
   niVB_MSO_InstrumentHandle instrumentHandle,
   bool* stateModeEnabled,
   char* clockChannel,
   size_t clockChannelSize,
   size_t* clockChannelSizeOut,
   niVB_EdgeWithEither* clockEdge);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryStateModeW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   bool* stateModeEnabled,
   wchar_t* clockChannel,
   size_t clockChannelSize,
   size_t* clockChannelSizeOut,
   niVB_EdgeWithEither* clockEdge);
#endif

/*
 * Indicates the trigger type of the specified instance.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryTriggerType(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   niVB_MSO_TriggerType* triggerType);

/*
 * Indicates the analog edge trigger configuration of the specified instance.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryAnalogEdgeTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   char* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut,
   niVB_EdgeWithEither* triggerSlope,
   double* triggerLevel,
   double* triggerHysteresis);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryAnalogEdgeTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   wchar_t* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut,
   niVB_EdgeWithEither* triggerSlope,
   double* triggerLevel,
   double* triggerHysteresis);
#endif

/*
 * Indicates the digital trigger configuration of the specified instance.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalEdgeTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   char* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut,
   niVB_EdgeWithEither* triggerSlope);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalEdgeTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   wchar_t* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut,
   niVB_EdgeWithEither* triggerSlope);
#endif

/*
 * Indicates the digital pattern trigger configuration of the specified 
 * instance. A trigger is produced when every level (high/low) requirement 
 * specified in Trigger Pattern is met, and when at least one toggling 
 * (toggle/fall/rise) requirement is met. If no toggling requirements are set, 
 * then only the level requirements must be met to produce a trigger.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalPatternTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   char* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut,
   char* triggerPattern,
   size_t triggerPatternSize,
   size_t* triggerPatternSizeOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalPatternTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   wchar_t* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut,
   wchar_t* triggerPattern,
   size_t triggerPatternSize,
   size_t* triggerPatternSizeOut);
#endif

/*
 * Indicates the digital glitch trigger configuration of the specified 
 * instance. A glitch occurs when a channel in Trigger Source toggles between 
 * two edges of the sample clock. This may happen when the sampling rate is 
 * less than 1 GHz.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalGlitchTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   char* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalGlitchTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   wchar_t* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut);
#endif

/*
 * Indicates the trigger delay setting of the MSO.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryTriggerDelay(
   niVB_MSO_InstrumentHandle instrumentHandle,
   double* triggerDelay);

/*
 * Indicates the analog pulse width trigger configuration of the specified 
 * instance.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryAnalogPulseWidthTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   char* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut,
   niVB_MSO_TriggerPolarity* triggerPolarity,
   double* triggerLevel,
   niVB_MSO_ComparisonMode* comparisonMode,
   double* lowerLimit,
   double* upperLimit);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryAnalogPulseWidthTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   wchar_t* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut,
   niVB_MSO_TriggerPolarity* triggerPolarity,
   double* triggerLevel,
   niVB_MSO_ComparisonMode* comparisonMode,
   double* lowerLimit,
   double* upperLimit);
#endif

/*
 * Indicates the digital pulse width trigger configuration of the specified 
 * instance.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalPulseWidthTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   char* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut,
   niVB_MSO_TriggerPolarity* triggerPolarity,
   niVB_MSO_ComparisonMode* comparisonMode,
   double* lowerLimit,
   double* upperLimit);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_QueryDigitalPulseWidthTriggerW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_TriggerInstance triggerInstance,
   wchar_t* triggerSource,
   size_t triggerSourceSize,
   size_t* triggerSourceSizeOut,
   niVB_MSO_TriggerPolarity* triggerPolarity,
   niVB_MSO_ComparisonMode* comparisonMode,
   double* lowerLimit,
   double* upperLimit);
#endif

/*
 * Returns the status of a completed or ongoing acquisition.
 */
niVB_Status NIVB_DECL niVB_MSO_QueryAcquisitionStatus(
   niVB_MSO_InstrumentHandle instrumentHandle,
   niVB_MSO_AcquisitionStatus* status);

/*
 * Transitions the acquisition from the Stopped state to the Running state. If 
 * the current state is Triggered, the acquisition is first transitioned to 
 * the Stopped state before transitioning to the Running state. This method 
 * returns an error if too much power is applied to any enabled channel.
 */
niVB_Status NIVB_DECL niVB_MSO_Run(
   niVB_MSO_InstrumentHandle instrumentHandle,
   bool autoTrigger);

/*
 * Causes a software-timed trigger to occur after the pretrigger time has 
 * expired.
 */
niVB_Status NIVB_DECL niVB_MSO_ForceTrigger(
   niVB_MSO_InstrumentHandle instrumentHandle);

/*
 * Transitions the acquisition from either the Triggered or Running state to 
 * the Stopped state.
 */
niVB_Status NIVB_DECL niVB_MSO_Stop(
   niVB_MSO_InstrumentHandle instrumentHandle);

/*
 * Transfers data from the instrument as long as the acquisition state is 
 * Acquisition Complete. If the state is either Running or Triggered, this 
 * method will wait until the state transitions to Acquisition Complete. If 
 * the state is Stopped, this method returns an error.
 */
niVB_Status NIVB_DECL niVB_MSO_ReadAnalog(
   niVB_MSO_InstrumentHandle instrumentHandle,
   double* data,
   size_t dataSize,
   size_t* dataSizeOut,
   size_t* dataStride,
   niVB_Timestamp* initialTimestamp,
   niVB_Timestamp* triggerTimestamp,
   niVB_MSO_TriggerReason* triggerReason);

/*
 * Transfers data from the instrument as long as the acquisition state is 
 * Acquisition Complete. If the state is either Running or Triggered, this 
 * method will wait until the state transitions to Acquisition Complete. If 
 * the state is Stopped, this method returns an error.
 */
niVB_Status NIVB_DECL niVB_MSO_ReadDigitalU64(
   niVB_MSO_InstrumentHandle instrumentHandle,
   uint64_t* data,
   size_t dataSize,
   size_t* dataSizeOut,
   uint32_t* sampleTimestamps,
   size_t sampleTimestampsSize,
   size_t* sampleTimestampsSizeOut,
   niVB_Timestamp* initialTimestamp,
   niVB_Timestamp* triggerTimestamp,
   niVB_MSO_TriggerReason* triggerReason);

/*
 * Transfers data from the instrument as long as the acquisition state is 
 * Acquisition Complete. If the state is either Running or Triggered, this 
 * method will wait until the state transitions to Acquisition Complete. If 
 * the state is Stopped, this method returns an error.
 */
niVB_Status NIVB_DECL niVB_MSO_ReadAnalogDigitalU64(
   niVB_MSO_InstrumentHandle instrumentHandle,
   double* analogData,
   size_t analogDataSize,
   size_t* analogDataSizeOut,
   size_t* analogDataStride,
   niVB_Timestamp* analogInitialTimestamp,
   uint64_t* digitalData,
   size_t digitalDataSize,
   size_t* digitalDataSizeOut,
   uint32_t* digitalSampleTimestamps,
   size_t digitalSampleTimestampsSize,
   size_t* digitalSampleTimestampsSizeOut,
   niVB_Timestamp* digitalInitialTimestamp,
   niVB_Timestamp* triggerTimestamp,
   niVB_MSO_TriggerReason* triggerReason);

/*
 * Resets the session configuration to default values, and resets the device 
 * and driver software to a known state.
 */
niVB_Status NIVB_DECL niVB_MSO_ResetInstrument(
   niVB_MSO_InstrumentHandle instrumentHandle);

/*
 * Exports a configuration file for use with the MSO.
 */
niVB_Status NIVB_DECL niVB_MSO_ExportConfiguration(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ExportConfigurationW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Imports a configuration file for use with the MSO. You can import PNG files 
 * exported from the VirtualBench Application or files created from MSO Export 
 * Configuration.
 */
niVB_Status NIVB_DECL niVB_MSO_ImportConfiguration(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_ImportConfigurationW(
   niVB_MSO_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Removes the session and deallocates any resources acquired during the 
 * session. If output is enabled on any channels, they remain in their current 
 * state.
 */
niVB_Status NIVB_DECL niVB_MSO_Close(
   niVB_MSO_InstrumentHandle instrumentHandleIn);

/*
 * Returns instrument information from the last successful calibration 
 * adjustment.
 */
niVB_Status NIVB_DECL niVB_MSO_GetCalibrationAdjustmentInformation(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   niVB_Timestamp* adjustmentDate,
   double* adjustmentTemperature);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_GetCalibrationAdjustmentInformationW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   niVB_Timestamp* adjustmentDate,
   double* adjustmentTemperature);
#endif

/*
 * Opens a calibration session with the instrument. The instrument is reset 
 * upon successful completion of this method. This method returns an error if 
 * the instrument is reserved or if Password is incorrect.
 */
niVB_Status NIVB_DECL niVB_MSO_InitializeCalibration(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   const char* password,
   niVB_MSOCal_InstrumentHandle* instrumentHandle);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_InitializeCalibrationW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   const wchar_t* password,
   niVB_MSOCal_InstrumentHandle* instrumentHandle);
#endif

/*
 * Grounds the input to the specified Channel. You must run this method as the 
 * first step of adjustment.
 */
niVB_Status NIVB_DECL niVB_MSO_AdjustOffsetCalibration(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   const char* channel);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_AdjustOffsetCalibrationW(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   const wchar_t* channel);
#endif

/*
 * Returns the configuration values necessary for MSO Adjust Compensator 
 * Attenuation. Each element of the Range, Amplitude, and Frequency arrays 
 * correspond to each other.
 */
niVB_Status NIVB_DECL niVB_MSO_GetCompensatorAttenuationCalibrationAdjustmentPoints(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   double* range,
   size_t rangeSize,
   size_t* rangeSizeOut,
   double* amplitude,
   size_t amplitudeSize,
   size_t* amplitudeSizeOut,
   double* frequency,
   size_t frequencySize,
   size_t* frequencySizeOut);

/*
 * Adjusts the compensator attenuation using the values from MSO Get 
 * Compensator Attenuation Adjustment Points.
 */
niVB_Status NIVB_DECL niVB_MSO_AdjustCompensatorAttenuationCalibration(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   const char* channel,
   double range,
   double amplitude,
   double frequency);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_AdjustCompensatorAttenuationCalibrationW(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double range,
   double amplitude,
   double frequency);
#endif

/*
 * Returns the adjustment points and range values needed to sweep the 
 * instrument for adjustment.
 */
niVB_Status NIVB_DECL niVB_MSO_GetRangeCalibrationAdjustmentPoints(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   double* range,
   size_t rangeSize,
   size_t* rangeSizeOut,
   double* adjustmentPoint,
   size_t adjustmentPointSize,
   size_t* adjustmentPointSizeOut);

/*
 * Adjusts the range calibration using the values returned by MSO Get Range 
 * Adjustment Points. This method returns an error if it is run before MSO 
 * Adjust Compensator Attenuation.
 */
niVB_Status NIVB_DECL niVB_MSO_AdjustRangeCalibration(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   const char* channel,
   double range,
   double adjustmentPoint);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_AdjustRangeCalibrationW(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double range,
   double adjustmentPoint);
#endif

/*
 * Returns the adjustment point and range values necessary for MSO Adjust 
 * Offset DAC Calibration. Each element of the Range and Adjustment Point 
 * arrays correspond to each other.
 */
niVB_Status NIVB_DECL niVB_MSO_GetOffsetDACCalibrationAdjustmentPoints(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   double* range,
   size_t rangeSize,
   size_t* rangeSizeOut,
   double* adjustmentPoint,
   size_t adjustmentPointSize,
   size_t* adjustmentPointSizeOut);

/*
 * Configures the instrument on the specified channel using the values 
 * obtained by MSO Get Offset DAC Calibration Adjustment Points. This method 
 * returns an error if it is run before MSO Adjust Offset Calibration.
 */
niVB_Status NIVB_DECL niVB_MSO_AdjustOffsetDACCalibration(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   const char* channel,
   double range,
   double adjustmentPoint);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_MSO_AdjustOffsetDACCalibrationW(
   niVB_MSOCal_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double range,
   double adjustmentPoint);
#endif

/*
 * Closes the calibration session, then resets the device.
 */
niVB_Status NIVB_DECL niVB_MSO_CloseCalibration(
   niVB_MSOCal_InstrumentHandle instrumentHandleIn,
   niVB_CalibrationAction action);

/*
 * Establishes communication with the device. This method should be called 
 * once per session.
 */
niVB_Status NIVB_DECL niVB_DMM_Initialize(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   bool reset,
   niVB_DMM_InstrumentHandle* instrumentHandle);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_DMM_InitializeW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   bool reset,
   niVB_DMM_InstrumentHandle* instrumentHandle);
#endif

/*
 * Configures the instrument to take a DMM measurement.
 */
niVB_Status NIVB_DECL niVB_DMM_ConfigureMeasurement(
   niVB_DMM_InstrumentHandle instrumentHandle,
   niVB_DMM_Function function,
   bool autoRange,
   double manualRange);

/*
 * Configures DC voltage measurement specifications for the DMM.
 */
niVB_Status NIVB_DECL niVB_DMM_ConfigureDCVoltage(
   niVB_DMM_InstrumentHandle instrumentHandle,
   niVB_DMM_InputResistance inputResistance);

/*
 * Configures DC current measurement specifications for the DMM.
 */
niVB_Status NIVB_DECL niVB_DMM_ConfigureDCCurrent(
   niVB_DMM_InstrumentHandle instrumentHandle,
   niVB_DMM_CurrentTerminal autoRangeTerminal);

/*
 * Configures AC current measurement specifications for the DMM.
 */
niVB_Status NIVB_DECL niVB_DMM_ConfigureACCurrent(
   niVB_DMM_InstrumentHandle instrumentHandle,
   niVB_DMM_CurrentTerminal autoRangeTerminal);

/*
 * Indicates the measurement settings for the instrument.
 */
niVB_Status NIVB_DECL niVB_DMM_QueryMeasurement(
   niVB_DMM_InstrumentHandle instrumentHandle,
   niVB_DMM_Function* function,
   bool* autoRange,
   double* range);

/*
 * Indicates the settings for a DC voltage measurement.
 */
niVB_Status NIVB_DECL niVB_DMM_QueryDCVoltage(
   niVB_DMM_InstrumentHandle instrumentHandle,
   niVB_DMM_InputResistance* inputResistance);

/*
 * Indicates the settings for a DC current measurement.
 */
niVB_Status NIVB_DECL niVB_DMM_QueryDCCurrent(
   niVB_DMM_InstrumentHandle instrumentHandle,
   niVB_DMM_CurrentTerminal* autoRangeTerminal);

/*
 * Indicates the settings for a AC current measurement.
 */
niVB_Status NIVB_DECL niVB_DMM_QueryACCurrent(
   niVB_DMM_InstrumentHandle instrumentHandle,
   niVB_DMM_CurrentTerminal* autoRangeTerminal);

/*
 * Reads the data from the instrument.
 */
niVB_Status NIVB_DECL niVB_DMM_Read(
   niVB_DMM_InstrumentHandle instrumentHandle,
   double* measurement);

/*
 * Resets the session configuration to default values, and resets the device 
 * and driver software to a known state.
 */
niVB_Status NIVB_DECL niVB_DMM_ResetInstrument(
   niVB_DMM_InstrumentHandle instrumentHandle);

/*
 * Exports a configuration file for use with the DMM.
 */
niVB_Status NIVB_DECL niVB_DMM_ExportConfiguration(
   niVB_DMM_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_DMM_ExportConfigurationW(
   niVB_DMM_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Imports a configuration file for use with the DMM. You can import PNG files 
 * exported from the VirtualBench Application or files created from DMM Export 
 * Configuration.
 */
niVB_Status NIVB_DECL niVB_DMM_ImportConfiguration(
   niVB_DMM_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_DMM_ImportConfigurationW(
   niVB_DMM_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Stops the session and deallocates any resources acquired during the 
 * session.
 */
niVB_Status NIVB_DECL niVB_DMM_Close(
   niVB_DMM_InstrumentHandle instrumentHandleIn);

/*
 * Returns instrument information from the last successful calibration 
 * adjustment.
 */
niVB_Status NIVB_DECL niVB_DMM_GetCalibrationAdjustmentInformation(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   niVB_Timestamp* adjustmentDate,
   double* adjustmentTemperature);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_DMM_GetCalibrationAdjustmentInformationW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   niVB_Timestamp* adjustmentDate,
   double* adjustmentTemperature);
#endif

/*
 * Opens a calibration session with the instrument. The instrument is reset 
 * upon successful completion of this method. This method returns an error if 
 * the instrument is reserved or if Password is incorrect.
 */
niVB_Status NIVB_DECL niVB_DMM_InitializeCalibration(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   const char* password,
   niVB_DMMCal_InstrumentHandle* instrumentHandle);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_DMM_InitializeCalibrationW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   const wchar_t* password,
   niVB_DMMCal_InstrumentHandle* instrumentHandle);
#endif

/*
 * Returns the adjustment point and range configurations needed to sweep the 
 * DMM for DC voltage adjustment.
 */
niVB_Status NIVB_DECL niVB_DMM_GetDCVoltageCalibrationAdjustmentPoints(
   niVB_DMMCal_InstrumentHandle instrumentHandle,
   double* range,
   size_t rangeSize,
   size_t* rangeSizeOut,
   double* adjustmentPoint,
   size_t adjustmentPointSize,
   size_t* adjustmentPointSizeOut);

/*
 * Measures and stores the reference value for the specified Adjustment Point 
 * and Range with the DMM. Specify these values in the order returned by DMM 
 * Get DC Voltage Calibration Adjustment Points.
 */
niVB_Status NIVB_DECL niVB_DMM_AdjustDCVoltageCalibration(
   niVB_DMMCal_InstrumentHandle instrumentHandle,
   double range,
   double adjustmentPoint);

/*
 * Returns the adjustment point and range configurations needed to sweep the 
 * DMM for AC voltage adjustment.
 */
niVB_Status NIVB_DECL niVB_DMM_GetACVoltageCalibrationAdjustmentPoints(
   niVB_DMMCal_InstrumentHandle instrumentHandle,
   double* range,
   size_t rangeSize,
   size_t* rangeSizeOut,
   double* adjustmentPoint,
   size_t adjustmentPointSize,
   size_t* adjustmentPointSizeOut,
   double* frequency,
   size_t frequencySize,
   size_t* frequencySizeOut);

/*
 * Measures and stores the reference value for the specified Adjustment Point, 
 * Range, and Frequency with the DMM. Specify these values in the order 
 * returned by DMM Get AC Voltage Calibration Adjustment Points. This method 
 * returns an error if it is run before DMM Adjust Resistance Calibration.
 */
niVB_Status NIVB_DECL niVB_DMM_AdjustACVoltageCalibration(
   niVB_DMMCal_InstrumentHandle instrumentHandle,
   double range,
   double adjustmentPoint,
   double frequency);

/*
 * Returns the adjustment point and range configurations needed to sweep the 
 * DMM for current adjustment.
 */
niVB_Status NIVB_DECL niVB_DMM_GetCurrentCalibrationAdjustmentPoints(
   niVB_DMMCal_InstrumentHandle instrumentHandle,
   double* range,
   size_t rangeSize,
   size_t* rangeSizeOut,
   double* adjustmentPoint,
   size_t adjustmentPointSize,
   size_t* adjustmentPointSizeOut);

/*
 * Measures and stores the reference value for the specified Adjustment Point 
 * and Range with the DMM. Specify these values in the order returned by DMM 
 * Get Current Calibration Adjustment Points. This method returns an error if 
 * it is run before DMM Adjust AC Voltage Calibration.
 */
niVB_Status NIVB_DECL niVB_DMM_AdjustCurrentCalibration(
   niVB_DMMCal_InstrumentHandle instrumentHandle,
   double range,
   double adjustmentPoint);

/*
 * Returns the adjustment point and range configurations needed to sweep the 
 * DMM for resistance adjustment.
 */
niVB_Status NIVB_DECL niVB_DMM_GetResistanceCalibrationAdjustmentPoints(
   niVB_DMMCal_InstrumentHandle instrumentHandle,
   double* range,
   size_t rangeSize,
   size_t* rangeSizeOut,
   double* adjustmentPoint,
   size_t adjustmentPointSize,
   size_t* adjustmentPointSizeOut);

/*
 * Configures the DMM to use the specified resistance range and places the DMM 
 * in resistance mode.
 */
niVB_Status NIVB_DECL niVB_DMM_SetupResistanceCalibration(
   niVB_DMMCal_InstrumentHandle instrumentHandle,
   double range);

/*
 * Measures and stores the reference value for the specified Adjustment Point 
 * with the DMM. Specify these values in the order returned by DMM Get 
 * Resistance Calibration Adjustment Points. This method returns an error if 
 * it is run before DMM Setup Resistance Calibration.
 */
niVB_Status NIVB_DECL niVB_DMM_AdjustResistanceCalibration(
   niVB_DMMCal_InstrumentHandle instrumentHandle,
   double adjustmentPoint);

/*
 * Closes the calibration session, then resets the device.
 */
niVB_Status NIVB_DECL niVB_DMM_CloseCalibration(
   niVB_DMMCal_InstrumentHandle instrumentHandleIn,
   niVB_CalibrationAction action);

/*
 * Establishes communication with the device. This method should be called 
 * once per session.
 */
niVB_Status NIVB_DECL niVB_PS_Initialize(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   bool reset,
   niVB_PS_InstrumentHandle* instrumentHandle);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_InitializeW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   bool reset,
   niVB_PS_InstrumentHandle* instrumentHandle);
#endif

/*
 * Configures a voltage output on the specified channel. This method should be 
 * called once for every channel you want to configure to output voltage.
 */
niVB_Status NIVB_DECL niVB_PS_ConfigureVoltageOutput(
   niVB_PS_InstrumentHandle instrumentHandle,
   const char* channel,
   double voltageLevel,
   double currentLimit);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_ConfigureVoltageOutputW(
   niVB_PS_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double voltageLevel,
   double currentLimit);
#endif

/*
 * Configures a current output on the specified channel. This method should be 
 * called once for every channel you want to configure to output current.
 */
niVB_Status NIVB_DECL niVB_PS_ConfigureCurrentOutput(
   niVB_PS_InstrumentHandle instrumentHandle,
   const char* channel,
   double currentLevel,
   double voltageLimit);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_ConfigureCurrentOutputW(
   niVB_PS_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double currentLevel,
   double voltageLimit);
#endif

/*
 * Enables or disables tracking between the positive and negative 25V 
 * channels. If enabled, any configuration change on the positive 25V channel 
 * is mirrored to the negative 25V channel, and any writes to the negative 25V 
 * channel are ignored.
 */
niVB_Status NIVB_DECL niVB_PS_EnableTracking(
   niVB_PS_InstrumentHandle instrumentHandle,
   bool enableTracking);

/*
 * Enables or disables all outputs on all channels of the instrument.
 */
niVB_Status NIVB_DECL niVB_PS_EnableAllOutputs(
   niVB_PS_InstrumentHandle instrumentHandle,
   bool enableOutputs);

/*
 * Indicates the voltage output settings on the specified channel.
 */
niVB_Status NIVB_DECL niVB_PS_QueryVoltageOutput(
   niVB_PS_InstrumentHandle instrumentHandle,
   const char* channel,
   double* voltageLevel,
   double* currentLimit);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_QueryVoltageOutputW(
   niVB_PS_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double* voltageLevel,
   double* currentLimit);
#endif

/*
 * Indicates the current output settings on the specified channel.
 */
niVB_Status NIVB_DECL niVB_PS_QueryCurrentOutput(
   niVB_PS_InstrumentHandle instrumentHandle,
   const char* channel,
   double* currentLevel,
   double* voltageLimit);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_QueryCurrentOutputW(
   niVB_PS_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double* currentLevel,
   double* voltageLimit);
#endif

/*
 * Indicates whether the outputs are enabled for the instrument.
 */
niVB_Status NIVB_DECL niVB_PS_QueryOutputsEnabled(
   niVB_PS_InstrumentHandle instrumentHandle,
   bool* outputsEnabled);

/*
 * Indicates whether voltage tracking is enabled on the instrument.
 */
niVB_Status NIVB_DECL niVB_PS_QueryTracking(
   niVB_PS_InstrumentHandle instrumentHandle,
   bool* trackingEnabled);

/*
 * Reads the voltage and current levels of the specified channel.
 */
niVB_Status NIVB_DECL niVB_PS_ReadOutput(
   niVB_PS_InstrumentHandle instrumentHandle,
   const char* channel,
   double* actualVoltageLevel,
   double* actualCurrentLevel,
   niVB_PS_State* state);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_ReadOutputW(
   niVB_PS_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double* actualVoltageLevel,
   double* actualCurrentLevel,
   niVB_PS_State* state);
#endif

/*
 * Resets the session configuration to default values, and resets the device 
 * and driver software to a known state.
 */
niVB_Status NIVB_DECL niVB_PS_ResetInstrument(
   niVB_PS_InstrumentHandle instrumentHandle);

/*
 * Exports a configuration file for use with the power supply.
 */
niVB_Status NIVB_DECL niVB_PS_ExportConfiguration(
   niVB_PS_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_ExportConfigurationW(
   niVB_PS_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Imports a configuration file for use with the power supply. You can import 
 * PNG files exported from the VirtualBench Application or files created from 
 * PS Export Configuration.
 */
niVB_Status NIVB_DECL niVB_PS_ImportConfiguration(
   niVB_PS_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_ImportConfigurationW(
   niVB_PS_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Stops the session and deallocates any resources acquired during the 
 * session. If output is enabled on any channels, they remain in their current 
 * state and continue to output data.
 */
niVB_Status NIVB_DECL niVB_PS_Close(
   niVB_PS_InstrumentHandle instrumentHandleIn);

/*
 * Returns instrument information from the last successful calibration 
 * adjustment.
 */
niVB_Status NIVB_DECL niVB_PS_GetCalibrationAdjustmentInformation(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   niVB_Timestamp* adjustmentDate,
   double* adjustmentTemperature);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_GetCalibrationAdjustmentInformationW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   niVB_Timestamp* adjustmentDate,
   double* adjustmentTemperature);
#endif

/*
 * Opens a calibration session with the instrument. The instrument is reset 
 * upon successful completion of this method. This method returns an error if 
 * the instrument is reserved or if Password is incorrect.
 */
niVB_Status NIVB_DECL niVB_PS_InitializeCalibration(
   niVB_LibraryHandle libraryHandle,
   const char* deviceName,
   niVB_PS_CalType calType,
   const char* password,
   niVB_PSCal_InstrumentHandle* instrumentHandleOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_InitializeCalibrationW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* deviceName,
   niVB_PS_CalType calType,
   const wchar_t* password,
   niVB_PSCal_InstrumentHandle* instrumentHandleOut);
#endif

/*
 * Returns the adjustment points needed to sweep the instrument for adjustment 
 * on the specified Channel.
 */
niVB_Status NIVB_DECL niVB_PS_GetAdjustmentPoints(
   niVB_PSCal_InstrumentHandle instrumentHandle,
   const char* channel,
   double* adjustmentPoints,
   size_t adjustmentPointsSize,
   size_t* adjustmentPointsSizeOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_GetAdjustmentPointsW(
   niVB_PSCal_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double* adjustmentPoints,
   size_t adjustmentPointsSize,
   size_t* adjustmentPointsSizeOut);
#endif

/*
 * Sets the calibration adjustment point for the specified Channel.
 */
niVB_Status NIVB_DECL niVB_PS_SetAdjustmentPoint(
   niVB_PSCal_InstrumentHandle instrumentHandle,
   const char* channel,
   double adjustmentPoint);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_SetAdjustmentPointW(
   niVB_PSCal_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double adjustmentPoint);
#endif

/*
 * Measures the adjustment points for the specified Channel given a measured 
 * Reference Value.
 */
niVB_Status NIVB_DECL niVB_PS_MeasureAdjustmentPoint(
   niVB_PSCal_InstrumentHandle instrumentHandle,
   const char* channel,
   double referenceValue);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_PS_MeasureAdjustmentPointW(
   niVB_PSCal_InstrumentHandle instrumentHandle,
   const wchar_t* channel,
   double referenceValue);
#endif

/*
 * Closes the calibration session, then resets the device.
 */
niVB_Status NIVB_DECL niVB_PS_CloseCalibration(
   niVB_PSCal_InstrumentHandle instrumentHandleIn,
   niVB_CalibrationAction action);

/*
 * Creates and returns a new VirtualBench SPI session on the SPI engine for 
 * the device. The session is used in all subsequent VirtualBench SPI method 
 * calls. This method should be called once per session.
 */
niVB_Status NIVB_DECL niVB_SPI_Initialize(
   niVB_LibraryHandle libraryHandle,
   const char* bus,
   bool reset,
   niVB_SPI_InstrumentHandle* instrumentHandle);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_SPI_InitializeW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* bus,
   bool reset,
   niVB_SPI_InstrumentHandle* instrumentHandle);
#endif

/*
 * Configures the basic parameters of the SPI engine.
 */
niVB_Status NIVB_DECL niVB_SPI_ConfigureBus(
   niVB_SPI_InstrumentHandle instrumentHandle,
   double clockRate,
   niVB_Polarity clockPolarity,
   niVB_ClockPhase clockPhase,
   niVB_Polarity chipSelectPolarity);

/*
 * Indicates the current basic configuration of the SPI engine.
 */
niVB_Status NIVB_DECL niVB_SPI_QueryBusConfiguration(
   niVB_SPI_InstrumentHandle instrumentHandle,
   double* clockRate,
   niVB_Polarity* clockPolarity,
   niVB_ClockPhase* clockPhase,
   niVB_Polarity* chipSelectPolarity);

/*
 * Completes a transaction on the bus by writing the provided data to MOSI and 
 * returning the data read on MISO.
 */
niVB_Status NIVB_DECL niVB_SPI_WriteRead(
   niVB_SPI_InstrumentHandle instrumentHandle,
   const uint8_t* writeData,
   size_t writeDataSize,
   int32_t bytesPerFrame,
   uint8_t* readData,
   size_t readDataSize);

/*
 * Resets the session configuration to default values, and resets the device 
 * and driver software to a known state.
 */
niVB_Status NIVB_DECL niVB_SPI_ResetInstrument(
   niVB_SPI_InstrumentHandle instrumentHandle);

/*
 * Exports the current configuration of the instrument to a file.
 */
niVB_Status NIVB_DECL niVB_SPI_ExportConfiguration(
   niVB_SPI_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_SPI_ExportConfigurationW(
   niVB_SPI_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Imports a configuration file for use with the SPI engine. You can import 
 * PNG files exported from the VirtualBench Application or files created from 
 * SPI Export Configuration.
 */
niVB_Status NIVB_DECL niVB_SPI_ImportConfiguration(
   niVB_SPI_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_SPI_ImportConfigurationW(
   niVB_SPI_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Closes the session specified in Instrument Handle In.
 */
niVB_Status NIVB_DECL niVB_SPI_Close(
   niVB_SPI_InstrumentHandle instrumentHandleIn);

/*
 * Creates and returns a new VirtualBench I2C session on the I2C engine for 
 * the device. The session is used in all subsequent VirtualBench I2C method 
 * calls. This method should be called once per session.
 */
niVB_Status NIVB_DECL niVB_I2C_Initialize(
   niVB_LibraryHandle libraryHandle,
   const char* bus,
   bool reset,
   niVB_I2C_InstrumentHandle* instrumentHandleOut);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_I2C_InitializeW(
   niVB_LibraryHandle libraryHandle,
   const wchar_t* bus,
   bool reset,
   niVB_I2C_InstrumentHandle* instrumentHandleOut);
#endif

/*
 * Configures the basic parameters of the I2C engine.
 */
niVB_Status NIVB_DECL niVB_I2C_ConfigureBus(
   niVB_I2C_InstrumentHandle instrumentHandle,
   niVB_I2C_ClockRate clockRate,
   uint16_t address,
   niVB_I2C_AddressSize addressSize,
   bool enablePullUps);

/*
 * Indicates the current basic configuration of the I2C engine.
 */
niVB_Status NIVB_DECL niVB_I2C_QueryBusConfiguration(
   niVB_I2C_InstrumentHandle instrumentHandle,
   niVB_I2C_ClockRate* clockRate,
   uint16_t* address,
   niVB_I2C_AddressSize* addressSize,
   bool* pullUpsEnabled);

/*
 * Completes a read transaction on the bus.
 */
niVB_Status NIVB_DECL niVB_I2C_Read(
   niVB_I2C_InstrumentHandle instrumentHandle,
   double timeout,
   uint8_t* readData,
   size_t readDataSize);

/*
 * Completes a write transaction on the bus.
 */
niVB_Status NIVB_DECL niVB_I2C_Write(
   niVB_I2C_InstrumentHandle instrumentHandle,
   const uint8_t* writeData,
   size_t writeDataSize,
   double timeout,
   int32_t* numberOfBytesWritten);

/*
 * Performs a write followed by read (combined format) on an I2C slave device.
 */
niVB_Status NIVB_DECL niVB_I2C_WriteRead(
   niVB_I2C_InstrumentHandle instrumentHandle,
   const uint8_t* writeData,
   size_t writeDataSize,
   double timeout,
   int32_t* numberOfBytesWritten,
   uint8_t* readData,
   size_t readDataSize);

/*
 * Resets the session configuration to default values, and resets the device 
 * and driver software to a known state.
 */
niVB_Status NIVB_DECL niVB_I2C_ResetInstrument(
   niVB_I2C_InstrumentHandle instrumentHandle);

/*
 * Exports the current configuration of the instrument to a file.
 */
niVB_Status NIVB_DECL niVB_I2C_ExportConfiguration(
   niVB_I2C_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_I2C_ExportConfigurationW(
   niVB_I2C_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Imports a configuration file for use with the I2C engine. You can import 
 * PNG files exported from the VirtualBench Application or files created from 
 * I2C Export Configuration.
 */
niVB_Status NIVB_DECL niVB_I2C_ImportConfiguration(
   niVB_I2C_InstrumentHandle instrumentHandle,
   const char* configurationFileName);

#if defined(_WIN32) && !defined(_CVI_)
niVB_Status NIVB_DECL niVB_I2C_ImportConfigurationW(
   niVB_I2C_InstrumentHandle instrumentHandle,
   const wchar_t* configurationFileName);
#endif

/*
 * Closes the session specified in Instrument Handle In.
 */
niVB_Status NIVB_DECL niVB_I2C_Close(
   niVB_I2C_InstrumentHandle instrumentHandleIn);


#if defined(__cplusplus)
}
#endif

#endif