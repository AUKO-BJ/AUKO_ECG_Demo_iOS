/**
 *
 *  @protocol JSBLEHandlerProtocol
 *
 *  @discussion BLE 协议类, 获得蓝牙相关的状态、结果回调
 *              所有回调均在主线程
 *
 */

#import "JSBluetoothToolConst.h"
#import "CBPeripheral+Extension.h"

/*!
 *  @enum ECGBLESearchResult
 *
 *  @discussion Represents the current ble-device-search result.
 *
 *  @constant ECGBLESearchResultTimeOut      be cause timeout by connect with timeout parameter
 *  @constant ECGBLESearchResultAutoStop     stop normal
 *  @constant ECGBLESearchResultManualStop   invoke the stop method
 *
 */
typedef NS_ENUM(NSUInteger, ECGBLESearchResult) {
    ECGBLESearchResultTimeOut,      //! 超时 (设置了超时时长) <
    ECGBLESearchResultAutoStop,     //! 自动停止(当开始连接外设(ECG)时, 自动终止搜索操作, 则会自动停止扫描) <
    ECGBLESearchResultManualStop,   //! 手动停止(人工干预, 调用<code>stopToScanBluetoothPeripheral</code>接口停止搜索) <
};


@class CBPeripheral;
@protocol JSBLEHandlerProtocol <NSObject>

@optional

/**
 *  @method js_peripheralSearchFinished:
 *
 *  @param searchResult     搜索结果
 *
 *  @discussion             搜索停止后被调用, 通过searchResult可以得知本次搜索结果原因, 例如因为设置了超时时间而停止, 手动调用了停止搜索接口停止等
 */
- (void)js_peripheralSearchFinished:(ECGBLESearchResult)searchResult;
/**
 *  @method js_peripheralFounded:
 *
 *  @param peripherals      扫描到的外设集合
 *
 *  @discussion             搜索到外设后调用,参数<i>peripherals</i>用来记录扫描到的周边BLE设备
 *                          此SDK做了搜索过滤, 只能搜索到ECG设备, 无法搜到周边其他蓝牙外设
 */
- (void)js_peripheralFounded:(NSArray <CBPeripheral *> *)peripherals;
/**
 *  @method js_peripheralConnected:
 *
 *  @param peripheral       外设对象
 *
 *  @discussion             连接上设备时调用, <i>peripheral</i>就是本次连接上的外设 (ECG)
 */
- (void)js_peripheralConnected:(CBPeripheral *)peripheral;
/**
 *  @method js_peripheralDisconnected:
 *
 *  @param peripheral       外设对象
 *
 *  @discussion             断开连接时调用, <code>peripheral</code>就是本次断开连接的外设 (ECG)
 */
- (void)js_peripheralDisconnected:(CBPeripheral *)peripheral;


@end
