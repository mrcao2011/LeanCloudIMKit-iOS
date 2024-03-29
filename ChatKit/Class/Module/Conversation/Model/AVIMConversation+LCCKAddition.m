//
//  AVIMConversation+LCCKAddition.m
//  LeanCloudChatKit-iOS
//
//  Created by 陈宜龙 on 16/3/11.
//  Copyright © 2016年 ElonChan. All rights reserved.
//

#import "AVIMConversation+LCCKAddition.h"
#import <objc/runtime.h>
#import "LCCKUserSystemService.h"
#import "LCCKSessionService.h"
#import "LCCKUserModelDelegate.h"

@implementation AVIMConversation (LCCKAddition)

- (AVIMTypedMessage *)lcim_lastMessage {
    return objc_getAssociatedObject(self, @selector(lcim_lastMessage));
}

- (void)setLcim_lastMessage:(AVIMTypedMessage *)lcim_lastMessage {
    objc_setAssociatedObject(self, @selector(lcim_lastMessage), lcim_lastMessage, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (NSInteger)lcim_unreadCount {
    NSNumber *lcim_unreadCountObject = objc_getAssociatedObject(self, @selector(lcim_unreadCount));
    return [lcim_unreadCountObject intValue];
}

- (void)setLcim_unreadCount:(NSInteger)lcim_unreadCount {
    NSNumber *lcim_unreadCountObject = [NSNumber numberWithInteger:lcim_unreadCount];
    objc_setAssociatedObject(self, @selector(lcim_unreadCount), lcim_unreadCountObject, OBJC_ASSOCIATION_ASSIGN);
}

- (BOOL)lcim_mentioned {
    NSNumber *lcim_mentionedObject = objc_getAssociatedObject(self, @selector(lcim_mentioned));
    return [lcim_mentionedObject boolValue];
}

- (void)setLcim_mentioned:(BOOL)lcim_mentioned {
    NSNumber *lcim_mentionedObject = [NSNumber numberWithBool:lcim_mentioned];
    objc_setAssociatedObject(self, @selector(lcim_mentioned), lcim_mentionedObject, OBJC_ASSOCIATION_ASSIGN);
}

- (LCCKConversationType)lcim_type {
    if (self.members.count > 2) {
        return LCCKConversationTypeGroup;
    }
    return LCCKConversationTypeSingle;
}

+ (NSString *)lcim_groupConversaionDefaultNameForUserIds:(NSArray *)userIds {
    NSError *error = nil;
    NSArray *array = [[LCCKUserSystemService sharedInstance] getProfilesForUserIds:userIds error:&error];
    if (error) {
        return nil;
    }
    
    NSMutableArray *names = [NSMutableArray array];
    [array enumerateObjectsUsingBlock:^(id<LCCKUserModelDelegate>  _Nonnull user, NSUInteger idx, BOOL * _Nonnull stop) {
        [names addObject:user.name];
    }];
    return [names componentsJoinedByString:@","];
}

- (NSString *)lcim_displayName {
    if ([self lcim_type] == LCCKConversationTypeSingle) {
        NSString *peerId = [self lcim_peerId];
        NSError *error = nil;
        id<LCCKUserModelDelegate> peer = [[LCCKUserSystemService sharedInstance] getProfileForUserId:peerId error:&error];
        return peer.name ? peer.name : peerId;
    } else {
        return self.name;
    }
}

- (NSString *)lcim_peerId {
    NSArray *members = self.members;
    if (members.count == 0) {
        [NSException raise:@"invalid conversation" format:@"invalid conversation"];
    }
    if (members.count == 1) {
        return members[0];
    }
    NSString *peerId;
    if ([members[0] isEqualToString:[LCCKSessionService sharedInstance].clientId]) {
        peerId = members[1];
    } else {
        peerId = members[0];
    }
    return peerId;
}

- (NSString *)lcim_title {
    if (self.lcim_type == LCCKConversationTypeSingle) {
        return self.lcim_displayName;
    } else {
        return [NSString stringWithFormat:@"%@(%ld)", self.lcim_displayName, (long)self.members.count];
    }
}

@end

