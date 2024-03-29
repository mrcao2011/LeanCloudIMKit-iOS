//
//  LCCKContactListController.h
//  LeanCloudChatKit-iOS
//
//  Created by ElonChan on 16/2/22.
//  Copyright © 2016年 LeanCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LCCKBaseTableViewController.h"

typedef enum : NSUInteger {
    LCCKContactListModeNormal,
    LCCKContactListModeSingleSelection,
    LCCKContactListModeMultipleSelection
} LCCKContactListMode;

@class LCCKContactListController;

@protocol LCCKContactListControllerDelegate <NSObject>
- (void)contactListController:(LCCKContactListController *)controller
           didSelectPeerIds:(NSArray *)peerIds;
@end

@interface LCCKContactListController : LCCKBaseTableViewController

@property (nonatomic, assign) LCCKContactListMode mode;
@property (nonatomic, strong) NSArray *excludedPersonIDs;
@property (nonatomic, weak) id<LCCKContactListControllerDelegate> delegate;

- (void)refresh;

@end
