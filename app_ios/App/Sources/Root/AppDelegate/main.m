//

int main(int argc, char *argv[]) {
    NSString *delegate = nil;
    
//    delegate = @"CQCPPCarrierAppDelegate";
    
    if (delegate == nil) {
        delegate = @"AppDelegate";
    }
    return UIApplicationMain(argc, argv, nil, delegate);
}
