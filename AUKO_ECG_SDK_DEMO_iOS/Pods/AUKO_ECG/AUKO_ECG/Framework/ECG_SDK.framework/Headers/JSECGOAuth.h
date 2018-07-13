/**
 *
 *  @author       ShenYj
 *  @copyright    Copyright © 2018年 ShenYj. All rights reserved.
 *
 *  @Discussion   用户授权, 绑定蓝牙代理对象, 报告相关接口
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

typedef void(^ECG_SDK_OAuthCallback)(BOOL result, NSString *msg);
typedef void(^ECG_SDK_SuccessCallback)(id __nullable object);
typedef void(^ECG_SDK_FaildCallback)(NSError * __nullable err, NSString * __nullable extensionMsg);
typedef void(^ECG_SDK_WearingAndRepeatSuccessCallback)(NSUInteger wearingSec, NSUInteger repeatSec, NSString *adviseMsg);

@interface JSECGOAuth : NSObject

#pragma mark - OAuth

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


#pragma mark - About Apply Reporter

//                 申请报告的流程:
//
//            检查某年某月哪天有已上传数据
//                      ↓
//     根据返回结果检查对应某天内的佩戴时长与重复时长
//                      ↓
//            根据结果决定是否要申请报告

/**
 *  @method js_CheckServerDataWith: month: success: faild:
 *
 *  @param year             年份, 格式: 2018
 *  @param month            月份, 格式: 05
 *  @param success          成功回调, 返回的是 该月内有上传数据记录的<i>Day</i>的数组, 如@[21, 24, 25, 26]
 *  @param faild            失败回调
 *
 *  @discussion             检查某月内哪一天有上传数据的记录
 */
+ (void)js_CheckServerDataWith: (NSString *)year
                         month: (NSString *)month
                       success: (ECG_SDK_SuccessCallback)success
                         faild: (ECG_SDK_FaildCallback)faild;
/**
 *  @method js_CheckServerDataWith: month: success: faild:
 *
 *  @param date             日期, 格式: 2018-05
 *  @param success          成功回调, 返回的是 该月内有上传数据记录的<i>Day</i>的数组, 如@[21, 24, 25, 26]
 *  @param faild            失败回调
 *
 *  @discussion             检查某月内哪一天有上传数据的记录
 */
+ (void)js_CheckServerDataWithDate: (NSString *)date
                           success: (ECG_SDK_SuccessCallback)success
                             faild: (ECG_SDK_FaildCallback)faild;


/**
 *  @method js_checkWearingAndRepeatSecTime: endTime: success: faild:
 *
 *  @param startTime        开始时间, 格式: 2018-05-10 01:00:00, 最小单位为小时
 *  @param endTime          结束时间, 格式: 2018-05-10 01:00:00
 *  @param success          成功回调, 包含佩戴时长(单位:秒), 重复时长(单位:秒), 建议文本
 *  @param faild            失败回调
 *
 *  @discussion             检查佩戴时长和重复时长
 */
+ (void)js_checkWearingAndRepeatSecTime:(NSString *)startTime
                                endTime:(NSString *)endTime
                                success:(ECG_SDK_WearingAndRepeatSuccessCallback)success
                                  faild:(ECG_SDK_FaildCallback)faild;

/**
 *  @method js_ApplyReportWith: endTime: remark: callBack:
 *
 *  @param startTime        开始时间 , 格式: 2018-05-10 01:00:00, 最小单位为小时
 *  @param endTime          结束时间 , 格式: 2018-05-10 01:00:00
 *  @param remark           补充信息
 *  @param success          成功回调
 *  @param faild            失败回调
 *
 *  @discussion             申请一份报告 (暂时为机器报告, 将来会被取消)
 */
+ (void)js_ApplyReportWith: (NSString *)startTime
                   endTime: (NSString *)endTime
                    remark: (NSString *)remark
                   success: (ECG_SDK_SuccessCallback)success
                     faild: (ECG_SDK_FaildCallback)faild;


#pragma mark - About View Reporter

/**
 *  @method js_GetShortTimeAnalysisList: success: faild:
 *
 *  @param pageIndex        页码索引
 *  @param success          成功回调
 *  @param faild            失败回调
 *
 *  @discussion             查看短时分析报告列表
 */
+ (void)js_GetShortTimeAnalysisList: (int)pageIndex
                            success: (ECG_SDK_SuccessCallback)success
                              faild: (ECG_SDK_FaildCallback)faild;

/**
 *  @method js_GetECGAnalysisList: success: faild:
 *
 *  @param pageIndex        页码索引
 *  @param success          成功回调
 *  @param faild            失败回调
 *
 *  @discussion             查看心电报告列表
 */
+ (void)js_GetECGAnalysisList: (int)pageIndex
                      success: (ECG_SDK_SuccessCallback)success
                        faild: (ECG_SDK_FaildCallback)faild;

/**
 *  @method js_GetSTReportID: success: faild:
 *
 *  @param reportIDString   报告ID
 *  @param success          成功回调
 *  @param faild            失败回调
 *
 *  @discussion             查看短时分析报告详情
 */
+ (void)js_GetSTReportID: (NSString *)reportIDString
                 success: (ECG_SDK_SuccessCallback)success
                   faild: (ECG_SDK_FaildCallback)faild;
/**
 *  @method js_GetECGTaskID: success: faild:
 *
 *  @param taskIDString     报告ID
 *  @param success          成功回调
 *  @param faild            失败回调
 *
 *  @discussion             查看懂啊提心电报告详情
 */
+ (void)js_GetECGTaskID: (NSString *)taskIDString
                success: (ECG_SDK_SuccessCallback)success
                  faild: (ECG_SDK_FaildCallback)faild;



@end
NS_ASSUME_NONNULL_END
