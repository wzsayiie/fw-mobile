#import "IAPDemoController.h"
#import <StoreKit/StoreKit.h>

@interface IAPDemoController () <SKProductsRequestDelegate, SKPaymentTransactionObserver>
@property (nonatomic, weak) IBOutlet UITableView *tableView;
@property (nonatomic, copy) NSArray<SKProduct *> *productList;
@end

@implementation IAPDemoController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self addRow:@"1. can make payments"    action:@selector(handleCanMakePayments)];
    [self addRow:@"2. request products"     action:@selector(handleRequestProducts)];
    [self addRow:@"3. make payment"         action:@selector(handleMakePayment)];
    [self addRow:@"4. restore transactions" action:@selector(handleRestoreTransactions)];
}

#pragma mark - 1. can make payments

- (void)handleCanMakePayments {
    
    if ([SKPaymentQueue canMakePayments]) {
        I(@"can make payments");
    } else {
        I(@"can't make payments");
    }
}

#pragma mark - 2. request products

- (void)handleRequestProducts {
    
    NSMutableSet<NSString *> *identifiers = [NSMutableSet set];
    //[identifiers addObject:@""];
    
    if (identifiers.count == 0) {
        E(@"not specify identifers of product need to request");
        return;
    }
    
    I(@"request products");
    SKProductsRequest *request = [[SKProductsRequest alloc] initWithProductIdentifiers:identifiers];
    request.delegate = self;
    [request start];
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    
    self.productList = response.products;
    
    //SKProduct couldn't distinguish bewteen consumable product and subscript product
    
    I(@"request products' response: {");
    for (SKProduct *product in response.products) {
        I(@"  '%@'", product.productIdentifier);
    }
    I(@"}");
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error {
    E(@"request products error: %@", error);
}

- (void)requestDidFinish:(SKRequest *)request {
    I(@"request products finish");
}

#pragma mark - 3. make payment

- (void)handleMakePayment {
    
    if (self.productList.count == 0) {
        E(@"there are not available products, firstly request product");
        return;
    }
    
    //to purchase first product here
    SKProduct *product = self.productList[0];
    
    SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:product];
    payment.applicationUsername = @"user_custom_data";
    payment.quantity = 1;
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray<SKPaymentTransaction *> *)transactions {
    I(@"transaction list: {");
    
    NSMutableArray<SKPaymentTransaction *> *finishedTransactions = [NSMutableArray array];
    for (SKPaymentTransaction *t in transactions) {
        
        BOOL f = NO;
        switch (t.transactionState) {
            case SKPaymentTransactionStatePurchasing: [self updatePurchasing:t isFinished:&f]; break;
            case SKPaymentTransactionStatePurchased : [self updatePurchased :t isFinished:&f]; break;
            case SKPaymentTransactionStateFailed    : [self updateFailed    :t isFinished:&f]; break;
            case SKPaymentTransactionStateRestored  : [self updateRestored  :t isFinished:&f]; break;
            case SKPaymentTransactionStateDeferred  : [self updateDeferred  :t isFinished:&f]; break;
            default:;
        }
        if (f) {
            [finishedTransactions addObject:t];
        }
    }
    for (SKPaymentTransaction *transaction in finishedTransactions) {
        [queue finishTransaction:transaction];
    }
    
    I(@"}");
}

- (void)updatePurchasing:(SKPaymentTransaction *)transaction isFinished:(BOOL *)finished {
    NSString *transactionID = transaction.transactionIdentifier;
    NSString *productID = transaction.payment.productIdentifier;
    
    I(@"  transaction '%@' (product '%@') added", transactionID, productID);
}

- (void)updatePurchased:(SKPaymentTransaction *)transaction isFinished:(BOOL *)finished {
    NSString *transactionID = transaction.transactionIdentifier;
    NSString *productID = transaction.payment.productIdentifier;
    
    //if a transaction restored, the current transaction holds new ID, new receipt.
    //property 'originalTransaction' retrieves the restored one.
    if (transaction.originalTransaction == nil) {
        I(@"  transaction '%@' (product '%@') purchased", transactionID, productID);
    } else {
        I(@"  transaction '%@' (product '%@') restored", transactionID, productID);
    }
    
    //all receipts of transaction were stored at [[NSBundle mainBundle] appStoreReceiptURL]
    
    *finished = YES;
}

- (void)updateFailed:(SKPaymentTransaction *)transaction isFinished:(BOOL *)finished {
    NSString *transactionID = transaction.transactionIdentifier;
    NSString *productID = transaction.payment.productIdentifier;
    
    I(@"  transaction '%@' (product '%@') failed", transactionID, productID);
    
    *finished = YES;
}

- (void)updateRestored:(SKPaymentTransaction *)transaction isFinished:(BOOL *)finished {
    NSString *transactionID = transaction.transactionIdentifier;
    NSString *productID = transaction.payment.productIdentifier;
    
    I(@"  transaction '%@' (product '%@') restored", transactionID, productID);
    
    *finished = YES;
}

- (void)updateDeferred:(SKPaymentTransaction *)transaction isFinished:(BOOL *)finished {
    NSString *transactionID = transaction.transactionIdentifier;
    NSString *productID = transaction.payment.productIdentifier;
    
    I(@"  transaction '%@' (product '%@') is waiting", transactionID, productID);
}

#pragma mark - 4. restore transactions

- (void)handleRestoreTransactions {
    
    //if a product purchased is restorable,
    //user can "restore" it after re-install app or change device
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

@end
