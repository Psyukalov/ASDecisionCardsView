//
//  ASDecisionCardsView.h
//
//
//  Created by Vladimir Psyukalov on 01.08.2018.
//  Copyright © 2018 Psyukalov. All rights reserved.
//


#import <UIKit/UIKit.h>


@class ASDecisionCardsView;


@protocol ASDecisionCardProtocol <NSObject>

@optional

/**
 
 Implement this method for custom reaction to changing offset.
 
 @param view ASDecisionCardsView's superview of UIView's object.
 @param offset CGFloat value of horizontal offset from superview's center to UIView's object center. Сan be from -1.f to 1.f (inclusive both).
 
 */

- (void)decisionCardsView:(ASDecisionCardsView *)view didChangeOffset:(CGFloat)offset;

@end


@interface ASDecisionCardsView : UIView

/**
 
 @property visibleCardsCount
 
 @brief Set count of visible card on ASDecisionCardsView's view;
 
 */

@property (assign, nonatomic) NSUInteger visibleCardsCount;

@end
