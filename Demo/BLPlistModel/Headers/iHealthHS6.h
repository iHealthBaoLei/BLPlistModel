//
//  iHealthHS6.h
//  iHealthHS6
//
//  Created by daiqingquan on 15/11/25.
//  Copyright © 2015年 daiqingquan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HealthUser.h"
#import "HSMacroFile.h"

/*HS6 error instruction*/
/*
 error code:
 
 7:User verify error;
 
 101,102,103,104:networkerror
 
 */



@interface iHealthHS6 : NSObject

+(iHealthHS6 *)shareIHHS6Controller;


/**
 * Binding QR Device
 * When using the SDK for the first time, measuring method needs to be called to finish user verification.

 * Import parameter:
 * @param tempUser  - Properties included: clientID，clientSecret，userAccount，height，weight，isAthlete，sex.
 * clientID & clientSecret: the only identification for users of the SDK, requires registration from iHealth administrator, please email: daiqingquan@ihealthlabs.com.cn for more information.
 * @param tempDeviceID  - device Mac
 * Return parameters:
 * The measurement via SDK will be operated in the case of 1-4, and will be terminated if any of 5-8 occurs. The interface needs to be re-called after analyzing the return parameters.
 * Notice: when a new user registers via SDK, an ‘iHealth disclaimer’ will pop up automatically, and will require the user to agree in order to continue. SDK applications require an Internet connection; there is 10-day trial period if the SDK cannot connect to the internet, the SDK is fully functional during tryout period, but will be terminated without a working internet connection after 10 days.
 
 * @param result  - Action = 1;(1:bind sucess 2：full user bind faild 3,:ts error bind faild 4 other),
 * BineNum=10
 * MAC
 * Position = 1;（user in weight number）
 * SetWifi=0
 * Status = 1;（1:binding 2：unbind）
 * TS (time);

 * @param error  - error code
 * Error code definition：
 * refer to “error” : HS6 error instruction.
*/

-(void)cloudCommandUserBinedQRDeviceWithUser:(HealthUser *)tempUser  deviceID:(NSString *)tempDeviceID  binedResult:(BinedQRDeviceBlock)result binedError:(BinedQRDeviceErrorBlock)error;

/**
 * unBind QR Device

 * Import parameter:
 * @param tempUser  - Properties included: clientID，clientSecret，userAccount，height.
 * @param tempDeviceID device Mac
 * clientID & clientSecret: the only identification for users of the SDK, requires registration from iHealth administrator, please email: lvjincan@ihealthlabs.com.cn.com for more information.
 * Return parameters:
 
 * @param result  - Action = 1;(1:bind sucess 2：full user bind faild 3,:ts error bind faild 4 other),
 * MAC
 * Status = 2;（1:binding 2：unbind）
 * TS
 
 * @param error  - error code
 * Error code definition：
 * refer to “error” : HS6 error instruction.
*/


-(void)cloudCommandUserDisBinedQRDeviceForUser:(HealthUser *)tempUser withDeviceID:(NSString *)tempDeviceID disBinedResult:(DisBinedQRDeviceBlock)result disBinedError:(DisBinedQRDeviceErrorBlock)error;

/**
 * set HS6 wifi
 * Import parameter:
 * @param password  - wifi password.
 * Return parameters:
 
 * @param disposeHS6SuccessBlock  - set sucess
 
 * @param disposeHS6FailBlock  - set faild
 
 * @param disposeHS6EndBlock  - end set
 
 * @param disposeHS6ErrorBlock - error code
 * Error code definition：
 * refer to “error” : HS6 error instruction.
 */

-(void)commandSetHS6WithPassWord:(NSString*)password disposeHS6SuccessBlock:(DisposeHS6SuccessBlock)disposeHS6SuccessBlock disposeHS6FailBlock:(DisposeHS6FailBlock)disposeHS6FailBlock  disposeHS6EndBlock:(DisposeHS6EndBlock)disposeHS6EndBlock disposeHS6ErrorBlock:(DisposeHS6ErrorBlock)disposeHS6ErrorBlock;


/**
 *get open APItoken
 
 * Get AccessToken of HS6 user,and this method is a time consuming operation that cannot be called
 * in the main thread.
 * After get AccessToken, you can call openApi(http://developer.ihealthlabs.com) to pull data form iHealth cloud.
 * Import parameter:
    @param tempUser  - Properties included: clientID，clientSecret，userAccount,serialNub.
 
 
 * Return parameters:
 * @param  getOpenAPIBlock
 * -----(NSDictionary){@link iHealthDeviceHs6Callback#onNotify(String, String, String, String)} and its'
 * action is {@link #ACTION_HS6_GET_TOKEN}.
 
 * eg. {APIName="OpenApiActivity OpenApiBG OpenApiBP OpenApiFood OpenApiSleep OpenApiSpO2 OpenApiSport
 * OpenApiUserInfo OpenApiWeight",
 * AccessToken="9fuIPl3Bo6lqJfbYjXFjuPnNwNqVfxjiUE7cMCZSjrX22RJSoKf28jtIhI0v86wjV5GJ21bc6LvMNbfYG0QsZ7cYuUSO0EkaiFTST*GcjZvvTKxfEOmhQTfLXTXYAOA
 * wCoXlEs0DRqJaHZU5JS30ssyLNlqADPV9dlvWZitQmIfXjF6CSZM2SuRCD*bbbrqtwBsn*sC24OEoQCRpDau6wQ",
 * ClassParamentKey =     {
 * "client_id" = 2a8387e3f4e94407a3a767a72dfd52ea;
 * "client_para" = 99;
 * "client_secret" = fd5e845c47944a818bc511fb7edb0a77;
 * hash = d86bf92a851bf9211851d8e6827eea55;
 * username = "he@12.com";
 * };
 * "Expires":3672000,
 *"RefreshToken":"9fuIPl3Bo6lqJfbYjXFjuPnNwNqVfxjiUE7cMCZSjrX22RJSoKf28jtIhI0v86wjV5GJ21bc6LvMNbfYG0QsZ2TcvTQNInn85XdPIJRIe-9zB-eaY5utBVKmtLjJdEEmBlx5le5mT6oF7WBwVkwx*CUpSsdgUcyE3mG3FJnSHlajogaUSUgvMgmgUaVEMYzv4pcbCUltGNAMqJt5wwvBZA",
 * "RefreshTokenExpires":31536000,
 * "UUID":"",
 * "UserID":"51027f3e09a14a55917e687c628a0f13",
 * "UserNameKey"
 * "UserOpenID"
 * "UserRegion":"https:\/\/api.ihealthlabs.com.cn:8443",
 * "client_para":"random_str"}
 * @param ErrorBlock  - error code
 * Error code definition：
 * refer to “error” : HS6 error instruction.

 */


-(void)commandHS6GetOpenAPITokenWithUser:(HealthUser *)tempUser withSuccessBlock:(DisposeHS6GetOpenAPISuccessBlock)getOpenAPIBlock withErrorBlock:(DisposeHS6GetOpenAPIErrorBlock)errorBlock;





/**
 
 * sync Weight Unit
 
 * Import parameter:
 * @param tempUser  - Properties included: clientID，clientSecret，userAccount,serialNub.
 * @param unit  - IHHS6SDKUnitWeight_kg,IHHS6SDKUnitWeight_lb,IHHS6SDKUnitWeight_oz
 * Return parameters:
 * @param unitBlock  - YES or NO
 * @param errorBlock  - error code
 * Error code definition：
 * refer to “error” : HS6 error instruction.
 */
-(void)commandHS6WithUser:(HealthUser *)tempUser withSyncWeightUnit:(IHHS6SDKUnitWeight)unit withSuccessBlock:(DisposeHS6SyncWeightUnitSuccessBlock)unitBlock withErrorBlock:(DisposeHS6SyncWeightUnitErrorBlock)errorBlock;


@end
