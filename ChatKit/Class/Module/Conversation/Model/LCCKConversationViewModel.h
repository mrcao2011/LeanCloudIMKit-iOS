//
//  LCCKConversationViewModel.h
//  LCCKChatExample
//
//  Created by ElonChan ( https://github.com/leancloud/LeanCloudChatKit-iOS ) on 15/11/18.
//  Copyright © 2015年 https://LeanCloud.cn . All rights reserved.
//

#import <UIKit/UIKit.h>

#import "LCCKMessage.h"
#import <AVOSCloudIM/AVOSCloudIM.h>
#import <AVOSCloud/AVOSCloud.h>
#import "LCCKConstants.h"

@class LCCKMessage;
@class LCCKConversationViewController;

@protocol LCCKConversationViewModelDelegate <NSObject>

@optional
- (void)reloadAfterReceiveMessage:(LCCKMessage *)message;
- (void)messageSendStateChanged:(LCCKMessageSendState)sendState  withProgress:(CGFloat)progress forIndex:(NSUInteger)index;
- (void)messageReadStateChanged:(LCCKMessageReadState)readState withProgress:(CGFloat)progress forIndex:(NSUInteger)index;
@end

@protocol LCCKChatMessageCellDelegate;

typedef void (^LCCKSendMessageSuccessBlock)(NSString *messageUUID);
typedef void (^LCCKSendMessageSuccessFailedBlock)(NSString *messageUUID, NSError *error);

@interface LCCKConversationViewModel : NSObject <UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, assign, readonly) NSUInteger messageCount;

@property (nonatomic, weak) id<LCCKConversationViewModelDelegate> delegate;

- (instancetype)initWithParentViewController:(LCCKConversationViewController *)parentViewController;

@property (nonatomic, strong, readonly) NSMutableArray<LCCKMessage *> *dataArray;
@property (nonatomic, strong, readonly) NSMutableArray<AVIMTypedMessage *> *avimTypedMessage;

/**
 *  添加一条消息到LCCKConversationViewModel,并不会出发发送消息到服务器的方法
 */
- (void)addMessage:(LCCKMessage *)message;

/**
 *  发送一条消息,消息已经通过addMessage添加到LCCKConversationViewModel数组中了,此方法主要为了LCCKChatServer发送消息过程
 */
- (void)sendMessage:(LCCKMessage *)message;

- (void)removeMessageAtIndex:(NSUInteger)index;

- (LCCKMessage *)messageAtIndex:(NSUInteger)index;

+ (NSMutableArray *)getAVIMMessages:(NSArray<LCCKMessage *> *)lcimMessages;
+ (AVIMTypedMessage *)getAVIMTypedMessageWithMessage:(LCCKMessage *)message;
+ (NSMutableArray *)getLCCKMessages:(NSArray<AVIMTypedMessage *> *)avimTypedMessage;
- (void)loadMessagesWhenInitHandler:(LCCKBooleanResultBlock)handler;
- (void)loadOldMessages;
- (void)updateConversationAsRead;
- (void)getAllImageMessagesForMessage:(LCCKMessage *)message allImageMessageImages:(NSArray **)allImageMessageImages selectedMessageIndex:(NSNumber **)selectedMessageIndex;

@end
