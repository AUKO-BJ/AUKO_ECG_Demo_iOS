/**
 *
 *  @author       ShenYj
 *  @copyright    Copyright © 2017 - 2018年 ShenYj. All rights reserved.
 *
 *  @Discussion   为系统默认<i>CBPeripheral</i>类 @see CBPeripheral  增添ECG特有属性
 */

#import <CoreBluetooth/CoreBluetooth.h>

@interface CBPeripheral (Extension)

/**
 *  @property peripheralMACStr
 *
 *  @discussion 设备信息: ECG 设备MAC地址字符串 
 */
@property (nonatomic,  copy) NSString *peripheralMACStr;
/**
 *  @property signalLevel
 *
 *  @discussion 设备信息: ECG 信号强度 广播时可获得
 */
@property (nonatomic,strong) NSNumber *signalLevel;
/**
 *  @property distance
 *
 *  @discussion 设备信息: 与ECG设备间距离
 */
@property (nonatomic,strong) NSNumber *distance;
/**
 *  @property versionString
 *
 *  @discussion 设备信息: ECG设备版本号 广播时和同步时间戳时可获得
 */
@property (nonatomic,  copy) NSString *versionString;
/**
 *  @property powerLevel
 *
 *  @discussion 设备信息: ECG当前电量
 */
@property (nonatomic,strong) NSNumber *powerLevel;


@end
