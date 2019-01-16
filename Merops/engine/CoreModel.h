//
//  CoreModel.h
//  Merops
//
//  Created by sho sumioka on 2019/01/09.
//  Copyright © 2019 sho sumioka. All rights reserved.
//

#ifndef CoreModel_h
#define CoreModel_h

#import <Foundation/Foundation.h>

@interface CoreModel : NSObject

// scene
@property id root;
@property id current;

// model
@property NSString* name;
@property id attr;
@property int Id;
@property id geometry;
@property id shader;
@property id transform;

// CRUD
- (id)Create:(NSString *)name;
- (void)Delete;
- (id)Select:(NSString *)name;
- (id)Copy;
- (void)SetName:(NSString *)name;
- (void)SetAttr:(id)attr;
- (void)Hide;
- (void)Lock;

- (id)Import;
- (NSString *)Export;

// private
- (void)_Update;

@end

#endif /* CoreModel_h */
