/**
 *
 *  @author       ShenYj
 *  @copyright    Copyright © 2018年 ShenYj. All rights reserved.
 *
 *  @Discussion   用户授权, 绑定蓝牙代理对象
 */


#import <Foundation/Foundation.h>

@protocol JSBLEHandlerProtocol;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, AUKOGender) {
    /** 女 */
    AUKOGenderFemale,
    /** 男 */
    AUKOGenderMale,
    /** 未知 */
    AUKOGenderUnknow
};

typedef void(^ECG_SDK_OAuthCallback)(BOOL result,NSString *msg);

@interface JSECGOAuth : NSObject

/**
 *  @method js_registerECG_SDK: birthday: gender: callBlack:
 *
 *  @param tel           手机号码
 *  @param birthday      生日, 格式: 2018-06-19
 *  @param gender        性别
 *  @param delegate      代理对象, 实现<i>JSBLEHandlerProtocol</i>协议的对象, 需要通过实现协议方法来获取周边搜索到的设备
 *  @param debugMode     YES -> Debug模式, NO -> Release模式
 *  @param callBack      回调
 *
 *  @discussion          SDK注册接口
 */
+ (void)js_registerECG_SDK: (NSString *)tel
                  birthday: (NSString *)birthday
                    gender: (AUKOGender)gender
                  delegate: (id<JSBLEHandlerProtocol>)delegate
                 debugMode: (BOOL)debugMode
                  callBack: (ECG_SDK_OAuthCallback)callBack;

/**
 *  @method js_registerECG_SDK: age: gender: callBlack:
 *
 *  @param tel           手机号码
 *  @param age           年龄, 格式: 20
 *  @param gender        性别
 *  @param delegate      代理对象, 实现<i>JSBLEHandlerProtocol</i>协议的对象, 需要通过实现协议方法来获取周边搜索到的设备
 *  @param debugMode     YES -> Debug模式, NO -> Release模式
 *  @param callBack      回调
 *
 *  @discussion          SDK注册接口
 */
+ (void)js_registerECG_SDK: (NSString *)tel
                       age: (NSString *)age
                    gender: (AUKOGender)gender
                  delegate: (id<JSBLEHandlerProtocol>)delegate
                 debugMode: (BOOL)debugMode
                  callBack: (ECG_SDK_OAuthCallback)callBack;

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


@end
NS_ASSUME_NONNULL_END
