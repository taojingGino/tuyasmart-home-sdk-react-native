//
//  TYBLEAgent.h
//  TuyaSmartPublic
//
//  Created by 冯晓 on 16/8/2.
//  Copyright © 2016年 Tuya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@class TYBLECentralManager;
@class TYBLEPeripheral;

typedef void(^TYBLEAgentCentralNotifyCallback)(NSData *data, NSError *error);
typedef void(^TYBLEAgentCentralReadCallback)(NSData *data, NSError *error);
typedef void(^TYBLEAgentCentralWriteCallback)(NSError *error);
typedef void(^TYBLEAgentCentralDiscoverCallback)(NSArray<TYBLEPeripheral *> *peripherals, NSError *error);
typedef void(^TYBLEAgentCentralConnectionCallback)(TYBLEPeripheral* peripheral,NSError* error) ;

@protocol TYBLEAgent <NSObject>

@optional

- (void)onCentralDidDisconnecteFromPeripheral:(TYBLEPeripheral*)peripheral;

@end
typedef NS_ENUM(int, TYBLEAgentRole)
{
    kTYBLEAgentPeripheral = 0,
    kTYBLEAgentCentral = 1,
    kTYBLEAgentBoth = 2,
};


@interface TYBLEAgent : NSObject

@property (nonatomic, assign, readonly) TYBLEAgentRole role;
@property (nonatomic, assign) id<TYBLEAgent> delegate;
@property (nonatomic, strong) TYBLECentralManager* cManager;



- (instancetype)initWithType:(TYBLEAgentRole)role;

////////////////////////////////////////////////////////////////////////////////////
#pragma mark - central  methods

/**
 *  发现周围的BLE设备
 *
 *  @param aCharacteristic 特征UUID
 *  @param aService        服务UUID
 *  @param aCallback       回调
 */
- (void)discoverCharactUUID:(NSString *)aCharacteristic
                serviceUUID:(NSString *)aService
                 completion:(TYBLEAgentCentralDiscoverCallback)aCallback;
/**
 *  停止扫描
 */
- (void)stopDiscovering;

/**
 *  链接发现的BLE设备
 *
 *  @param peripheral      待链接的BLE设备
 *  @param aCharacteristic 特征UUID
 *  @param aService        服务UUID
 *  @param aCallback       回调
 */
- (void)connectPeripheral:(TYBLEPeripheral*)peripheral
              CharactUUID:(NSString *)aCharacteristic
              serviceUUID:(NSString *)aService
               completion:(TYBLEAgentCentralConnectionCallback)aCallback;

/**
 *  链接发现的BLE设备
 *
 *  @param peripheral      待链接的BLE设备
 *  @param aCharacteristic 特征UUID
 *  @param aService        服务UUID
 *  @param timeout         超时
 *  @param aCallback       回调
 */
- (void)connectPeripheral:(TYBLEPeripheral*)peripheral
              CharactUUID:(NSString *)aCharacteristic
              serviceUUID:(NSString *)aService
                  timeout:(NSTimeInterval)timeout
               completion:(TYBLEAgentCentralConnectionCallback)aCallback;

/**
 *  断开链接的BLE设备
 *
 *  @param peripheral 链接的BLE设备
 */
- (void)disconnectPeripheral:(TYBLEPeripheral*)peripheral;

/**
 *  向BLE设备写数据
 *
 *  @param aData           待写入的二进制数据
 *  @param aPeripheral     目标BLE设备
 *  @param aCharacteristic 设备特征UUID
 *  @param aService        服务UUID
 *  @param aCallback       回调
 */
- (void)writeData:(NSData *)aData
     toPeripheral:(TYBLEPeripheral *)aPeripheral
      charactUUID:(NSString *)aCharacteristic
      serviceUUID:(NSString *)aService
       completion:(TYBLEAgentCentralWriteCallback)aCallback;
/**
 *  从BLE设备读数据
 *
 *  @param aPeripheral     待读入的BLE设备
 *  @param aCharacteristic 目标设备特征UUID
 *  @param aService        服务UUID
 *  @param aCallback       回调
 */
- (void)readDataFromPeriphreral:(TYBLEPeripheral *)aPeripheral
                    CharactUUID:(NSString *)aCharacteristic
                    serviceUUID:(NSString *)aService
                     completion:(TYBLEAgentCentralReadCallback)aCallback;
/**
 *  接受BLE设备Push来的数据
 *
 *  @param b               传输数据的开关
 *  @param aPeripheral     链接的BLE设备
 *  @param aCharacteristic 目标设备特征UUID
 *  @param aService        服务UUID
 *  @param aCallback       回调
 */
- (void)notifyData:(BOOL)b
     FromPeriphral:(TYBLEPeripheral *)aPeripheral
       CharactUUID:(NSString *)aCharacteristic
       serviceUUID:(NSString *)aService
        completion:(TYBLEAgentCentralNotifyCallback)aCallback;

@end
