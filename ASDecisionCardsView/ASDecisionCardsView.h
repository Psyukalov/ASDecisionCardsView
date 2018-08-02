//
//  ASDecisionCardsView.h
//
//
//  Created by Vladimir Psyukalov on 01.08.2018.
//  Copyright © 2018 Psyukalov. All rights reserved.
//


#import <UIKit/UIKit.h>


/**
 
 @brief Decision type.
 
 */

typedef NS_ENUM(NSUInteger, ASDecisionType) {
    ASDecisionTypeCancel = 0,
    ASDecisionTypeUndefined,
    ASDecisionTypePositive,
    ASDecisionTypeNegative,
};


@class ASDecisionCardsView;


@protocol ASCardProtocol <NSObject>

@optional

/**
 
 Implement this method for custom reaction to changing offset.
 
 @param view ASDecisionCardsView's superview of card.
 @param offset CGFloat value of horizontal offset from superview's center to card center. Сan be from -1.f to 1.f (inclusive both).
 
 */

- (void)decisionCardsView:(ASDecisionCardsView *)view didChangeOffset:(CGFloat)offset;

@end


@protocol ASDecisionCardsViewDelegate <NSObject>

@optional

/**
 
 Implement this method for card customize before his moving to visible queue, such as alpha, CGAffineTransform and etc.
 
 @param view ASDecisionCardsView's object.
 @param card Card for customize from cards queue at index 'visibleCardsCount' or less if this parameter greater than cards count in queue.
 
 */

- (void)decisionCardsView:(ASDecisionCardsView *)view cardBeforeMovingToVisibleQueue:(UIView *)card;

/**
 
 Implement this method for card customize after his moving to visible queue, such as alpha, CGAffineTransform and etc.
 
 @param view ASDecisionCardsView's object.
 @param card Card for customize from cards queue at index 'visibleCardsCount' - 1 or less if this parameter greater than cards count in queue.
 
 */

- (void)decisionCardsView:(ASDecisionCardsView *)view cardAfterMovingToVisibleQueue:(UIView *)card;

/**
 
 Implement this method for card customize after his moving to top, such as alpha, CGAffineTransform and etc.
 
 @param view ASDecisionCardsView's object.
 @param card Card for customize from cards queue at index 0.
 
 */

- (void)decisionCardsView:(ASDecisionCardsView *)view cardAfterMovingToTop:(UIView *)card;

/**
 
 Implement this method for define reaction to decision made. If also needed use first card (top card) use ASDecisionCardsView's object property 'topCard'.
 
 @param view ASDecisionCardsView's object.
 @param type ASDecisionType value of maded decision.
 
 @return BOOL value that says can we skip top card or not. If method is not implemented default value is YES (always skipping) except when type is equal to ASDecisionTypeCancel.
 
 */

- (BOOL)decisionCardsView:(ASDecisionCardsView *)view didMadeDecisionType:(ASDecisionType)type;

@end


@interface ASDecisionCardsView : UIView

/**
 
 @property delegate
 
 @brief ASDecisionCardsView's delegate.
 
 */

@property (weak, nonatomic) id<ASDecisionCardsViewDelegate> delegate;

/**
 
 @property visibleCardsCount
 
 @brief Set count of visible cards for ASDecisionCardsView's object. Minimum is 1, maximum is 32. Default is 4.
 
 */

@property (assign, nonatomic) NSUInteger visibleCardsCount;

/**
 
 @property cardsCount
 
 @brief Cards count from cards views queue.
 
 */

@property (assign, nonatomic, readonly) NSUInteger cardsCount;

/**
 
 @property topCard
 
 @brief Card in cards queue at index 0.
 
 */

@property (strong, nonatomic, readonly) UIView *topCard;

/**
 
 This method add new card to cards queue.
 
 @param card Сard that need to add.
 
 */

- (void)addCard:(nonnull UIView *)card;

/**
 
 This method remove all card from cards queue.
 
 @param animated Says that need to remove with animation.
 
 */

- (void)removeCardsAnimated:(BOOL)animated;

/**
 
 This method made decision for top card.
 
 @param type Says that decision type need for top card.
 
 */

- (void)madeDecisionWithType:(ASDecisionType)type;

@end
