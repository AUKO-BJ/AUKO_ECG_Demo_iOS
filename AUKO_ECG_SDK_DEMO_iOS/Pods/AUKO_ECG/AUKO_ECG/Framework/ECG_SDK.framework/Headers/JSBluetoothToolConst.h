/**
 *  @brief  BLE 常量
 *
 *  @author       ShenYj
 *  @copyright    Copyright © 2018年 ShenYj. All rights reserved.
 */



#import <UIKit/UIKit.h>
#import "OneSecondPacket.h"
#import "JSBluetoothManager.h"
#import "JSBLEHandlerProtocol.h"
#import "JSBluetoothToolConst.h"
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>



#pragma mark - UUID & ECG

/** ECG设备名称 */
FOUNDATION_EXTERN NSString * const ECGDeviceDisplayName;
/** 服务UUID */
FOUNDATION_EXTERN NSString * const ECGDeviceServiceUUIDString;
/** 写入特征 */
FOUNDATION_EXTERN NSString * const CharacteristicUUIDStringWrite;
/** 订阅特征 */
FOUNDATION_EXTERN NSString * const CharacteristicUUIDStringNotify;


/** 记录连接ECG的模式, 是否自动重连, 还是手动重连 1->下一个生命周期自动重连 */
FOUNDATION_EXTERN NSString * const kAukoConnectECGKey;

/** 最后一次连接的ECG设备标识 */
FOUNDATION_EXTERN NSString * const kLastPeripheralIdentifierConnectedKey;
/** 最后一次连接的ECG设备MAC地址信息 */
FOUNDATION_EXTERN NSString * const kLastPeripheralMACPath;
/** 保存最后一次连接ECG设备的Version */
FOUNDATION_EXTERN NSString * const kLastPeripheralVersionKey;

/** 获取数据的通知 */
FOUNDATION_EXTERN NSString * const kReceivedECGOneSecPacketNotification;
/** 收到通知后, 获取1s包的key */
FOUNDATION_EXTERN NSString * const kOneSecPacketKey;

/** ECG OTA 升级文件缓存标识 */
FOUNDATION_EXTERN NSString * const kECGOTACacheFileKey;



#pragma mark - Other

/** 每次发送字节的长度 */
FOUNDATION_EXTERN NSInteger const JSCentralToolSendDataSubLength;
/** 扫描蓝牙是否开启的频率: 自动重连的频率 单位: 秒 */
FOUNDATION_EXTERN CGFloat const kScanBluetoothStatusCycle;
/** 检查蓝牙连接状态下,50s内是否有数据,如果50s内没有收到数据,则断开蓝牙连接 */
FOUNDATION_EXTERN CGFloat const kECGConnectionIsSendData;
/** 自动记录上一次连接过外设的identifier */
FOUNDATION_EXTERN BOOL const JSCentralManagerAutoSaveLastConnectedPeripheralIdentifier;


//#ifdef DEBUG
//#define NSLog(fmt, ...) NSLog((@"%s [Line %d]  " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
//#else
//#define NSLog(...)
//#endif


