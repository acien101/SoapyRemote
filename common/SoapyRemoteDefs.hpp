// Copyright (c) 2015-2015 Josh Blum
// SPDX-License-Identifier: BSL-1.0

#pragma once
#include "SoapyRemoteConfig.hpp"

/***********************************************************************
 * Key-words and their defaults
 **********************************************************************/
//! Use this magic stop key in the server to prevent infinite loops
#define SOAPY_REMOTE_KWARG_STOP "soapy_remote_no_deeper"

//! Use this key prefix to pass in args that will become local
#define SOAPY_REMOTE_KWARG_PREFIX "remote:"

//! Stream args key to set the format on the remote server
#define SOAPY_REMOTE_KWARG_FORMAT (SOAPY_REMOTE_KWARG_PREFIX "format")

//! Stream args key to set the scalar for local float conversions
#define SOAPY_REMOTE_KWARG_SCALAR (SOAPY_REMOTE_KWARG_PREFIX "scalar")

//! Scale factor used for float conversions (on local machine)
#define SOAPY_REMOTE_DEFAULT_SCALING double(1 << 15)

//! Stream args key to set the buffer MTU bytes for network transfers
#define SOAPY_REMOTE_KWARG_MTU (SOAPY_REMOTE_KWARG_PREFIX "mtu")

/*!
 * Default stream transfer size (under network MTU).
 * Larger transfer sizes may not be supported in hardware
 * or may require tweaks to the system configuration.
 */
#define SOAPY_REMOTE_DEFAULT_ENDPOINT_MTU 1500

/*!
 * Stream args key to set the very large socket buffer size in bytes.
 * This sets the socket buffer size as well as the flow control window.
 */
#define SOAPY_REMOTE_KWARG_WINDOW (SOAPY_REMOTE_KWARG_PREFIX "window")

/*!
 * Default number of bytes in socket buffer.
 * Larger buffer sizes may not be supported or
 * may require tweaks to the system configuration.
 */
#ifdef __APPLE__ //large buffer size causes crash
#define SOAPY_REMOTE_DEFAULT_ENDPOINT_WINDOW (16*1024)
#else
#define SOAPY_REMOTE_DEFAULT_ENDPOINT_WINDOW (42*1024*1024)
#endif

/*!
 * Stream args key to set the priority of the forwarding threads.
 * Priority ranges: -1.0 (low), 0.0 (normal), and 1.0 (high)
 */
#define SOAPY_REMOTE_KWARG_PRIORITY (SOAPY_REMOTE_KWARG_PREFIX "priority")

//! Default thread priority is elevated for stream forwarding
#define SOAPY_REMOTE_DEFAULT_THREAD_PRIORITY double(0.5)

/***********************************************************************
 * Socket defaults
 **********************************************************************/

//! The default bind port for the remote server
#define SOAPY_REMOTE_DEFAULT_SERVICE "55132"

//! Use this timeout for every socket poll loop
#define SOAPY_REMOTE_SOCKET_TIMEOUT_US (50*1000) //50 ms

//! Backlog count for the server socket listen
#define SOAPY_REMOTE_LISTEN_BACKLOG 100

/*!
 * The number of buffers that can be acquired.
 * This is the number of buffers for the direct access API.
 * The socket is doing all of the actual buffering,
 * this just allows the user to get some flexibility
 * with the direct access API. Otherwise, most client code
 * will acquire and immediately release the same handle.
 */
#define SOAPY_REMOTE_ENDPOINT_NUM_BUFFS 8

/*!
 * The maximum buffer size for single socket call.
 * Use this in the packer and unpacker TCP code.
 * Larger buffers may crash some socket implementations.
 * The implementation should loop until completed.
 */
#define SOAPY_REMOTE_SOCKET_BUFFMAX 4096

/***********************************************************************
 * RPC structures and constants
 **********************************************************************/
//major, minor, patch when this was last updated
//bump the version number when changes are made
static const unsigned int SoapyRPCVersion = 0x000300;

enum SoapyRemoteTypes
{
    SOAPY_REMOTE_CHAR            = 0,
    SOAPY_REMOTE_BOOL            = 1,
    SOAPY_REMOTE_INT32           = 2,
    SOAPY_REMOTE_INT64           = 3,
    SOAPY_REMOTE_FLOAT64         = 4,
    SOAPY_REMOTE_COMPLEX128      = 5,
    SOAPY_REMOTE_STRING          = 6,
    SOAPY_REMOTE_RANGE           = 7,
    SOAPY_REMOTE_RANGE_LIST      = 8,
    SOAPY_REMOTE_STRING_LIST     = 9,
    SOAPY_REMOTE_FLOAT64_LIST    = 10,
    SOAPY_REMOTE_KWARGS          = 11,
    SOAPY_REMOTE_KWARGS_LIST     = 12,
    SOAPY_REMOTE_EXCEPTION       = 13,
    SOAPY_REMOTE_VOID            = 14,
    SOAPY_REMOTE_CALL            = 15,
    SOAPY_REMOTE_SIZE_LIST       = 16,
    SOAPY_REMOTE_TYPE_MAX        = 17,
};

enum SoapyRemoteCalls
{
    //factory
    SOAPY_REMOTE_FIND            = 0,
    SOAPY_REMOTE_MAKE            = 1,
    SOAPY_REMOTE_UNMAKE          = 2,
    SOAPY_REMOTE_HANGUP          = 3,

    //logger
    SOAPY_REMOTE_GET_SERVER_ID          = 20,
    SOAPY_REMOTE_START_LOG_FORWARDING   = 21,
    SOAPY_REMOTE_STOP_LOG_FORWARDING    = 22,

    //identification
    SOAPY_REMOTE_GET_DRIVER_KEY      = 100,
    SOAPY_REMOTE_GET_HARDWARE_KEY    = 101,
    SOAPY_REMOTE_GET_HARDWARE_INFO   = 102,

    //channels
    SOAPY_REMOTE_SET_FRONTEND_MAPPING      = 200,
    SOAPY_REMOTE_GET_FRONTEND_MAPPING      = 201,
    SOAPY_REMOTE_GET_NUM_CHANNELS          = 202,
    SOAPY_REMOTE_GET_FULL_DUPLEX           = 203,

    //stream
    SOAPY_REMOTE_SETUP_STREAM              = 300,
    SOAPY_REMOTE_CLOSE_STREAM              = 301,
    SOAPY_REMOTE_ACTIVATE_STREAM           = 302,
    SOAPY_REMOTE_DEACTIVATE_STREAM         = 303,

    //antenna
    SOAPY_REMOTE_LIST_ANTENNAS      = 500,
    SOAPY_REMOTE_SET_ANTENNA        = 501,
    SOAPY_REMOTE_GET_ANTENNA        = 502,

    //corrections
    SOAPY_REMOTE_HAS_DC_OFFSET_MODE       = 600,
    SOAPY_REMOTE_SET_DC_OFFSET_MODE       = 601,
    SOAPY_REMOTE_GET_DC_OFFSET_MODE       = 602,
    SOAPY_REMOTE_HAS_DC_OFFSET            = 603,
    SOAPY_REMOTE_SET_DC_OFFSET            = 604,
    SOAPY_REMOTE_GET_DC_OFFSET            = 605,
    SOAPY_REMOTE_HAS_IQ_BALANCE_MODE      = 606,
    SOAPY_REMOTE_SET_IQ_BALANCE_MODE      = 607,
    SOAPY_REMOTE_GET_IQ_BALANCE_MODE      = 608,

    //gain
    SOAPY_REMOTE_LIST_GAINS               = 700,
    SOAPY_REMOTE_SET_GAIN_MODE            = 701,
    SOAPY_REMOTE_GET_GAIN_MODE            = 702,
    SOAPY_REMOTE_SET_GAIN                 = 703,
    SOAPY_REMOTE_SET_GAIN_ELEMENT         = 704,
    SOAPY_REMOTE_GET_GAIN                 = 705,
    SOAPY_REMOTE_GET_GAIN_ELEMENT         = 706,
    SOAPY_REMOTE_GET_GAIN_RANGE           = 707,
    SOAPY_REMOTE_GET_GAIN_RANGE_ELEMENT   = 708,

    //frequency
    SOAPY_REMOTE_SET_FREQUENCY                 = 800,
    SOAPY_REMOTE_SET_FREQUENCY_COMPONENT       = 801,
    SOAPY_REMOTE_GET_FREQUENCY                 = 802,
    SOAPY_REMOTE_GET_FREQUENCY_COMPONENT       = 803,
    SOAPY_REMOTE_LIST_FREQUENCIES              = 804,
    SOAPY_REMOTE_GET_FREQUENCY_RANGE           = 805,
    SOAPY_REMOTE_GET_FREQUENCY_RANGE_COMPONENT = 806,

    //sample rate
    SOAPY_REMOTE_SET_SAMPLE_RATE               = 900,
    SOAPY_REMOTE_GET_SAMPLE_RATE               = 901,
    SOAPY_REMOTE_LIST_SAMPLE_RATES             = 902,
    SOAPY_REMOTE_SET_BANDWIDTH                 = 903,
    SOAPY_REMOTE_GET_BANDWIDTH                 = 904,
    SOAPY_REMOTE_LIST_BANDWIDTHS               = 905,

    //clocking
    SOAPY_REMOTE_SET_MASTER_CLOCK_RATE         = 1000,
    SOAPY_REMOTE_GET_MASTER_CLOCK_RATE         = 1001,
    SOAPY_REMOTE_LIST_CLOCK_SOURCES            = 1002,
    SOAPY_REMOTE_SET_CLOCK_SOURCE              = 1003,
    SOAPY_REMOTE_GET_CLOCK_SOURCE              = 1004,
    SOAPY_REMOTE_LIST_TIME_SOURCES             = 1005,
    SOAPY_REMOTE_SET_TIME_SOURCE               = 1006,
    SOAPY_REMOTE_GET_TIME_SOURCE               = 1007,

    //time
    SOAPY_REMOTE_HAS_HARDWARE_TIME        = 1100,
    SOAPY_REMOTE_GET_HARDWARE_TIME        = 1101,
    SOAPY_REMOTE_SET_HARDWARE_TIME        = 1102,
    SOAPY_REMOTE_SET_COMMAND_TIME         = 1103,

    //sensors
    SOAPY_REMOTE_LIST_SENSORS            = 1200,
    SOAPY_REMOTE_READ_SENSOR             = 1201,
    SOAPY_REMOTE_LIST_CHANNEL_SENSORS    = 1202,
    SOAPY_REMOTE_READ_CHANNEL_SENSOR     = 1203,

    //registers
    SOAPY_REMOTE_WRITE_REGISTER            = 1300,
    SOAPY_REMOTE_READ_REGISTER             = 1301,

    //settings
    SOAPY_REMOTE_WRITE_SETTING            = 1400,
    SOAPY_REMOTE_READ_SETTING             = 1401,

    //gpio
    SOAPY_REMOTE_LIST_GPIO_BANKS         = 1500,
    SOAPY_REMOTE_WRITE_GPIO              = 1501,
    SOAPY_REMOTE_WRITE_GPIO_MASKED       = 1502,
    SOAPY_REMOTE_READ_GPIO               = 1503,
    SOAPY_REMOTE_WRITE_GPIO_DIR          = 1504,
    SOAPY_REMOTE_WRITE_GPIO_DIR_MASKED   = 1505,
    SOAPY_REMOTE_READ_GPIO_DIR           = 1506,

    //i2c
    SOAPY_REMOTE_WRITE_I2C            = 1600,
    SOAPY_REMOTE_READ_I2C             = 1601,

    //spi
    SOAPY_REMOTE_TRANSACT_SPI         = 1700,

    //uart
    SOAPY_REMOTE_LIST_UARTS            = 1801,
    SOAPY_REMOTE_WRITE_UART            = 1802,
    SOAPY_REMOTE_READ_UART             = 1803,
};

#define SOAPY_PACKET_WORD32(str) \
    ((unsigned int)(str[0]) << 24) | \
    ((unsigned int)(str[1]) << 16) | \
    ((unsigned int)(str[2]) << 8) | \
    ((unsigned int)(str[3]) << 0)

static const unsigned int SoapyRPCHeaderWord = SOAPY_PACKET_WORD32("SRPC");
static const unsigned int SoapyRPCTrailerWord = SOAPY_PACKET_WORD32("CPRS");

struct SoapyRPCHeader
{
    unsigned int headerWord; //!< header word to identify this protocol
    unsigned int version; //!< version number for protocol compatibility
    unsigned int length; //!< complete packet length in bytes
};

struct SoapyRPCTrailer
{
    unsigned int trailerWord; //!< trailer word to identify this protocol
};
