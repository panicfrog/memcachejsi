#import <React/RCTBridgeModule.h>

#ifdef __cplusplus

#import "react-native-memcachejsi.h"

#endif

@interface Memcachejsi : NSObject <RCTBridgeModule>

@property (nonatomic, assign) BOOL setBridgeOnMainQueue;

@end
