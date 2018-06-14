/**
 *
 *  @Discussion   8s数据包模型类
 */


#import <Foundation/Foundation.h>


@interface EcgDataPacket : NSObject

@property (nonatomic,assign) Byte   *byteArr;
@property (nonatomic,assign) long long date;
@property (nonatomic,copy) NSString *date_str;
@property (nonatomic,assign) Byte   pdkind;
@property (nonatomic,assign) int    pdsize;
@property (nonatomic,copy) NSString *pmac;
@property (nonatomic,assign) int    alarmTime;
@property (nonatomic,assign) int    pheartrate;
// ShenYj
@property (nonatomic,strong) NSArray <NSNumber *> *pheartRates;

@property (nonatomic,assign) int    pbatlevel;
@property (nonatomic,assign) int    pid;
@property (nonatomic,assign) double ptemp;

@property (nonatomic,strong) NSMutableArray *pdata;
@property (nonatomic,strong) NSMutableArray *rawDayas;
@property (nonatomic,strong) NSMutableArray *rawDayas1;  // 8s数据拆成1s包数组

- (id)initWithAddress:(NSString *)address;
- (id)initWithData:(Byte[])data;

- (void)checkData:(Byte[] )data;
- (void)setupPAlarmTime:(Byte[] )data;
- (void)setupPtime:(Byte[] )data;
- (void)setupPBatlevel:(Byte[] )data;
- (void)setupPtemp:(Byte[] )data;
- (void)setupPdata:(Byte[] )data;
- (void)setupPdataCmp:(Byte[] )data;
- (void)setupRawdata;
- (int)getType;
- (BOOL)getECGReceivedCheck;
- (NSString *)getFormatDate;
- (NSString *)getFormatYMD;
+ (NSString *)intToString:(int )data;
+ (int)byte4ToInt:(Byte)byte1 andByte:(Byte)byte2 andByteO:(Byte)byte3 andByteT:(Byte)byte4;

@end
