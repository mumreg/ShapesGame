//
//  FileUtils_objc.h
//  BaseEngine
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FileUtils_objc : NSObject

+(const char *)getFullPathFor:(NSString *)fileName;

@end
