/**
 *  @discussion 心电数据
 */

#import <Foundation/Foundation.h>


@interface EcgRawData : NSObject

@property(nonatomic,assign) long long time;
@property(nonatomic,copy)NSString *time_str;

@property(nonatomic,strong)NSMutableArray *pdata;

@property(nonatomic,strong)NSMutableArray *pdataByte;

@property(nonatomic,copy)NSString *data;

@property(nonatomic,assign)int *pdataB;

@property(nonatomic,assign)Byte *pdataByteB;

-(NSMutableArray*)pdata;

-(void)setPdata:(NSMutableArray *)pdata;

-(NSMutableArray*)pdataByte;

-(void)setPdataByte:(NSMutableArray *)pdataByte;

-(NSString*)getFormatDate;

-(id)initWithData:(long long)time andDate:(NSMutableArray*) pdata andByte:(NSMutableArray*) pdataByte;

-(id)initWithData1:(long long)time andDate:(int*) pdata andByte:(Byte*) pdataByte;

-(id)initWithByte:(long long)time andByte:(Byte*) pdataByte;

-(id)initWithString:(NSString*)time andString:(NSString*) data;

//-(void)setupPdata:(NSMutableArray*) pdataByte;

-(void)setupPdataB:(Byte*) pdataByte;

@end
