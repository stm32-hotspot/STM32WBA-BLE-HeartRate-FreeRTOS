/*$Id: //dwh/bluetooth/DWC_ble154combo/firmware/rel/1.21a-SOW07PatchV1/firmware/shrd_utils/inc/ll_fw_config.h#1 $*/
/**
 ********************************************************************************
 * @file    ll_fw_config.h
 * @brief   This file contains the major configurations to the BLE controller.
 ******************************************************************************
 * @copy
 *
 *COPYRIGHT "2021" Synopsys, Inc. This Synopsys "product" and all associated documentation
 *are proprietary to Synopsys, Inc. and may only be used pursuant to the terms and
 *conditions of a written license agreement with Synopsys, Inc. All other use,
 *reproduction, modification, or distribution of the Synopsys "product" or the associated
 *documentation is strictly prohibited.
 *
 *
 * THE ENTIRE NOTICE ABOVE MUST BE REPRODUCED ON ALL AUTHORIZED COPIES.
 *
 * <h2><center>&copy; (C) COPYRIGHT 2021 SYNOPSYS, INC.</center></h2>
 * <h2><center>&copy;   ALL RIGHTS RESERVED</center></h2>
 *
 * \n\n<b>References</b>\n
 * -Documents folder .
 *
 * <b>Edit History For File</b>\n
 *  This section contains comments describing changes made to this file.\n
 *  Notice that changes are listed in reverse chronological order.\n
 * <table border>
 * <tr>
 *   <td><b> when </b></td>
 *   <td><b> who </b></td>
 *   <td><b> what, where, why </b></td>
 * </tr>
 * <tr>
 * </tr>
 * </table>\n
 */
#ifndef INCLUDE_LL_FW_CONFIG_H
#define INCLUDE_LL_FW_CONFIG_H

/*************************** BLE Configuration *************************************/
/*Configurations of BLE will apply only when BLE is enabled*/
/* Roles configurations */
#define SUPPORT_EXPLCT_OBSERVER_ROLE                0 /* Enable\Disable Explicit observer role. Enable:1 - Disable:0 */
#define SUPPORT_EXPLCT_BROADCASTER_ROLE             0 /* Enable\Disable Explicit broadcaster role. Enable:1 - Disable:0 */
#define SUPPORT_MASTER_CONNECTION                   0 /* Enable\Disable Master connection role. Enable:1 - Disable:0 */
#define SUPPORT_SLAVE_CONNECTION                    0 /* Enable\Disable Slave connection role. Enable:1 - Disable:0 */

/* Standard features configurations */
#define SUPPORT_LE_ENCRYPTION                       0 /* Enable\Disable Encryption feature. Enable:1 - Disable:0 */
#define SUPPORT_PRIVACY                             0 /* Enable\Disable Privacy feature. Enable:1 - Disable:0 */
#define SUPPORT_LE_EXTENDED_ADVERTISING             0 /* Enable\Disable Extended advertising feature. Enable:1 - Disable:0 */
#define SUPPORT_LE_PERIODIC_ADVERTISING             0 /* Enable\Disable Periodic advertising feature. Enable:1 - Disable:0 */
#define SUPPORT_LE_POWER_CLASS_1                    0 /* Enable\Disable Low power class 1 feature. Enable:1 - Disable:0 */
#define SUPPORT_AOA_AOD                             0 /* Enable\Disable AOA_AOD feature. Enable:1 - Disable:0 */
#define SUPPORT_PERIODIC_SYNC_TRANSFER              0 /* Enable\Disable PAST feature. Enable:1 - Disable:0 */
#define SUPPORT_SLEEP_CLOCK_ACCURCY_UPDATES         0 /* Enable\Disable Sleep Clock Accuracy Updates Feature. Enable:1 - Disable:0 */
#define SUPPORT_CONNECTED_ISOCHRONOUS               0 /* Enable\Disable Connected Isochronous Channel Feature. Enable:1 - Disable:0 */
#define SUPPORT_BRD_ISOCHRONOUS                     0 /* Enable\Disable Broadcast Isochronous Channel Feature. Enable:1 - Disable:0 */
#define SUPPORT_SYNC_ISOCHRONOUS                    0 /* Enable\Disable Broadcast Isochronous Synchronizer Channel Feature. Enable:1 - Disable:0 */
#define SUPPORT_LE_POWER_CONTROL                    0 /* Enable\Disable LE Power Control Feature. Enable:1 - Disable:0 */
/* Capabilities configurations */
#define MAX_NUM_CNCRT_STAT_MCHNS                    0 /* Set maximum number of states the controller can support */
#define USE_NON_ACCURATE_32K_SLEEP_CLK              1 /* Allow to drive the sleep clock by sources other than the default crystal oscillator source.*/
                                                       /*LL can use crystal oscillator or RTC or RCO to drive the sleep clock.This selection is done via "DEFAULT_SLEEP_CLOCK_SOURCE" macro. */

/* Non-standard features configurations */
#define NUM_OF_CTSM_EMNGR_HNDLS                     0 /* Number of custom handles in event manager to be used for app specific needs */
#define SUPPORT_AUGMENTED_BLE_MODE                  0 /* Enable\Disable Augmented BLE Support. Enable:1 - Disable:0 */
#define SUPPORT_PTA                                 1 /* Enable\Disable PTA Feature. Enable:1 - Disable:0 */

#define CHECK_ANY_MISSED_EVENT_ON_DEEP_SLEEP_EXIT   1 /* Enable\Disable calling event scheduler handler function at the end of deep sleep exit*/

/*************************** MAC Configuration *************************************/
/*Configurations of MAC will apply only when MAC is enabled*/
#define FFD_DEVICE_CONFIG                           1 /* Enable\Disable FFD:1 - RFD:0 */
#ifdef RFD_DEVICE_CONFIG
#undef FFD_DEVICE_CONFIG
#define FFD_DEVICE_CONFIG                           0 /* Enable\Disable FFD:1 - RFD:0 */
#endif

#define RAL_NUMBER_OF_INSTANCE                      1 /* The Number of RAL instances supported */
#define MAX_NUMBER_OF_INDIRECT_DATA                 10 /* The maximum number of supported indirect data buffers */
#define SUPPORT_OPENTHREAD_1_2                      0 /* Enable / disable FW parts related to new features introduced in openthread 1.2*/
#define SUPPORT_SEC                                 0 /* The MAC Security Supported : 1 - Not Supported:0 */
#define RADIO_CSMA                                  1 /* Enable\Disable CSMA Algorithm in Radio Layer, Must be Enabled if MAC_LAYER_BUILD */
#define SUPPORT_ANT_DIV                             1 /* Enable/Disable Antenna Diversity Feature */
#define SUPPORT_A_MAC                               1
#define SMPL_PRTCL_TEST_ENABLE                      0
#define IEEE_EUI64_VENDOR_SPECIFIC_FUNC             1 /* Comment to disable EUI-64 vendor specific function, in this case EUI-64 is not unique */

#endif /* INCLUDE_LL_FW_CONFIG_H */
