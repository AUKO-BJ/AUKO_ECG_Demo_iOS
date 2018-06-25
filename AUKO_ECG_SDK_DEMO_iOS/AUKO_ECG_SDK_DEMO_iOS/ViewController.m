//
//  ViewController.m
//  AUKO_ECG_SDK_DEMO_iOS
//
//  Created by ecg on 2018/6/14.
//  Copyright © 2018年 Auko. All rights reserved.
//


#import <Masonry.h>
#import <ECG_SDK/ECG_SDK.h>
#import "UIColor+JSColor.h"
#import "ViewController.h"
#import "ECGViewController.h"

static NSString * const kTableViewCellReusedID = @"kTableViewCellReusedID";

@interface ViewController () <JSBLEHandlerProtocol, UITableViewDataSource, UITableViewDelegate>

@property (strong, nonatomic) UIButton          *ecgSearchBtn;
@property (strong, nonatomic) UIButton          *ecgStopScanBtn;
@property (strong, nonatomic) UIButton          *ecgConnectBtn;
@property (strong, nonatomic) ECGViewController *ecgDrawVC;

@property (nonatomic, strong) UITableView              *ecgDeviceList;
@property (nonatomic, strong) NSArray <CBPeripheral *> *ecgDevices;
@property (nonatomic, strong) CBPeripheral             *selectedPeripheral;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    /** 传参: 手机号 + 年龄 + 性别 */
//    [JSECGOAuth js_registerECG_SDK: @"18600699320"
//                               age: @"29"
//                            gender: AUKOGenderMale
//                          delegate: self
//                         debugMode: YES
//                          callBack: ^(BOOL result, NSString * _Nonnull msg) {
//        if (result) {
//            // 授权成功, 界面展示
//            NSLog(@" 授权成功, 界面展示");
//            return ;
//        }
//        NSLog(@" AUKO_ECG_SDK 授权失败: %@",msg);
//
//    }];

    /** 传参: 手机号 + 生日 + 性别 */
    [JSECGOAuth js_registerECG_SDK: @"18600699320"
                          birthday: @"2017-01-01"
                            gender: AUKOGenderMale
                          delegate: self
                         debugMode: YES
                          callBack: ^(BOOL result, NSString * _Nonnull msg) {
      if (result) {
          // 授权成功, 界面展示
          NSLog(@" 授权成功, 界面展示");
          
          NSData *userData = [[NSUserDefaults standardUserDefaults] objectForKey:@"AukoUserData"];
          if (userData == nil) return;
          id userModel = [NSKeyedUnarchiver unarchiveObjectWithData:userData];
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundeclared-selector"
          NSLog(@"%@",[userModel performSelector:@selector(aukoUserID)]);
#pragma clang diagnostic pop
      }
      NSLog(@" AUKO_ECG_SDK 授权失败: %@",msg);
    }];
    
    
    
    [self setUpUI];
}

#pragma mark - UI

- (void)setUpUI {
    
    self.view.backgroundColor         = [UIColor whiteColor];
    
    // 搜索
    self.ecgSearchBtn                 = [[UIButton alloc] init];
    self.ecgSearchBtn.titleLabel.font = [UIFont systemFontOfSize:14];
    self.ecgSearchBtn.backgroundColor = [UIColor js_randomColor];
    [self.ecgSearchBtn setTitle:@"开始扫描" forState:UIControlStateNormal];
    [self.ecgSearchBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    // 停止搜索
    self.ecgStopScanBtn                 = [[UIButton alloc] init];
    self.ecgStopScanBtn.titleLabel.font = [UIFont systemFontOfSize:14];
    self.ecgStopScanBtn.backgroundColor = [UIColor js_randomColor];
    [self.ecgStopScanBtn setTitle:@"停止扫描" forState:UIControlStateNormal];
    [self.ecgStopScanBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    // 连接
    self.ecgConnectBtn                 = [[UIButton alloc] init];
    self.ecgConnectBtn.titleLabel.font = [UIFont systemFontOfSize:14];
    self.ecgConnectBtn.backgroundColor = [UIColor js_randomColor];
    [self.ecgConnectBtn setTitle:@"连接设备" forState:UIControlStateNormal];
    [self.ecgConnectBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    
    self.ecgDeviceList = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
    self.ecgDeviceList.backgroundColor = self.view.backgroundColor;
    self.ecgDeviceList.dataSource      = self;
    self.ecgDeviceList.delegate        = self;
    [self.ecgDeviceList registerClass:[UITableViewCell class] forCellReuseIdentifier:kTableViewCellReusedID];
    
    if (@available(iOS 11.0, *)) {
        self.ecgDeviceList.contentInsetAdjustmentBehavior = UIScrollViewContentInsetAdjustmentNever;
    } else {
        // Fallback on earlier versions
        self.automaticallyAdjustsScrollViewInsets = NO;
    }
    [self.view addSubview:self.ecgSearchBtn];
    [self.view addSubview:self.ecgStopScanBtn];
    [self.view addSubview:self.ecgConnectBtn];
    [self.view addSubview:self.ecgDeviceList];
    
    NSArray *btns = @[self.ecgSearchBtn, self.ecgStopScanBtn, self.ecgConnectBtn];
    [btns mas_distributeViewsAlongAxis:MASAxisTypeHorizontal withFixedSpacing:10 leadSpacing:20 tailSpacing:20];
    [btns mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(40);
        make.top.mas_equalTo(self.view).mas_offset(100);
    }];
    [self.ecgDeviceList mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(self.ecgSearchBtn.mas_bottom).offset(40);
        make.left.mas_equalTo(self.ecgSearchBtn);
        make.right.mas_equalTo(self.ecgConnectBtn);
        make.bottom.mas_equalTo(self.view).mas_offset(-50);
    }];
    
    [self.ecgSearchBtn addTarget:self action:@selector(js_searchECG:) forControlEvents:UIControlEventTouchUpInside];
    [self.ecgStopScanBtn addTarget:self action:@selector(js_stopScanECG:) forControlEvents:UIControlEventTouchUpInside];
    [self.ecgConnectBtn addTarget:self action:@selector(js_connectECG:) forControlEvents:UIControlEventTouchUpInside];
}


#pragma mark - target

- (void)js_searchECG:(UIButton *)sender {
    [JSBluetoothManager.sharedCentralBLEManager js_scanBluetoothTimeOut:60];
}

- (void)js_stopScanECG:(UIButton *)sender {
    [JSBluetoothManager.sharedCentralBLEManager js_stopToScanBluetoothPeripheral];
}

- (void)js_connectECG:(UIButton *)sender {
    if (self.selectedPeripheral == nil) {
        // NSLog(@" ****** 未选择设备或选择外设对象为nil ****** ");
        return;
    }
    [JSBluetoothManager.sharedCentralBLEManager js_connect:self.selectedPeripheral connectMethod:ECGConnectMethodAuto];
}

#pragma mark - JSBLEHandlerProtocol

/**  扫描到的外设数组   */
- (void)js_peripheralFounded:(NSArray <CBPeripheral *> *)peripherals {
    self.ecgDevices = peripherals;
    [self.ecgDeviceList reloadData];
}
/**  连接上设备时调用   */
- (void)js_peripheralConnected:(CBPeripheral *)peripheral {
    self.selectedPeripheral = peripheral;
    
    if ([self.navigationController.childViewControllers containsObject:self.ecgDrawVC]) return;
    self.ecgDrawVC = [[ECGViewController alloc] init];
    [self.navigationController pushViewController:self.ecgDrawVC animated:YES];
}
/**  断开连接时调用    */
- (void)js_peripheralDisconnected:(CBPeripheral *)peripheral {
    
}
/**  搜索停止后被调用  */
- (void)js_peripheralSearchFinished:(ECGBLESearchResult)searchResult {
    
    NSString *result = @"";
    if (searchResult == ECGBLESearchResultTimeOut) {
        result = @"搜索设备超时";
    } else if (searchResult == ECGBLESearchResultAutoStop) {
        result = @"自动停止";
    } else {
        result = @"手动停止";
    }
}
#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.ecgDevices.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    CBPeripheral *peripheral            = self.ecgDevices[indexPath.row];
    UITableViewCell *cell               = [tableView dequeueReusableCellWithIdentifier:kTableViewCellReusedID forIndexPath:indexPath];
    cell.backgroundColor                = self.view.backgroundColor;
    cell.backgroundView.backgroundColor = self.view.backgroundColor;
    cell.textLabel.text                 = [NSString stringWithFormat:@"AUKO - %@",peripheral.peripheralMACStr];
    return cell;
}

#pragma mark - UITableViewDelegate

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 50.0f;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    self.selectedPeripheral = self.ecgDevices[indexPath.row];
}

@end
