//
//  Mutyda.h
//  Mutyda
//
//  Created by Admin on 13.09.15.
//  Copyright (c) 2015 MeshSoft Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface Mutyda : NSObject

- (id)autenticationWithSID:(NSString*)sid appID:(NSString*)appID appScheme:(NSString*)appScheme appURL:(NSString*)appURL;
- (NSString*)checkAuthenticationResultFromURL:(NSURL*)url;

@end