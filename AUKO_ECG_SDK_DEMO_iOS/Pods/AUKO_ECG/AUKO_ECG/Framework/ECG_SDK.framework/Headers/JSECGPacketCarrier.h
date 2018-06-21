/**
 *
 *  @author       ShenYj
 *  @copyright    Copyright © 2018年 ShenYj. All rights reserved.
 *
 *  @Discussion   心电数据载体, 从该单例中获取1s的实时心电数据
 */


#import "JSBluetoothToolConst.h"

@class EcgDataPacket;
@protocol JSECGDataTransferProtocol;
@interface JSECGPacketCarrier : NSObject <JSECGDataTransferProtocol>



/**
 *  @method sharedECGPacketCarrierManager
 *
 *  @return 心电数据包载体对象
 *
 *  @discusstion:  用此单例来获取心电数据
 */
+ ( __kindof JSECGPacketCarrier *)sharedECGPacketCarrierManager;
- (instancetype)init NS_UNAVAILABLE;


/**
 *  @method getRealTimeEcgdata
 *
 *  @return 一秒的心电数据模型
 *
 *  @discusstion:  返回实时的1s心电数据模型
 */
- (OneSecondPacket *)getRealTimeEcgdata;



@end
