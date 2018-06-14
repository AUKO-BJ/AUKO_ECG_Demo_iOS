//
//  UIColor+JSColor.h
//  AUKO_ECG_SDK_DEMO_iOS
//
//  Created by ecg on 2018/6/14.
//  Copyright © 2018年 Auko. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIColor (JSColor)

/**
 *  设置RGB颜色
 *
 *  @param red   red: 0 ~ 255
 *  @param green green: 0 ~ 255
 *  @param blue  blue: 0 ~ 255
 *
 *  @return RGB颜色
 */
+ (UIColor *)js_RGBColorWithRed:(CGFloat)red withGreen:(CGFloat)green withBlue:(CGFloat)blue;

/*!
 *  @metohd grayColor:
 *
 *  @param number      0~255的数值,设置需要的灰度值
 *
 *  @discussion        设置指定灰度颜色
 */
+ (UIColor *)js_GrayColor:(CGFloat)number;

/**
 *  生成随机色
 *
 *  @return 返回随机色
 */
+ (UIColor *)js_randomColor;

/**
 *  根据无符号的 32 位整数转换成对应的 RGB 颜色
 *
 *  @param hex hex
 *
 *  @return UIColor
 */
+ (instancetype)js_colorWithHex:(u_int32_t)hex;

+ (instancetype)colorWithHexString:(NSString *)hexString;

@end
