# AUKO_ECG


[![CI Status](https://img.shields.io/travis/ShenYj/AUKO_ECG.svg?style=flat)](https://travis-ci.org/ShenYj/AUKO_ECG)
[![Version](https://img.shields.io/cocoapods/v/AUKO_ECG.svg?style=flat)](https://cocoapods.org/pods/AUKO_ECG)
[![License](https://img.shields.io/cocoapods/l/AUKO_ECG.svg?style=flat)](https://cocoapods.org/pods/AUKO_ECG)
[![Platform](https://img.shields.io/cocoapods/p/AUKO_ECG.svg?style=flat)](https://cocoapods.org/pods/AUKO_ECG)

## 示例Demo

[example project](https://github.com/AUKO-BJ/AUKO_ECG_Demo_iOS) __clone此工程__

## SDK集成 & 条件


#### 1. 集成ECG_SDK<br>

 - 1.1  手动集成<br>
       *  SDK下载 [仓库地址](https://github.com/AUKO-BJ/AUKO_ECG) <br>
       *  拖入工程<br>
       
 - 1.2  pod集成<br>
   AUKO_ECG is available through [CocoaPods](https://cocoapods.org). To install
it, simply add the following line to your Podfile:

   ```ruby
   pod 'AUKO_ECG', '~> 0.0.6'
   ```
 
#### 2. 导入依赖库: 

   `CoreBluetooth.framework` <br>
   `libsqlite3.dylib`<br>
   `SystemConfiguration.framework`<br>
    
#### 3. 设置	`Other Linker Flag:  -ObjC`

#### 4. 导入头文件 ```#import <ECG_SDK/ECG_SDK.h>```


## 软件架构

- 指令集包含: x86_64、armv7、armv7s、arm64
- 软件支持 `iOS 8.0 +` <br>
- 硬件支持 `iPhone 5 +` <br>
 * `iPhone 4s 起支持蓝牙4.0 但考虑到用户体验, 硬件最低建议 iPhone 5`
 *  因未包含`i386`指令集, 如需使用模拟器, 请保证`5s +` ; __另模拟器无法进行蓝牙功能调试__

## 接口说明

- SDK 注册接口, 手机号、性别、代理对象和 生日/年龄 为必填项

```
/**
 *  @method js_registerECG_SDK: tel: birthday: age: gender: debugMode: callBlack:
 *
 *  @param userName      用户姓名
 *  @param nickName      用户昵称
 *  @param identifier    用户唯一标识, 如果为空, 则依据手机号标识用户
 *  @param birthday      生日, 格式: 2018-06-19
 *  @param age           年龄, 格式: 20
 *  @param tel           手机号码
 *  @param gender        性别
 *  @param delegate      代理对象, 实现<i>JSBLEHandlerProtocol</i>协议的对象;不允许为nil, 需要通过实现协议方法来获取周边搜索到的设备
 *  @param debugMode     是否是debug模式, YES->debug
 *  @param callBack      回调
 *
 *  @discussion          SDK注册接口
 */
+ (void)js_registerECG_SDK: (NSString * __nullable)userName
                  nickName: (NSString * __nullable)nickName
                identifier: (NSString * __nullable)identifier
                  birthday: (NSString * __nullable)birthday
                       age: (NSString * __nullable)age
                       tel: (NSString *)tel
                    gender: (AUKOGender)gender
                  delegate: (id<JSBLEHandlerProtocol>)delegate
                 debugMode: (BOOL)debugMode
                  callBack: (ECG_SDK_OAuthCallback)callBack;

```
- 搜索ECG设备  e.g.`[JSBluetoothManager.sharedCentralBLEManager js_scanBluetoothTimeOut:60];`

```
/**
 *  @method js_scanBluetoothTimeOut:
 *
 *  @param timeout  超时时长, 单位秒
 *
 *  @discusstion:   扫描蓝牙 . 如果不指定 <code>timeout</code> 参数,即默认为0,将不做限制,持续扫描设备
 */
- (void)js_scanBluetoothTimeOut:(unsigned int)timeout;
```
- 蓝牙回调方法, 获取搜索到的蓝牙设备, 连接成功, 断开连接等回调结果

```
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
```

更多接口介绍请Clone本地后查看本地文档: Git\_SDK\_Project/AUKO_ECG/html/index.html

## 补充说明

1. 连接 ECG 成功后, 若手机不反时间戳 15s ECG 主动断开连接重连
2. 连接 ECG 成功后, 若ECG不传输数据 50s App 主动断开连接重连
3. 手动调用`js_disconnect`断开连接, 本次生命周期内 , App 不会自动重连
4. 启动 App 时, 会根据上一次连接设备的选项`connectMethod`, 决定是否自动建立重连, 如果不希望启动App时自动建立连接, 在连接ECG时可以设置为`ECGConnectMethodManual`或在已经连接后调用`js_deBindingECGDevice`解除绑定
5. 缓存压缩默认启动App 60s后开始, 根据当前数据库换存量调整触发时间, 每次压缩上传100条, 间隔30s, 不足30s将间隔200s触发一次

## Author

ShenYj, shen-yanjie@seagbri.com、shenyj4@51nb.com

## License

AUKO_ECG is available under the MIT license. See the LICENSE file for more info.



