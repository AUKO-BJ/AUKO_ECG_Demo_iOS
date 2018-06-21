/**
 *
 *  @author       ShenYj
 *  @copyright    Copyright © 2018年 ShenYj. All rights reserved.
 *
 *  @Discussion   蓝牙管理工具, 实现蓝牙协议, 处理基础蓝牙交互逻辑
 */


#import <CoreBluetooth/CoreBluetooth.h>

/**
 *  @enum ECGConnectMethod
 *
 *  @discussion 用于决定启动App时是否自动重连
 *
 *  @constant ECGConnectMethodAuto       当应用被杀死后, 从新启动App, 会根据上次连接的设备自动重连
 *  @constant ECGConnectMethodManual     当应用被杀死后, 重新启动App, 需要用户手动搜索连接设备
 *
 */
typedef NS_ENUM(NSUInteger, ECGConnectMethod) {
    ECGConnectMethodAuto   = 1,           //! 自动重连 默认 <
    ECGConnectMethodManual = 2,           //! 手动连接 <
} NS_ENUM_AVAILABLE_IOS(8.0);

/**
 *  @enum ECGDisConnectMethod
 *
 *  @discussion 用于决定断开连接后是否自动重连, 如果调用了 {@link js_disconnect} 方法, 那么本次App生命周期内不会自动重连
 *
 *  @constant ECGDisConnectMethodManual       手动调用断开连接方法时的状态, 此时App将不会进行重连
 *                                            如果杀死重新启动App, 是否自动重连, 由 <i>ECGConnectMethod</i> 决定
 *  @constant ECGDisConnectMethodDefault      断开连接的默认状态
 *
 */
typedef NS_ENUM(NSUInteger, ECGDisConnectMethod) {
    ECGDisConnectMethodManual,      //! 人工干预断开连接 <
    ECGDisConnectMethodDefault,     //! 其他原因导致的断开连接 默认 <
} NS_ENUM_AVAILABLE_IOS(8.0);

/**
 *  @enum ECGiphoneBLEStatus
 *
 *  @discussion Represents the current state of a iPhone.
 *
 *  @constant ECGiphoneBLEStatusUnknown       State unknown, update imminent.
 *  @constant ECGiphoneBLEStatusResetting     The connection with the system service was momentarily lost, update imminent.
 *  @constant ECGiphoneBLEStatusUnsupported   The platform doesn't support the Bluetooth Low Energy Central/Client role.
 *  @constant ECGiphoneBLEStatusUnauthorized  The application is not authorized to use the Bluetooth Low Energy role.
 *  @constant ECGiphoneBLEStatusPowerOff      Bluetooth is currently powered off.
 *  @constant ECGiphoneBLEStatusPowerOn       Bluetooth is currently powered on and available to use.
 *
 */
typedef NS_ENUM(NSUInteger, ECGiphoneBLEStatus) {
    ECGiphoneBLEStatusUnknown = 0,      //! 当前设备蓝牙位置状态, 程序初始时或其他异常场景 <
    ECGiphoneBLEStatusResetting,        //! 当前设备蓝牙重置中 <
    ECGiphoneBLEStatusUnsupported,      //! 当前设备不支持低功耗蓝牙 <
    ECGiphoneBLEStatusUnauthorized,     //! 未授权蓝牙功能 <
    ECGiphoneBLEStatusPowerOff,         //! 蓝牙关闭状态 <
    ECGiphoneBLEStatusPowerOn,          //! 蓝牙开启状态 <
} NS_ENUM_AVAILABLE_IOS(8.0);

@class JSBLEDataSerialization;
@protocol JSBLEHandlerProtocol;
@interface JSBluetoothManager : NSObject

/**
 *  @method     sharedCentralBLEManager
 *
 *  @discussion 获取蓝牙管理单例
 */
+ ( __kindof JSBluetoothManager *)sharedCentralBLEManager;

/**
 *  @property   delegate
 *
 *  @discussion 代理对象.
 */
@property (nonatomic, weak,readwrite) id <JSBLEHandlerProtocol> delegate;

/**
 *  @property   centralManager
 *
 *  @discussion 蓝牙中央管理者
 */
@property (nonatomic,strong,readonly) CBCentralManager *centralManager;

/**
 *  @property   peripheralConnected
 *
 *  @discussion 蓝牙设备 (ECG)
 */
@property (nonatomic,strong,readonly) CBPeripheral    *peripheralConnected;

/**
 *  @property   deviceBluetoothOn
 *
 *  @discussion 当前终端蓝牙是否开启
 */
@property (nonatomic,assign,readonly) BOOL deviceBluetoothIsOn;

/**
 *  @property   deviceConnecting
 *
 *  @discussion 连接状态.
 */
@property (nonatomic,assign,readonly) BOOL deviceIsConnecting;

/**
 *  @property   writeCharacteristicWithoutResponse
 *
 *  @discussion 需要写入的 characteristic (特征).因为有可能不止一个需要写入，所以在写入数据时，需要外部处理要写入哪一个.
 */
@property (nonatomic,strong,readonly) CBCharacteristic       *writeCharacteristicWithoutResponse;

/**
 *  @property dataPacketPresenter
 *
 *  @discussion 蓝牙数据解析协调器, 用于解析、组包
 */
@property (nonatomic,strong,readonly) JSBLEDataSerialization *dataPacketPresenter;

#pragma mark - 操作接口

/**
 *  @method js_scanBluetoothTimeOut:
 *
 *  @param timeout  超时时长, 单位秒
 *
 *  @discusstion:   扫描蓝牙 . 如果不指定 <code>timeout</code> 参数,即默认为0,将不做限制,持续扫描设备
 */
- (void)js_scanBluetoothTimeOut:(unsigned int)timeout;

/**
 *  @method js_stopToScanBluetoothPeripheral
 *
 *  @discusstion:         停止扫描
 */
- (void)js_stopToScanBluetoothPeripheral;

/**
 *  @method js_connect:
 *
 *  @param peripheral     扫描到的蓝牙设备
 *
 *  @discusstion:         连接设备 , 默认连接方式为:<i>ECGConnectMethodAuto</i> see {@link js_connect:connectMethod:}
 */
- (void)js_connect:(CBPeripheral *)peripheral;

/**
 *  @method js_connect: connectMethod:
 *
 *  @param peripheral     扫描到的蓝牙设备
 *  @param connectMethod  连接方式, 当下一次启动App时, 决定是否与ECG设备自动重连
 *                        ECGConnectMethodAuto自动重连, ECGConnectMethodManual手动连接, 默认ECGConnectMethodAuto
 *
 *  @discusstion:         连接设备
 */
- (void)js_connect:(CBPeripheral *)peripheral connectMethod:(ECGConnectMethod)connectMethod;

/**
 *  @method js_disconnect
 *
 *  @discussion           断开当前连接, 断开后, 本次App生命周期内, 不会自动重连, 如果杀死重启App, 会根据<i>connectMethod</i>决定是否重连
 */
- (void)js_disconnect;

/**
 *  @method js_deBindingECGDevice
 *
 *  @discusstion:         解绑设备, 彻底的断开连接, 清除最后一次连接的ECG记录, 当杀死重启App时, 即便设置为<i>ECGConnectMethodAuto</i>也无法重连
 */
+ (void)js_deBindingECGDevice;

/**
 *  @method js_isBindingECGDevice
 *
 *  @return               返回一个BOOL值,标识当前是否绑定设备
 *
 *  @discussion           是否有绑定设备
 */
+ (BOOL)js_isBindingECGDevice;


- (instancetype)init NS_UNAVAILABLE;

@end
