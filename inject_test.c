#include <UIKit/UIKit.h>
#include <dispatch/dispatch.h>

static void showTestAlert(){
    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Dylib测试"
                                                                         message:@"动态库注入加载成功！"
                                                                  preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *okBtn = [UIAlertAction actionWithTitle:@"关闭" style:0 handler:nil];
        [alert addAction:okBtn];
        UIViewController *root = [UIApplication sharedApplication].keyWindow.rootViewController;
        [root presentViewController:alert animated:YES completion:nil];
    });
}

// dylib被App加载自动执行此函数
__attribute__((constructor)) void lib_enter(){
    //延迟5秒弹窗
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 5ull * NSEC_PER_SEC),
                   dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0),^{
        showTestAlert();
    });
}
