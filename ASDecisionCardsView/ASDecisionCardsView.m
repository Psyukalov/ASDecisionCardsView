//
//  ASDecisionCardsView.m
//
//
//  Created by Vladimir Psyukalov on 01.08.2018.
//  Copyright © 2018 Psyukalov. All rights reserved.
//


#import "ASDecisionCardsView.h"


#define DEFAULT_VISIBLE_CARDS_COUNT (4)
#define MAXIMUM_VISIBLE_CARDS_COUNT (32)


@interface ASDecisionCardsView ()

{
    UIView *animatedView;
}

@property (strong, nonatomic) NSMutableArray *cardsQueue;

@property (strong, nonatomic, readonly) UIView *topCardInCardsQueue;

@property (assign, nonatomic, readonly) BOOL moreThanVisibles;

@end


@implementation ASDecisionCardsView

#pragma mark - Overriding methods

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self setup];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        [self setup];
    }
    return self;
}

#pragma mark - Private methods

- (void)setup {
    _cardsQueue = [NSMutableArray new];
    self.visibleCardsCount = DEFAULT_VISIBLE_CARDS_COUNT;
}

- (UIView *)cardFromQueueAtIndex:(NSUInteger)index {
    if (_cardsQueue.count == 0 || index >= _cardsQueue.count) return nil;
    return _cardsQueue[index];
}

- (void)addCardToSuperview:(UIView *)card {
    if (self.subviews.lastObject) {
        [self insertSubview:card belowSubview:self.subviews.firstObject];
    } else {
        [self addSubview:card];
    }
}

- (void)addCardFromCardsQueue {
    if (self.moreThanVisibles || !self.topCardInCardsQueue) return;
    UIView *card = self.topCardInCardsQueue;
    [_cardsQueue removeObject:card];
    [self addCardToSuperview:card];
    [self startAnimating];
}

- (void)startAnimating {
    UIView *card = self.subviews.firstObject;
    animatedView = card;
    if ([_delegate respondsToSelector:@selector(decisionCardsView:cardBeforeMovingToVisibleQueue:)]) {
        [_delegate decisionCardsView:self cardBeforeMovingToVisibleQueue:card];
    }
    if ([_delegate respondsToSelector:@selector(decisionCardsView:cardAfterMovingToVisibleQueue:)]) {
        [UIView animateWithDuration:.64f delay:0.f options:UIViewAnimationOptionCurveEaseInOut animations:^{
            [self->_delegate decisionCardsView:self cardAfterMovingToVisibleQueue:card];
        } completion:^(BOOL finished) {
            self->animatedView = nil;
        }];
    }
}

#pragma mark - Public methods

- (void)addCard:(UIView *)card {
    if (!card) @throw [NSException exceptionWithName:@"ASInvalidParameterException" reason:@"View is can not be a nil" userInfo:nil];
    if (self.moreThanVisibles) {
        [_cardsQueue addObject:card];
    } else {
        [self addCardToSuperview:card];
        [self startAnimating];
    }
}

- (void)removeCardsAnimated:(BOOL)animated {
#warning Implement.
}

- (void)madeDecisionWithType:(ASDecisionType)type {
    if (self.topCard == animatedView) return;
    [self.topCard removeFromSuperview];
    [self addCardFromCardsQueue];
}

#pragma mark - Private properties

- (UIView *)topCardInCardsQueue {
    return [self cardFromQueueAtIndex:0];
}

- (BOOL)moreThanVisibles {
    return self.subviews.count >= _visibleCardsCount;
}

#pragma mark - Public properties

- (void)setVisibleCardsCount:(NSUInteger)visibleCardsCount {
    NSUInteger maximum = MAXIMUM_VISIBLE_CARDS_COUNT;
    _visibleCardsCount = visibleCardsCount == 0 ? 1 : (visibleCardsCount > maximum ? maximum : visibleCardsCount);
}

- (NSUInteger)cardsCount {
    return self.subviews.count + _cardsQueue.count;
}

- (UIView *)topCard {
    return self.subviews.lastObject;
}

@end
