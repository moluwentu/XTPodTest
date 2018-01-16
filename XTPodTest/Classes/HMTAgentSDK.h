//当前SDK版本号1.2.03，2018年1月10日更新
#ifndef HMTAgentSDK_h
#define HMTAgentSDK_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>

typedef enum {
    HMT_BATCH    = 0,  //启动时发送
    HMT_REALTIME = 1   //实时发送
} HMTReportPolicy;     //发送模式

//数据发送回调协议
@protocol HMTAgentSdkDelegate <NSObject>

@optional

//数据即将发送回调
- (void)hmtPreSend:(NSString *)from;

//数据发送成功回调
- (void)hmtSendSuccess:(NSString *)from;

//数据发送失败回调
- (void)hmtSendFail:(NSString *)from status:(NSInteger)status;

@end

@interface HMTAgentSDK : NSObject <HMTAgentSdkDelegate>

//获取sdk版本号
+ (NSString *)getSDKVersion;

//设置回调代理
+ (BOOL)setDelegate:(id)delegate;

//如果需要配置服务器地址,在调用initWithAppKey初始化SDK方法前调用setServerHost,参数值格式为:@"https://xxx.com"
+ (BOOL)setServerHost:(NSString *)host;

//设置线上配置文件地址,此方法请在初始化前调用
+ (void)setOnLineConfigUrl:(NSString *)urlString;

//设置页面自动布码
+ (void)setViewHook:(BOOL)hook;

//设置调试模式(release版本暂不处理)
+ (void)setDebug:(BOOL)debug;

//设置页面Hook例外(传入要限制hook的viewController的名称)
+ (void)setViewHookException:(NSArray<NSString *> *)exceptionArray;

//设置是否开启错误抓取,默认关闭
+ (void)setCrashReportEnabled:(BOOL)vaule;

//设置地理位置收集
//此方法为SDK自动获取地理位置信息，会在主线程调用对应的location方法
+ (void)setLocation:(BOOL)isOpen;
//此方法为用户手动获取地理位置信息传给SDK
+ (void)setLocation:(BOOL)isOpen latitude:(double)lat longitude:(double)lon;

//绑定用户ID(只是作为一个扩展接口,可以不用处理)
+ (BOOL)bindUserIdentifier:(NSString *)userid;

//初始化SDK
+ (void)initWithAppKey:(NSString *)appkey channel:(NSString *)channel;
+ (void)initWithAppKey:(NSString *)appkey channel:(NSString *)channel reportPolicy:(HMTReportPolicy)reportPolicy;
+ (void)initWithAppKey:(NSString *)appkey channel:(NSString *)channel reportPolicy:(HMTReportPolicy)reportPolicy unTracked:(NSArray<NSString *> *)unTracked;
+ (void)initWithAppKey:(NSString *)appkey channel:(NSString *)channel reportPolicy:(HMTReportPolicy)reportPolicy trackedUrl:(NSArray<NSString *> *)trackedUrl;
+ (void)initWithAppKey:(NSString *)appkey channel:(NSString *)channel reportPolicy:(HMTReportPolicy)reportPolicy unTracked:(NSArray<NSString *> *)unTracked trackedUrl:(NSArray<NSString *> *)trackedUrl;

//Activity页面加载布码调用(activity:页面名称)
+ (BOOL)startTracPage:(NSString *)activity;
+ (BOOL)startTracPage:(NSString *)activity callback:(void(^)(void))callback;
+ (BOOL)startTracPage:(NSString *)activity viewController:(UIViewController *)vc callback:(void(^)(void))callback;

//Activity页面离开布码调用(结束上一次调用startTracPage的页面)
+ (BOOL)endTracPage;
+ (BOOL)endTracPage:(NSDictionary *)property;
+ (BOOL)endTracPage:(NSDictionary *)property callback:(void(^)(void))callback;
+ (BOOL)endTracPage:(NSDictionary *)property viewController:(UIViewController *)vc callback:(void(^)(void))callback;

//发送自定义事件(action:事件名称,acc:事件发生次数,acc默认为1,property:自定义属性)
+ (BOOL)postAction:(NSString *)action;
+ (BOOL)postAction:(NSString *)action callback:(void(^)(void))callback;
+ (BOOL)postAction:(NSString *)action acc:(NSInteger)acc;
+ (BOOL)postAction:(NSString *)action acc:(NSInteger)acc callback:(void(^)(void))callback;
+ (BOOL)postAction:(NSString *)action acc:(NSInteger)acc property:(NSDictionary *)property;
+ (BOOL)postAction:(NSString *)action acc:(NSInteger)acc property:(NSDictionary *)property callback:(void(^)(void))callback;

//提交错误信息
+ (BOOL)postErrorData:(NSString *)error;
+ (BOOL)postErrorData:(NSString *)error callback:(void(^)(void))callback;
+ (BOOL)postErrorData:(NSString *)error property:(NSDictionary *)property;
+ (BOOL)postErrorData:(NSString *)error property:(NSDictionary *)property callback:(void(^)(void))callback;

//发送客户端信息
+ (BOOL)postClientData;
+ (BOOL)postClientData:(void(^)(void))callback;

//发送HTTP数据统计
+ (BOOL)postReqData:(NSString *)url method:(NSString *)method;
+ (BOOL)postReqData:(NSString *)url method:(NSString *)method callback:(void(^)(void))callback;

//处理缓存数据
+ (void)pushAllData;
+ (void)pushAllData:(void(^)(void))callback;

//webView监听设置
+ (BOOL)setActionOnWebView:(UIWebView *)webView;
+ (BOOL)setActionOnWKWebView:(WKScriptMessage *)message;

@end

#endif
