#import "Memcachejsi.h"
#import "react-native-memcachejsi.h"

#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>
#import <jsi/jsi.h>
#import <Foundation/Foundation.h>

@implementation Memcachejsi

RCT_EXPORT_MODULE()

@synthesize bridge = _bridge;
@synthesize methodQueue = _methodQueue;

// Example method for C++
// See the implementation of the example module in the `cpp` folder
RCT_EXPORT_METHOD(multiply:(nonnull NSNumber*)a withB:(nonnull NSNumber*)b
                  withResolver:(RCTPromiseResolveBlock)resolve
                  withReject:(RCTPromiseRejectBlock)reject)
{
    NSNumber *result = @(memcachejsi::multiply([a doubleValue], [b doubleValue]));

    resolve(result);
}

+ (BOOL)requiresMainQueueSetup {
    return YES;
}

- (void)setBridge:(RCTBridge *)bridge {
  NSLog(@"yyp ---------- 0");
  _bridge = bridge;
  _setBridgeOnMainQueue = RCTIsMainQueue();

  RCTCxxBridge *cxxBridge = (RCTCxxBridge *)self.bridge;
  if (!cxxBridge.runtime) {
    return;
  }
  memcachejsi::install(*(facebook::jsi::Runtime *)cxxBridge.runtime);
  NSLog(@"yyp ---------- 1");
}

@end
