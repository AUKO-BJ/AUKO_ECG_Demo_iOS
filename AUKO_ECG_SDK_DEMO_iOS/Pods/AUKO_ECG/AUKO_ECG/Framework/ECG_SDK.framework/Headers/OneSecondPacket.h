/**
 *
 *  @discussion 一秒心电数据包
 */


#import "EcgRawData.h"
#import <Foundation/Foundation.h>

@interface OneSecondPacket : NSObject

/**
*  @property battery
*
*  @discussion ECG电量
*/
@property(nonatomic,assign) int        battery;
/**
 *  @property temp
 *
 *  @discussion 温度, 暂时无用
 */
@property(nonatomic,assign) double     temp;
/**
 *  @property rate
 *
 *  @discussion 心率
 */
@property(nonatomic,assign) int        rate;
/**
 *  @property date
 *
 *  @discussion 日期
 */
@property(nonatomic,assign) long long  date;
/**
 *  @property time
 *
 *  @discussion 时间
 */
@property(nonatomic,  copy) NSString   *time;
/**
 *  @property rawData
 *
 *  @discussion 点数据
 */
@property(nonatomic,strong) EcgRawData *rawData;


- (instancetype)initWithDict:(NSDictionary *)dict;
+ (instancetype)dateListWithDict:(NSDictionary *)dict;

@end
