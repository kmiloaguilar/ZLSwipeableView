//
//  ZLSwipeableView.h
//  ZLSwipeableViewDemo
//
//  Created by Zhixuan Lai on 11/1/14.
//  Copyright (c) 2014 Zhixuan Lai. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZLSwipeableViewMovement.h"
#import "ZLSwipeableViewSwipeOptions.h"

typedef NS_ENUM(NSUInteger, ZLSwipeableViewDirection) {
    ZLSwipeableViewDirectionNone = 0,
    ZLSwipeableViewDirectionLeft = (1 << 0),
    ZLSwipeableViewDirectionRight = (1 << 1),
    ZLSwipeableViewDirectionHorizontal = ZLSwipeableViewDirectionLeft |
                                         ZLSwipeableViewDirectionRight,
    ZLSwipeableViewDirectionUp = (1 << 2),
    ZLSwipeableViewDirectionDown = (1 << 3),
    ZLSwipeableViewDirectionVertical = ZLSwipeableViewDirectionUp | ZLSwipeableViewDirectionDown,
    ZLSwipeableViewDirectionAll = ZLSwipeableViewDirectionHorizontal |
                                  ZLSwipeableViewDirectionVertical,
};

typedef NS_ENUM(NSUInteger, ZLSwipeableViewSwipeRestriction) {
    ZLSwipeableViewSwipeRestrictionNone = 0,
    ZLSwipeableViewSwipeRestrictionHard = 1,  // swiping will do nothing
    ZLSwipeableViewSwipeRestrictionSoft = 2  // swiping is allowed, but it will never swipe away.  the physics is used
};

@class ZLSwipeableView;

@protocol ZLSwipeableViewAnimator <NSObject>

@required
- (void)animateView:(UIView *)view
              index:(NSUInteger)index
              views:(NSArray<UIView *> *)views
      swipeableView:(ZLSwipeableView *)swipeableView;

@end

@protocol ZLSwipeableViewDirectionInterpretor <NSObject>

@required
- (ZLSwipeableViewSwipeOptions *)interpretDirection:(ZLSwipeableViewDirection)direction
                                               view:(UIView *)view
                                              index:(NSUInteger)index
                                              views:(NSArray<UIView *> *)views
                                      swipeableView:(ZLSwipeableView *)swipeableView;

@end

@protocol ZLSwipeableViewSwipingDeterminator <NSObject>

@required
- (BOOL)shouldSwipeView:(UIView *)view
               movement:(ZLSwipeableViewMovement *)movement
          swipeableView:(ZLSwipeableView *)swipeableView;

@end

/// Delegate
@protocol ZLSwipeableViewDelegate <NSObject>
@optional
- (void)swipeableView:(ZLSwipeableView *)swipeableView
         didSwipeView:(UIView *)view
          inDirection:(ZLSwipeableViewDirection)direction;

- (void)swipeableView:(ZLSwipeableView *)swipeableView didCancelSwipe:(UIView *)view;

- (void)swipeableView:(ZLSwipeableView *)swipeableView
  didStartSwipingView:(UIView *)view
           atLocation:(CGPoint)location;

- (void)swipeableView:(ZLSwipeableView *)swipeableView
          swipingView:(UIView *)view
           atLocation:(CGPoint)location
          translation:(CGPoint)translation;

- (void)swipeableView:(ZLSwipeableView *)swipeableView
    didEndSwipingView:(UIView *)view
           atLocation:(CGPoint)location;

@end

// DataSource
@protocol ZLSwipeableViewDataSource <NSObject>

@required
- (UIView *)nextViewForSwipeableView:(ZLSwipeableView *)swipeableView;

@optional
- (UIView *)previousViewForSwipeableView:(ZLSwipeableView *)swipeableView;

@end

@interface ZLSwipeableView : UIView

// data source
@property (nonatomic, weak) IBOutlet id<ZLSwipeableViewDataSource> dataSource;

@property (nonatomic) NSUInteger numberOfActiveViews;
@property (nonatomic, readonly) UIView *topSwipeableView;
@property (nonatomic, readonly) UIView *secondFromTopSwipeableView;

// delegate
@property (nonatomic, weak) IBOutlet id<ZLSwipeableViewDelegate> delegate;

// history
@property (nonatomic, readonly) NSArray<UIView *> *history;
@property (nonatomic) NSUInteger numberOfHistoryItem;

// Customization
@property (nonatomic, strong) id<ZLSwipeableViewAnimator> viewAnimator;
@property (nonatomic, strong) id<ZLSwipeableViewDirectionInterpretor> directionInterpretor;
@property (nonatomic, strong) id<ZLSwipeableViewSwipingDeterminator> swipingDeterminator;
@property (nonatomic) CGFloat minTranslationInPercent;
@property (nonatomic) CGFloat minVelocityInPointPerSecond;
@property (nonatomic) ZLSwipeableViewDirection allowedDirection;
@property (nonatomic, assign) ZLSwipeableViewSwipeRestriction restriction;

- (UIView *)topView;

- (NSArray<UIView *> *)activeViews;

- (void)loadViewsIfNeeded;

- (void)rewind;

- (void)discardAllViews;

- (void)swipeTopViewToLeft;

- (void)swipeTopViewToRight;

- (void)swipeTopViewToUp;

- (void)swipeTopViewToDown;

- (void)swipeTopViewInDirection:(ZLSwipeableViewDirection)direction;

- (void)swipeTopViewFromPoint:(CGPoint)point inDirection:(CGVector)directionVector;

- (void)reloadData;

@end
